
#include "GLApplication.h"
#include "Sphere.h"


Sphere sphere(1, 40, 40);
Shader shader;
Texture * texture1;
Texture * texture2;


struct VertexTexture {
	glm::vec3 m_Pos;
	glm::vec2 m_TexCoord;
};

GLApplication::GLApplication() :
windowManager(nullptr) {
}

GLApplication::~GLApplication() {
	destroy();
}

void GLApplication::GLMain() {
	initialize();
	applicationLoop();
}

void GLApplication::initialize() {
	if (!windowManager
		|| !windowManager->initialize(800, 700, "Practica1", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	sphere.init();
	sphere.load();


	//shader.initialize("Shaders/Color.vs", "Shaders/Color.fs");
	shader.initialize("Shaders/Esfera.vs", "Shaders/Esfera.fs");

	texture1 = new Texture(GL_TEXTURE_2D, "Textures/awesomeface.png");
	texture1->loadt();

	texture2 = new Texture(GL_TEXTURE_2D, "Textures/test.png");
	texture2->loadt();

}

void GLApplication::applicationLoop() {
	bool processInput = true;
	double lastTime = TimeManager::Instance().GetTime();
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;

		shader.turnOn();

		// Create transformations
		glm::mat4 view;
		glm::mat4 projection;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(45.0f, (GLfloat)WindowManager::screenWidth / (GLfloat)WindowManager::screenHeight, 0.1f, 100.0f);
		// Get their uniform location
		shader.getUniformLocation("model");
		GLint modelLoc = shader.getUniformLocation("model");
		GLint viewLoc = shader.getUniformLocation("view");
		GLint projLoc = shader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model;
		model = glm::rotate(model, (GLfloat)timeValue * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//unir la textura
		texture2->bindt(GL_TEXTURE0);
		glUniform1i(shader.getUniformLocation("ourTexture"), 0);

		//poner la esfera
		sphere.render();
		shader.turnOff();

		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}

	shader.destroy();
}
