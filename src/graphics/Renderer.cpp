#include "pch.h"
#include "Renderer.h"

#include "GLCheck.h"

#include <application/Window.h>
#include <system/Log.h>
#include <glad/glad.h>

namespace tk
{
GLfloat vertices[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3};

GLuint vao, vbo, ebo;

Renderer::Renderer(const Window *attachedWindow)
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
	m_mainShader.load("res/shaders/default2D.vert", "res/shaders/default2D.frag");
	m_mainShader.enable();

	Matrix4f model(1.0f); // Should translate, rotate and scale using drawable properties
	model = maths::matrix::translate(model, {(float)m_attachedWindow->getWidth() / 2.0f, (float)m_attachedWindow->getHeight() / 2.0f, 0.0f});
	model = maths::matrix::rotate(model, maths::toRadians(10.0f), Vector3f(0.0f, 0.0f, 1.0f));
	model = maths::matrix::scale(model, {100.0f, 100.0f, 0.0f});

	Matrix4f view(1.0f);

	Matrix4f projection(1.0f);
	projection = maths::matrix::ortho(0.0f, (float)m_attachedWindow->getWidth(), 0.0f, (float)m_attachedWindow->getHeight());

	m_mainShader.setUniformMatrix4fv("modelMat", model);
	m_mainShader.setUniformMatrix4fv("viewMat", view);
	m_mainShader.setUniformMatrix4fv("projectionMat", projection);

	m_mainShader.disable();

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

void Renderer::drawNewFrame()
{
	m_mainShader.enable();

	glCheck(glBindVertexArray(vao));
	glCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0));
	glCheck(glBindVertexArray(0));

	m_mainShader.disable();
}

// private:

} // namespace tk