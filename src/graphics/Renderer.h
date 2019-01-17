#pragma once

#include "Shader.h"

namespace tk
{
class Window;

class Renderer
{
public:
	Renderer(const Window* attachedWindow);
	~Renderer();

	void init();
	void dispose();

	void drawNewFrame() const;

private:
	
private:
	const Window* m_attachedWindow;

	Shader m_mainShader;
	bool m_initialized = false;
};

} // namespace tk