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
	void Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
	void Draw_Circle(unsigned int x1, unsigned int y1, unsigned int radius, unsigned int color);
	void Draw_Rect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);

private:
	Window* window;

};

