#include "window.h"

#include "../core/console/console.h"

using namespace blowbox::memory;

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Window* Window::Create(Allocator* allocator, const std::string& name, unsigned int width, unsigned int height)
	{
		return MemoryManager::Allocate<Window>(allocator, allocator, name, width, height);
	}

	//------------------------------------------------------------------------------------------------------
	Window::Window(Allocator* allocator, const std::string& name, unsigned int width, unsigned int height) :
		MObject(allocator),
		width_(width),
		height_(height),
		aspect_ratio_((float)width / (float)height)
	{
		WNDCLASSA wndclass;
		hinstance_ = GetModuleHandle(0);
		ZeroMemory(&wndclass, sizeof(WNDCLASSA));
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndclass.lpfnWndProc = WindowProc;
		wndclass.hInstance = hinstance_;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wndclass.lpszClassName = name.c_str();
		wndclass.cbWndExtra = sizeof(void*);
		wndclass.cbClsExtra = sizeof(WNDCLASSA);

		RegisterClassA(&wndclass);

		int style = WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_SIZEBOX;

		RECT client_rect;
		client_rect.left = client_rect.top = 0;
		client_rect.right = width;
		client_rect.bottom = height;

		AdjustWindowRect(&client_rect, style, FALSE);
		int actualWidth = client_rect.right - client_rect.left;
		int actualHeight = client_rect.bottom - client_rect.top;
		int x = GetSystemMetrics(SM_CXSCREEN) / 2 - actualWidth / 2;
		int y = GetSystemMetrics(SM_CYSCREEN) / 2 - actualHeight / 2;

		hwindow_ = CreateWindowA(wndclass.lpszClassName, name.c_str(), style, x, y, actualWidth, actualHeight, GetDesktopWindow(), NULL, wndclass.hInstance, this);

		ShowWindow(hwindow_, SW_SHOWNORMAL);
	}

	//------------------------------------------------------------------------------------------------------
	Window::~Window()
	{
		DestroyWindow(hwindow_);
	}

	//------------------------------------------------------------------------------------------------------
	LRESULT CALLBACK Window::WindowProc(HWND hwindow, UINT message, WPARAM wparam, LPARAM lparam)
	{
		if (message == WM_CREATE)
		{
			SetWindowLongPtrA(hwindow, GWLP_USERDATA, (LONG_PTR)(((LPCREATESTRUCT)lparam)->lpCreateParams));
			return DefWindowProcA(hwindow, message, wparam, lparam);
		}
		//Window* window = reinterpret_cast<Window*>(GetWindowLongPtrA(hwindow, GWLP_USERDATA));

		return DefWindowProcA(hwindow, message, wparam, lparam);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::ProcessMessages()
	{
		MSG msg;

		while (PeekMessageA(&msg, hwindow_, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);

			window_input_listener_(msg);
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	const HWND& Window::GetWindowHandle() const
	{
		return hwindow_;
	}
	
	//------------------------------------------------------------------------------------------------------
	const HINSTANCE& Window::GetWindowInstance() const
	{
		return hinstance_;
	}
	
	//------------------------------------------------------------------------------------------------------
	const unsigned int& Window::GetWidth() const
	{
		return width_;
	}
	
	//------------------------------------------------------------------------------------------------------
	const unsigned int& Window::GetHeight() const
	{
		return height_;
	}
	
	//------------------------------------------------------------------------------------------------------
	const float& Window::GetAspectRatio() const
	{
		return aspect_ratio_;
	}
	
	//------------------------------------------------------------------------------------------------------
	void Window::SetWindowInputListener(std::function<void(MSG message)> listener)
	{
		window_input_listener_ = listener;
	}
}