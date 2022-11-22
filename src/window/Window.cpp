#include "Window.h"
#include <iostream>

std::vector<HWND*> Window::hWndList; // window handle list
std::vector<Window*> Window::windowList; // window object list

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		RECT rect;
		GetClientRect(hWnd, &rect);
		Window* window = Window::HandleToWindow(&hWnd);

		if (!window) {
			break;
		}

		window->setWidth(rect.right - rect.left);
		window->setHeight(rect.bottom - rect.top);

		// std::cout << "Old memory: " << window->getBufferMemory() << std::endl;

		if (window->getBufferMemory()) {
			VirtualFree(window->getBufferMemory(), 0, MEM_RELEASE);
			window->setBufferMemory(nullptr);
		}

		if (window->getBackBufferMemory()) {
			VirtualFree(window->getBackBufferMemory(), 0, MEM_RELEASE);
			window->setBackBufferMemory(nullptr);
		}

		void* newMem = VirtualAlloc(0, window->getWidth() * window->getHeight() * sizeof(unsigned int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		void* newMem_back = VirtualAlloc(0, window->getWidth() * window->getHeight() * sizeof(unsigned int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		// std::cout << "New memory: " << newMem << std::endl;

		window->setBufferMemory(newMem);
		window->setBackBufferMemory(newMem_back);

		BITMAPINFO buffer_bitmap_info = window->getBufferBitmapInfo();

		buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
		buffer_bitmap_info.bmiHeader.biWidth = window->getWidth();
		buffer_bitmap_info.bmiHeader.biHeight = window->getHeight();
		buffer_bitmap_info.bmiHeader.biPlanes = 1;
		buffer_bitmap_info.bmiHeader.biBitCount = 32;
		buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;

		window->setBufferBitmapInfo(buffer_bitmap_info);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window() : m_hInstance(GetModuleHandle(nullptr)) {
	const wchar_t* CLASS_NAME = L"Win32 Window Class";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_VISIBLE | WS_SYSMENU | WS_BORDER | WS_OVERLAPPEDWINDOW;

	int width = 640;
	int height = 480;

	// create a rect object to handle the window size
	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	// use the width and height as the canvas size
	AdjustWindowRect(&rect, style, false);

	this->m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Win32 Game Engine", // title pointer for the window
		style,
		rect.left, 
		rect.top, 
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	this->width = width;
	this->height = height;
	this->buffer_memory = VirtualAlloc(0, this->width * this->height * sizeof(unsigned int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	this->back_buffer_memory = VirtualAlloc(0, this->width * this->height * sizeof(unsigned int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	this->buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
	this->buffer_bitmap_info.bmiHeader.biWidth = this->width;
	this->buffer_bitmap_info.bmiHeader.biHeight = this->height;
	this->buffer_bitmap_info.bmiHeader.biPlanes = 1;
	this->buffer_bitmap_info.bmiHeader.biBitCount = 32;
	this->buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;

	Window::hWndList.push_back(&this->m_hWnd);
	Window::windowList.push_back(this);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::Window(LPCWSTR window_name) {
	const wchar_t* CLASS_NAME = L"Win32 Window Class";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_VISIBLE | WS_SYSMENU | WS_BORDER | WS_OVERLAPPEDWINDOW;

	int width = 640;
	int height = 480;

	// create a rect object to handle the window size
	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	// use the width and height as the canvas size
	AdjustWindowRect(&rect, style, false);

	this->m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		window_name, // title pointer for the window
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	this->width = width;
	this->height = height;
	this->buffer_memory = VirtualAlloc(0, this->width * this->height * sizeof(unsigned int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	this->back_buffer_memory = VirtualAlloc(0, this->width * this->height * sizeof(unsigned int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	this->buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
	this->buffer_bitmap_info.bmiHeader.biWidth = this->width;
	this->buffer_bitmap_info.bmiHeader.biHeight = this->height;
	this->buffer_bitmap_info.bmiHeader.biPlanes = 1;
	this->buffer_bitmap_info.bmiHeader.biBitCount = 32;
	this->buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;

	Window::hWndList.push_back(&this->m_hWnd);
	Window::windowList.push_back(this);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"Joey's Window Class";
	UnregisterClass(CLASS_NAME, m_hInstance);

	VirtualFree(this->buffer_memory, 0, MEM_RELEASE);
	VirtualFree(this->back_buffer_memory, 0, MEM_RELEASE);

	for (size_t i = 0; i < Window::hWndList.size(); i++) {
		if (this->m_hWnd == *Window::hWndList.at(i)) {
			Window::hWndList.erase(Window::hWndList.begin() + i);
			Window::windowList.erase(Window::windowList.begin() + i);
			break; 
		}
	}
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

unsigned int Window::getWidth() {
	return this->width;
}

unsigned int Window::getHeight() {
	return this->height;
}

void Window::setWidth(unsigned int width) {
	this->width = width;
}

void Window::setHeight(unsigned int height) {
	this->height = height;
}

void* Window::getBufferMemory() {
	return this->buffer_memory;
}

void Window::setBufferMemory(void *buffer_memory) {
	this->buffer_memory = buffer_memory;
}

void* Window::getBackBufferMemory() {
	return this->back_buffer_memory;
}

void Window::setBackBufferMemory(void* back_buffer_memory) {
	this->back_buffer_memory = back_buffer_memory;
}

BITMAPINFO Window::getBufferBitmapInfo() {
	return this->buffer_bitmap_info;
}

void Window::setBufferBitmapInfo(BITMAPINFO buffer_bitmap_info) {
	this->buffer_bitmap_info = buffer_bitmap_info;
}

void Window::flipBuffers() {
	HDC hdc = GetDC(this->m_hWnd);
	void* temp = this->buffer_memory;
	this->buffer_memory = this->back_buffer_memory;
	this->back_buffer_memory = temp;

	StretchDIBits(hdc, 0, 0, this->width, this->height, 0, 0, this->width, this->height, this->buffer_memory, &this->buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}

void Window::setPixelRGB(unsigned int x, unsigned int y, unsigned int color) {
	unsigned int* pixel = (unsigned int *) this->back_buffer_memory + x + (y * this->width);
	*pixel = color;
}

unsigned int Window::getPixelRGB(unsigned int x, unsigned int y) {
	unsigned int* pixel = (unsigned int*) this->back_buffer_memory + x + (y * this->width);
	return *pixel;
}

Window *Window::HandleToWindow(HWND *hWnd) {
	for (size_t i = 0; i < Window::hWndList.size(); i++) {
		// std::cout << *hWnd << std::endl;
		// std::cout << *Window::hWndList.at(i) << std::endl;

		if (*hWnd == *Window::hWndList.at(i)) {
			// std::cout << Window::windowList.at(i)->getHeight() << std::endl;
			return Window::windowList.at(i);
		}
	}

	return nullptr;
}