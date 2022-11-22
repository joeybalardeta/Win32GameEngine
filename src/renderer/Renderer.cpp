#include "Renderer.h"
#include "../window/Window.h"
#include "../utils/Utils.h"
#include <iostream>
#include <assert.h>


Renderer::Renderer() {
	this->window = new Window();
}

Renderer::Renderer(Window* window) {
	this->window = window;
}

Renderer::~Renderer() {

}

Window* Renderer::getWindow()
{
	return this->window;
}

void Renderer::Draw_Gradient(unsigned int color_bottom_left, unsigned int color_bottom_right, unsigned int color_top_left, unsigned int color_top_right) {
	
	
	int r_base_hb = (color_bottom_left / 0x10000);
	int g_base_hb = (color_bottom_left % 0x10000) / 0x100;
	int b_base_hb = (color_bottom_left % 0x100) / 0x1;

	int r_diff_hb = r_base_hb - (color_bottom_right) / 0x10000;
	int g_diff_hb = g_base_hb - ((color_bottom_right % 0x10000) / 0x100);
	int b_diff_hb = b_base_hb - ((color_bottom_right % 0x100) / 0x1);

	int r_base_ht = (color_top_left / 0x10000);
	int g_base_ht = (color_top_left % 0x10000) / 0x100;
	int b_base_ht = (color_top_left % 0x100) / 0x1;

	int r_diff_ht = r_base_ht - (color_top_right) / 0x10000;
	int g_diff_ht = g_base_ht - ((color_top_right % 0x10000) / 0x100);
	int b_diff_ht = b_base_ht - ((color_top_right % 0x100) / 0x1);


	// std::cout << r_base_hb << ", " << g_base_hb << ", " << b_base_hb << std::endl;
	// std::cout << r_diff_hb << ", " << g_diff_hb << ", " << b_diff_hb << std::endl;

	// std::cout << std::endl;
	// std::cout << std::endl;

	// std::cout << r_base_ht << ", " << g_base_ht << ", " << b_base_ht << std::endl;
	// std::cout << r_diff_ht << ", " << g_diff_ht << ", " << b_diff_ht << std::endl;

	// std::cout << std::endl;
	// std::cout << std::endl;

	for (int i = 0; i < this->window->getWidth(); i++) {
		int r_new_b = r_base_hb - (r_diff_hb * 1.0 / this->window->getWidth()) * i;
		int g_new_b = g_base_hb - (g_diff_hb * 1.0 / this->window->getWidth()) * i;
		int b_new_b = b_base_hb - (b_diff_hb * 1.0 / this->window->getWidth()) * i;

		int r_new_t = r_base_ht - (r_diff_ht * 1.0 / this->window->getWidth()) * i;
		int g_new_t = g_base_ht - (g_diff_ht * 1.0 / this->window->getWidth()) * i;
		int b_new_t = b_base_ht - (b_diff_ht * 1.0 / this->window->getWidth()) * i;

		int r_new_diff = r_new_b - r_new_t;
		int g_new_diff = g_new_b - g_new_t;
		int b_new_diff = b_new_b - b_new_t;

		// std::cout << r_new_b << ", " << g_new_b << ", " << b_new_b << std::endl;
		// std::cout << r_new_t << ", " << g_new_t << ", " << b_new_t << std::endl;

		// std::cout << r_new_diff << ", " << g_new_diff << ", " << b_new_diff << std::endl;

		// std::cout << std::endl;

		for (int j = 0; j < this->window->getHeight(); j++) {
			int r_final = r_new_b - (r_new_diff * 1.0 / this->window->getHeight()) * j;
			int g_final = g_new_b - (g_new_diff * 1.0 / this->window->getHeight()) * j;
			int b_final = b_new_b - (b_new_diff * 1.0 / this->window->getHeight()) * j;

			// this->window->setPixelRGB(i, j, Utils::RGBtoHex(r_new_t, g_new_t, b_new_t));

			this->window->setPixelRGB(i, j, Utils::RGBtoHex(r_final, g_final, b_final));
		}
	}
}

void Renderer::Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color) {
	// make sure x-coordinates are on the screen
	assert(x1 >= 0 && x1 < this->window->getWidth());
	assert(x2 >= 0 && x2 < this->window->getWidth());

	// make sure y-coordinates are on the screen
	assert(y1 >= 0 && y1 < this->window->getHeight());
	assert(y2 >= 0 && y2 < this->window->getHeight());

	// make sure first set of coordinates are less than the second set
	assert(x1 < x2);
	assert(y1 < y2);


	double slope = ((y2 - y1) * 1.0) / ((x2 - x1) * 1.0);

	double multiplier = 0.0;

	while (true) {
		this->window->setPixelRGB(x1 + (int) (slope * multiplier * (x2 - x1)), y1 + (int)(slope * multiplier * (y2 - y1)), color);

		multiplier += 0.0001;

		if (x1 + (int)(slope * multiplier * (x2 - x1)) > x2) {
			break;
		}
	}
}

void Renderer::Draw_Circle(unsigned int x1, unsigned int y1, unsigned int radius, unsigned int color) {
	// make sure coordinates are on the screen
	assert(x1 >= 0 && x1 < this->window->getWidth());
	assert(y1 >= 0 && y1 < this->window->getHeight());

	

}

void Renderer::Draw_Rect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color) {
	// make sure x-coordinates are on the screen
	assert(x1 >= 0 && x1 < this->window->getWidth());
	assert(x2 >= 0 && x2 < this->window->getWidth());

	// make sure y-coordinates are on the screen
	assert(y1 >= 0 && y1 < this->window->getHeight());
	assert(y2 >= 0 && y2 < this->window->getHeight());

	// make sure first set of coordinates are less than the second set
	assert(x1 < x2);
	assert(y1 < y2);


	for (int i = 0; i < x2 - x1; i++) {
		for (int j = 0; j < y2 - y1; j++) {
			this->window->setPixelRGB(x1 + i, y2 + j, color);
		}
	}
}
