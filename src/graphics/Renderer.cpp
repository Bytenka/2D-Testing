#include "pch.h"
#include "Renderer.h"

#include "GLCheck.h"

#include <system/Log.h>
#include <glad/glad.h>

namespace tk
{
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f };

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3 };

GLuint vao, vbo, ebo;

Renderer::Renderer(const Window* attachedWindow)
	: m_attachedWindow(attachedWindow)
{

}


Renderer::~Renderer()
{
	if (m_initialized)
		LOG_CRITICAL("Renderer destructor called but resources were not freed. GPU memory leak");
}

// public:

void Renderer::init()
{
	m_mainShader.load("res/shaders/default.vert", "res/shaders/default.frag");

	glCheck(glGenVertexArrays(1, &vao));
	glCheck(glGenBuffers(1, &vbo));
	glCheck(glGenBuffers(1, &ebo));

	glCheck(glBindVertexArray(vao));

	glCheck(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	glCheck(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void *)0));
	glCheck(glEnableVertexAttribArray(0));

	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
	glCheck(glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, false, 0, (void *)0));
	glCheck(glEnableVertexAttribArray(1));

	glCheck(glBindVertexArray(0));

	m_initialized = true;
}

void Renderer::dispose()
{
	m_mainShader.dispose();

	glCheck(glDeleteBuffers(1, &ebo));
	glCheck(glDeleteBuffers(1, &vbo));
	glCheck(glDeleteBuffers(1, &vao));

	m_initialized = false;
}

void Renderer::drawNewFrame() const
{
	m_mainShader.enable();

	glCheck(glBindVertexArray(vao));
	glCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0));
	glCheck(glBindVertexArray(0));

	m_mainShader.disable();
}


// private:

} // namespace tk