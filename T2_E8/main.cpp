#include "GLApplication.h"
#include "GLFWManager.h"

int main(int argc, char ** argv) {
	GLFWManager * ptrWindowManager = new GLFWManager();

	GLApplication application;
	application.setWindowManager(ptrWindowManager);
	application.GLMain();

	return EXIT_SUCCESS;
}

