#ifndef _InputManagerTPS_H
#define _InputManagerTPS_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standar GLFW for the management of inputs codes keyboards
enum InputCodes {
	kEscape = 27,
	Space = 32,
	Left = 37,
	Up = 38,
	Right = 39,
	Down = 40,
	a = 97,
	A = 65,
	b = 98,
	B = 66,
	c = 99,
	C = 67,
	d = 100,
	D = 68,
	e = 101,
	E = 69,
	f = 102,
	F = 70,
	g = 103,
	G = 71,
	h = 104,
	H = 72,
	i = 105,
	I = 73,
	j = 106,
	J = 74,
	k = 107,
	K = 75,
	l = 108,
	L = 76,
	m = 109,
	M = 77,
	n = 110,
	N = 78,
	o = 111,
	O = 79,
	p = 112,
	P = 80,
	q = 113,
	Q = 81,
	r = 114,
	R = 82,
	s = 115,
	S = 83,
	t = 116,
	T = 84,
	u = 117,
	U = 85,
	v = 118,
	V = 86,
	w = 119,
	W = 87,
	x = 120,
	X = 88,
	y = 121,
	Y = 89,
	z = 122,
	Z = 90
};

enum MouseButtonIndex {
	LEFT = 0, RIGHT = 1, MIDDLE = 2
};

enum State {
	RELESED = 0, PRESSED = 1, REPEATED = 2
};

class InputManager {
public:

	InputManager() :
		lastMousePos(glm::ivec2(0.0)), deltax(0), deltay(0), scrollYoffset(
		0), cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), yaw(0), pitch(
		20), roll(0), distanceFromPlayer(5), angleAroundPlayer(0), initDir(
		false) {
		mouseButtomState = new bool[3];
		keyState = new bool[1024];
		for (int i = 0; i < 3; i++)
			mouseButtomState[i] = false;
		for (int i = 0; i < 1024; i++)
			keyState[i] = false;
	}

	~InputManager() {
		delete[]mouseButtomState;
		delete[]keyState;
	}

	InputCodes toApplicationKey(int key);
	State toApplicationState(int state);
	MouseButtonIndex toMouseButtonIndex(int button);

	void keyPressed(InputCodes code, float deltaTime, State state);
	void mouseMoved(float mouseX, float mouseY);
	void mouseClicked(MouseButtonIndex code, float mouseX, float mouseY,
		State state);
	void mouseScroll(float yoffset);
	void do_movement(float deltaTime);

	glm::ivec2 getLastMousePos() {
		return lastMousePos;
	}

	bool* getKeyState() {
		return keyState;
	}

	glm::vec3 getCameraPos() {
		return cameraPos;
	}

	float getPitch() const {
		return pitch;
	}

	float getRoll() const {
		return roll;
	}

	float getYaw() const {
		return yaw;
	}

	float getScrollYoffset() const {
		return scrollYoffset;
	}

	glm::vec3 getCameraDirection() {
		return cameraDirection;
	}

protected:
	glm::ivec2 lastMousePos;
	float deltax;
	float deltay;
	float scrollYoffset;
	bool * mouseButtomState;
	bool * keyState;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	float yaw;
	float pitch;
	float roll;

	float distanceFromPlayer;
	float angleAroundPlayer;

	bool initDir;

};

#endif
