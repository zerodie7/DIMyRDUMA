/*
 * GLApplication.cpp
 *
 *  Created on: 20/08/2016
 *      Author: Diego Martinez
 */

#include "GLApplication.h"

// Shaders
const GLchar* vertexShaderSource = { "#version 400\n"

"layout(location=0) in vec4 in_Position;\n"
"layout(location=1) in vec4 in_Color;\n"
"out vec4 ex_Color;\n"

"void main(void)\n"
"{\n"
"  gl_Position = in_Position;\n"
"  ex_Color = in_Color;\n"
"}\n" };
const GLchar* fragmentShaderSource = { "#version 400\n"

"in vec4 ex_Color;\n"
"out vec4 out_Color;\n"

"void main(void)\n"
"{\n"
"  out_Color = ex_Color;\n"
"}\n" };

GLuint VBO, VAO, ColorBufferId;
GLint vertexShader, fragmentShader, shaderProgram;

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
		|| !windowManager->initialize(800, 700, "Triangles", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Build and compile our shader program
	// Vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
			<< std::endl;
	}
	// Fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
			<< std::endl;
	}
	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog
			<< std::endl;
	}

	// This is for primitive GL_TRIANGLE_STRIP
	GLfloat Vertices[] = {
		-0.8f, 0.8f, 0.0f, 1.0f,
		0.8f, 0.8f, 0.0f, 1.0f,
		-0.8f,-0.8f, 0.0f, 1.0f,

		-0.8f, -0.8f, 0.0f, 1.0f,
		0.8f, 0.8f, 0.0f, 1.0f,
		0.8f, -0.8f, 0.0f,1.0f };

	GLfloat Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
		1.0f,0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,1.0f };

	// This is for primitive GL_TRIANGLE_STRIP
	/*GLfloat Vertices[] = { -0.8f, 0.8f, 0.0f, 1.0f, 0.8f, 0.8f, 0.0f, 1.0f,
	-0.8f, -0.8f, 0.0f, 1.0f, 0.8f, -0.8f, 0.0f, 1.0f };

	GLfloat Colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };*/

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
}

void GLApplication::applicationLoop() {
	bool processInput = true;
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// Draw our first rectagle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// This is for primitive GL_TRIANGLE
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// This is for primitive GL_TRIANGLE_STRIP
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}

	glUseProgram(0);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(shaderProgram);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
}
