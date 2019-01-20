#include "pch.h"
#include "Renderer.h"

#include "GLCheck.h"

#include <glad/glad.h>

#include <application/Window.h>
#include <system/Log.h>


#include "Transform.h"
#include "Mesh.h"
#include "Vertex.h"


namespace tk {
GLfloat vertices[] =
    {-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f};

GLuint indices[] = {0, 1, 2, 0, 2, 3};

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
    m_mainShader.load("res/shaders/default2D.vert", "res/shaders/default2D.frag");
   // m_mainShader.enable();

    Matrix4f model(1.0f);  // Should translate, rotate and scale using drawable properties

    Matrix4f view(1.0f);

    Matrix4f projection(1.0f);
    projection = maths::matrix::ortho(0.0f, (float)m_attachedWindow->getWidth(), 0.0f, (float)m_attachedWindow->getHeight());

    m_mainShader.setUniformMatrix4fv("modelMat", model);
    m_mainShader.setUniformMatrix4fv("viewMat", view);
    m_mainShader.setUniformMatrix4fv("projectionMat", projection);

    //m_mainShader.disable();

    Mesh m;
    m.addVertex({{-1.0f, -1.0f, 0.0f}, Color(0, 255, 0)});
    m.addVertex({{1.0f, -1.0f, 0.0f}, Color(255, 0, 0)});
    m.addVertex({{1.0f, 1.0f, 0.0f}, Color(0, 0, 255)});
    m.addVertex({{-1.0f, 1.0f, 0.0f}, Color(0, 0, 0, 0)});

    /*
    glCheck(glGenVertexArrays(1, &vao));
    glCheck(glGenBuffers(1, &vbo));
    glCheck(glGenBuffers(1, &ebo));

    glCheck(glBindVertexArray(vao));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    glCheck(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0));
    glCheck(glEnableVertexAttribArray(0));

    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    glCheck(glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, false, 0, (void*)0));
    glCheck(glEnableVertexAttribArray(1));

    glCheck(glBindVertexArray(0));
	*/

    glCheck(glGenVertexArrays(1, &vao));
    glCheck(glGenBuffers(1, &vbo));
    glCheck(glGenBuffers(1, &ebo));

    glCheck(glBindVertexArray(vao));

    auto v = m.getData();

    for (auto& i : v)
        LOG_TRACE(i);

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    glCheck(glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), v.data(), GL_STATIC_DRAW));

    glCheck(glVertexAttribPointer(0, 3, GL_FLOAT, false, (3 + 4 + 2) * sizeof(float), (void*)0));  // Vertices positions
    glCheck(glEnableVertexAttribArray(0));
    glCheck(glVertexAttribPointer(1, 4, GL_FLOAT, false, (3 + 4 + 2) * sizeof(float), (void*)(sizeof(float) * 3)));  // Colors
    glCheck(glEnableVertexAttribArray(1));
    glCheck(glVertexAttribPointer(2, 2, GL_FLOAT, false, (3 + 4 + 2) * sizeof(float), (void*)(sizeof(float) * (3 + 4))));  // Textures
    glCheck(glEnableVertexAttribArray(2));

    LOG_INFO("{}, {}, {}", sizeof(Vertex), sizeof(Vector3f), sizeof(Vector3f) + sizeof(Vector4f));

    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

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

    Vector3f position((float)m_attachedWindow->getWidth() / 2.0f, (float)m_attachedWindow->getHeight() / 2.0f, 0.0f);
    Vector3f rotation = {0.0f, 0.0f, (float)glfwGetTime()};
    Vector3f size(100.0f, 100.0f, 0.0f);

    Transform t(position, rotation, size);
    t.setCenter({0.0f, 0.0f, 0.0f});

    Matrix4f model(1.0f);
    model = maths::matrix::translate(model, position);  // Place the object in the world

    model = maths::matrix::rotate(model, t.rotation.x, Vector3f(1.0f, 0.0f, 0.0f));  // Rotate the object around the "model origin"
    model = maths::matrix::rotate(model, t.rotation.y, Vector3f(0.0f, 1.0f, 0.0f));
    model = maths::matrix::rotate(model, t.rotation.z, Vector3f(0.0f, 0.0f, 1.0f));

    model = maths::matrix::translate(model, t.getCenter());  // Move the object to be fake a rotation center
    model = maths::matrix::scale(model, size);  // Scale the object accordingly

    m_mainShader.setUniformMatrix4fv("modelMat", model);

    glCheck(glBindVertexArray(vao));
    glCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0));
    glCheck(glBindVertexArray(0));

    m_mainShader.disable();
}

// private:

}  // namespace tk