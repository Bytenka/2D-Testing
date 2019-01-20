#version 330 core
layout (location = 0) in vec3 inVertexPos;
layout (location = 1) in vec4 inColorVal;
layout (location = 2) in vec2 inTexturePos;

out vec2 texturePos;
out vec4 colorVal;

uniform mat4 modelMat;          // From local to world
uniform mat4 viewMat;           // From world to camera
uniform mat4 projectionMat;     // From camera to screen

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(inVertexPos, 1.0);
    texturePos = inTexturePos;
    colorVal = inColorVal;
}