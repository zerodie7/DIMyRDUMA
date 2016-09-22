/*
 * GLApplication.h
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */

#ifndef GLAPPLICATION_H_
#define GLAPPLICATION_H_

#include <stdlib.h>

#include <GL/glew.h>

#include "WindowManager.h"
#include "Sphere.h"
#include "Shader.h"
#include "CameraTPS.h"
#include "TimeManager.h"
#include "Texture.h"

class GLApplication {
public:

	GLApplication();
	~GLApplication();

	void GLMain();
	void initialize();
	void applicationLoop();
	void destroy();

	void setWindowManager(WindowManager * windowManager) {
		this->windowManager = windowManager;
	}

	WindowManager * getWindowManager() {
		return windowManager;
	}

	CameraTPS* getCamera() {
		return camera;
	}

	void setCamera(CameraTPS* camera) {
		this->camera = camera;
	}

protected:
	WindowManager * windowManager;
	CameraTPS * camera;

};

#endif /* GLAPPLICATION_H_ */
