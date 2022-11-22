#include <iostream>
#include <math.h>
#include "window/Window.h"
#include "renderer/Renderer.h"

int main() {
	std::cout << "Creating window!" << std::endl;

	Renderer *renderer = new Renderer();

	bool running = true;

	float count = 0.0;

	while (running) {
		if (!renderer->getWindow()->ProcessMessages()) {
			std::cout << "Closing window" << std::endl;

			running = false;
		}

		// render
		renderer->Draw_Gradient(0xFFFFFF, 0x000000, 0xFF0000, 0x9900FF);
		

		// display
		renderer->getWindow()->flipBuffers();

		Sleep(10);

		count += 0.000001;
	}


	return 0;
}