#include <iostream>
#include <math.h>
#include "window/Window.h"
#include "renderer/Renderer.h"
#include <chrono>

#define TARGET_FPS 100

int main() {
	std::cout << "Creating window!" << std::endl;

	Renderer *renderer = new Renderer();

	bool running = true;

	float count = 0.0;

	

	while (running) {
		auto time = std::chrono::system_clock::now();

		long long time_start = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();

		if (!renderer->getWindow()->ProcessMessages()) {
			std::cout << "Closing window" << std::endl;

			running = false;
		}

		// render
		renderer->Draw_Gradient(0xFFFFFF, 0x000000, 0xFF0000, 0x9900FF);
		renderer->Draw_Line(100, 100, 200, 275, 0x000000);
		

		// display
		renderer->getWindow()->flipBuffers();

		time = std::chrono::system_clock::now();
		long long time_end = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
		long long frame_time = time_end - time_start;

		if ((1000 / TARGET_FPS) - frame_time > 0) {
			Sleep((1000 / TARGET_FPS) - frame_time);
		}
		

		count += 0.000001;

		// delete line in stdout
		std::cout << "\x1b[2K";
		std::cout << "\x1b[1A" << "\x1b[2K";
		std::cout << "\r";

		std::cout << "\x1b[2K";
		std::cout << "\x1b[1A" << "\x1b[2K";
		std::cout << "\r";

		std::cout << "\x1b[2K";
		std::cout << "\x1b[1A" << "\x1b[2K";
		std::cout << "\r";
		
		

		double fps = 1000 / (time_end - time_start);

		std::cout << "FPS: " << fps << std::endl;

		std::cout << "Frame time wanted: " << (1000 / TARGET_FPS) << std::endl;
		std::cout << "Frame time taken: " << frame_time << std::endl;
	}


	return 0;
}