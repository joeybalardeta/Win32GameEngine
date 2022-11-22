#pragma once
#include "../window/Window.h"

class Renderer {
public:
	// constructors
	Renderer();
	Renderer(Window *window);

	// destructor
	~Renderer();

	Window* getWindow();


	// 2D rendering/drawing functions
	void Draw_Gradient(unsigned int color_top_left, unsigned int color_top_right, unsigned int color_bottom_left, unsigned int color_bottom_right);

private:
	Window* window;

};

