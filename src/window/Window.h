#pragma once

#include <Windows.h>
#include <vector>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window {
public:
	Window();
	Window(LPCWSTR window_name);

	// deletes the copy constructor for Window
	Window(const Window &) = delete;

	// deletes the equals operation for Window
	Window &operator = (const Window &) = delete;
	~Window();

	bool ProcessMessages();

	unsigned int getWidth();
	unsigned int getHeight();

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);

	void* getBufferMemory();
	void setBufferMemory(void *buffer_memory);

	void* getBackBufferMemory();
	void setBackBufferMemory(void* back_buffer_memory);

	BITMAPINFO getBufferBitmapInfo();
	void setBufferBitmapInfo(BITMAPINFO buffer_bitmap_info);

	void flipBuffers();
	void setPixelRGB(unsigned int x, unsigned int y, unsigned int color);
	unsigned int getPixelRGB(unsigned int x, unsigned int y);

	static Window *HandleToWindow(HWND *hWnd);


private:
	BITMAPINFO buffer_bitmap_info;

	static std::vector<HWND *> hWndList; // window handle list
	static std::vector<Window *> windowList; // window object list

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	void* buffer_memory;
	void* back_buffer_memory;
	int width;
	int height;
	

};

