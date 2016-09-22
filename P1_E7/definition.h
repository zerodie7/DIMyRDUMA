/*
 * definition.h
 *
 *  Created on: 06/09/2016
 *      Author: rey
 */

#ifndef HEADERS_DEFINITION_H_
#define HEADERS_DEFINITION_H_

#include <glm/glm.hpp>
#include <GL/glew.h>

typedef struct _VertexColorText {

	_VertexColorText() {
	}

	_VertexColorText(glm::vec3 position, glm::vec3 color, glm::vec2 texCoord) {
		this->position = position;
		this->color = color;
		this->texCoord = texCoord;
	}

	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoord;
} VertexColorText;

#endif /* HEADERS_DEFINITION_H_ */
