/*
 * GLApplication.cpp
 *
 *  Created on: 20/08/2016
 *      Author: Diego Martinez
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLApplication.h"

GLuint VBO, VAO, EBO, texture;
Shader shader;

struct VertexColorTexture {
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
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
		|| !windowManager->initialize(800, 700, "T2_E8", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	shader.initialize("Shaders/texture.vs", "Shaders/texture.fs");

	// Set up vertex data (and buffer(s)) and attribute pointers
	VertexColorTexture vertices[36] = {

		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ -1.0f, 1.0f } }, //7
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ -1.0f, -1.0f } }, // 6
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 4

		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ -1.0f, -1.0f } }, // 6
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, -1.0f } }, // 5
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 4



		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 0
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 5
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 0.0f } }, // 1

		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 0
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 1.0f } }, // 4
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 5

		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 1
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 0.0f } }, // 2
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 3

		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 3
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 1.0f } }, // 0
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 1

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 2
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 0.0f } }, // 0
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, //7

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 2
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, //7
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 1.0f } }, // 3

		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, //7
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 0.0f } }, // 4
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 0

		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, //7
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 0
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 1.0f } }, // 3

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 2
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 0.0f } }, // 1
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 5

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 0.0f } }, // 2
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 1.0f, 1.0f } }, // 5
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2{ 0.0f, 1.0f } } // 6

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*) sizeof(vertices[0].m_Pos));
	glEnableVertexAttribArray(1);
	// Texture Mapping attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)(sizeof(vertices[0].m_Color) + sizeof(vertices[0].m_Pos)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	//This for load a texture with FreeImage lib
	// Se obtiene del nombre del archivo a cargar en la GPU como un apuntador a un arreglo de chars
	const char* filename = "Textures/test.png";

	// Determina el formato de la imagen
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

	// Si la imagen no es encontrada termina el programa
	if (format == -1) {
		std::cout << "No se encontr� la imagen: " << filename << " - Abortando."
			<< std::endl;
		exit(-1);
	}
	// Si el formato no es soportado por FreeImage termina el programa
	if (format == FIF_UNKNOWN) {
		std::cout
			<< "No se puede determinar el formato de imagen - validarla extensi�n del archivo..."
			<< std::endl;

		// Se obtiene el formato del archivo
		format = FreeImage_GetFIFFromFilename(filename);

		// Revisa si la librer�a es capaz de leer el formato
		if (!FreeImage_FIFSupportsReading(format)) {
			std::cout << "El formato de la imagen no puede ser lee�do!"
				<< std::endl;
			exit(-1);
		}
	}
	// Si es valida la imagen y puede ser lee�do, se carga la imagen en un bitap
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	FreeImage_FlipVertical(bitmap);

	// Obtiene el n�mero de bits por pixel de la imagen
	int bitsPerPixel = FreeImage_GetBPP(bitmap);

	// Convierte la imagen a 32 bits (8 bits por canal).
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		/*std::cout << "Source image has " << bitsPerPixel
		<< " bits per pixel. Skipping conversion." << std::endl;*/
		bitmap32 = bitmap;
	}
	else {
		/*std::cout << "Source image has " << bitsPerPixel
		<< " bits per pixel. Converting to 32-bit colour." << std::endl;*/
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}
	// Se obtiene las dimensiones de la imagen.
	int imageWidth = FreeImage_GetWidth(bitmap32);
	int imageHeight = FreeImage_GetHeight(bitmap32);
	/*std::cout << "Image: " << m_fileName << " is size: " << imageWidth << "x"
	<< imageHeight << "." << std::endl;*/

	// Se obtiene un apuntador a los datos de la textura como un arreglo de unsigned bytes.
	GLubyte* textureData = FreeImage_GetBits(bitmap32);

	// Load and create a texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unload the 32-bit colour bitmap
	// Se desecha los datos de la textura
	FreeImage_Unload(bitmap32);

	// Si se convirtio la imagen a 32 bits por pixel eliminamos el bitmap
	if (bitsPerPixel != 32) {
		FreeImage_Unload(bitmap);
	}

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

}

void GLApplication::applicationLoop() {
	bool processInput = true;
	double lastTime = TimeManager::Instance().GetTime();
	while (processInput) {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		shader.turnOn();
		// Bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);

		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;

		/* Create transformations
		glm::mat4 transform;
		//transform = glm::translate(transform, glm::vec3(InputManager::mouseClicked));
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.7f));
		transform = glm::rotate(transform, (GLfloat)timeValue * 1.0f,
		glm::vec3(0.0f, 1.0f, 0.0f));
		//transform = glm::rotate(transform, 1.0f,
		//glm::vec3(lastMousePos.x, lastMousePos.y, 0.0f));
		// Get matrix's uniform location and set matrix
		GLint transformLoc = shader.getUniformLocation("transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
		glm::value_ptr(transform));

		*/
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

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

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

	glDeleteTextures(1, &texture);
}