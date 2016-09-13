#include "GLApplication.h"

Sphere sphere(0.5, 40, 40);
Shader shader, shaderc;
Texture * texture1;
Texture * texture2;
GLuint VBOcub, VAOcub;

struct VertexTexture {
	glm::vec3 m_Pos;
	glm::vec2 m_TexCoord;
};

GLApplication::GLApplication() :
		windowManager(nullptr), camera(nullptr) {
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

	VertexTexture vertices[36] = {
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f,0.0f)  },
		{ glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec2(0.0f, 1.0f) }, 
		{ glm::vec3(-0.5f,-0.5f, -0.5f),  glm::vec2(0.0f, 0.0f) }, 
		{ glm::vec3(-0.5f, -0.5f,0.5f),   glm::vec2(0.0f, 0.0f) }, 
		{ glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec2(0.0f, 1.0f) }, 
		{ glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) }, 
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) }, 
		{ glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec2(1.0f, 1.0f) }, 
		{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f) }, 
		{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) }, 
		{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 1.0f) }, 
		{ glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) }, 
		{ glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) },
	    { glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec2(0.0f, 1.0f) }, 
		{ glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec2(0.0f, 0.0f) }, 
		{ glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec2(0.0f, 1.0f) }
	
	};
	
	glGenVertexArrays(1, &VAOcub);
	glGenBuffers(1, &VBOcub);

	glBindVertexArray(VAOcub);

	glBindBuffer(GL_ARRAY_BUFFER, VBOcub);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),(GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture Mapping attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),(GLvoid*) sizeof(vertices[0].m_Pos));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind VAO

	shaderc.initialize("Shaders/sistemascoordenados.vs","Shaders/sistemascoordenados.fs");

	//iniciar y cargar la esfera

	sphere.init();
	sphere.load();

	shader.initialize("Shaders/Esfera.vs", "Shaders/Esfera.fs");

	//Carga la textura1
	texture1 = new Texture(GL_TEXTURE_2D, "Textures/awesomeface.png");
	texture1->load();

	//Carga la textura2
	texture2 = new Texture(GL_TEXTURE_2D, "Textures/test.png");
	texture2->load();

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
		view = camera->GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(45.0f,(GLfloat) WindowManager::screenWidth / (GLfloat) WindowManager::screenHeight, 0.1f, 100.0f);

		// Get their uniform location
		GLint modelLoc = shader.getUniformLocation("model");
		GLint viewLoc = shader.getUniformLocation("view");
		GLint projLoc = shader.getUniformLocation("projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.75f, 0.0f, 0.0f));
		model = glm::rotate(model, (GLfloat) timeValue * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Poner textura esfera 
		texture2->bind(GL_TEXTURE0);
		glUniform1i(shader.getUniformLocation("ourTexture"), 0);

		//poner la esfera
		sphere.render();
		shader.turnOff();
		
		//Poner textura Cubo 
		shaderc.turnOn();

		texture1->bind(GL_TEXTURE0);
		glUniform1i(shaderc.getUniformLocation("ourTexture"), 0);
		texture2->bind(GL_TEXTURE1);
		glUniform1i(shaderc.getUniformLocation("ourTexture2"), 1);
		
		// Get their uniform location
		shaderc.getUniformLocation("model");
		modelLoc = shaderc.getUniformLocation("model");
		viewLoc = shaderc.getUniformLocation("view");
		projLoc = shaderc.getUniformLocation("projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAOcub);
		//poner el cubo
		glm::mat4 modelantes;
		modelantes = glm::translate(modelantes, glm::vec3(0.75f, 0.0f, 0.0f));
		modelantes = glm::rotate(modelantes, (GLfloat)timeValue * 1.0f, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelantes));
		model = glm::rotate(model, (GLfloat)timeValue * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		shaderc.turnOff();
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
