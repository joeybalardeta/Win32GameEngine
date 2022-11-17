#include <iostream>
#include "Window.h"

int main() {
	std::cout << "Creating window!" << std::endl;

	Window* window = new Window();

	bool running = true;

	unsigned int color = 0;

	while (running) {
		if (!window->ProcessMessages()) {
			std::cout << "Closing window" << std::endl;

			running = false;
		}

		// simulate
		for (size_t j = 0; j < window->getHeight(); j++) {
			for (size_t i = 0; i < window->getWidth(); i++) {
				window->SetPixelRGB(i, j, ((i * 0x000101) + (j * 0x010001)));
			}
		}
		color += 0xFF00000;

		// render 
		window->Draw();

		Sleep(1);
	}


	return 0;
}