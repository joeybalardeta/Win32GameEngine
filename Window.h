#pragma once

#include <Windows.h>
#include <vector>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	BITMAPINFO buffer_bitmap_info;

	Window();

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

	BITMAPINFO getBufferBitmapInfo();

	void Draw();
	void SetPixelRGB(unsigned int x, unsigned int y, unsigned int color);
	unsigned int GetPixelRGB(unsigned int x, unsigned int y);

	static Window *HandleToWindow(HWND *hWnd);


private:
	static std::vector<HWND *> hWndList; // window handle list
	static std::vector<Window *> windowList; // window object list

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	void* buffer_memory;
	int width;
	int height;
	

};

