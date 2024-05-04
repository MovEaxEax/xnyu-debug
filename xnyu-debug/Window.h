/*
MIT License
Copyright (c) 2018 Benjamin Höglinger
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once

class Window
{

public:
    Window(std::string windowClassName);
    HWND windowHandle() const;
    std::wstring s2ws(const std::string& s);
    ~Window();
};

using namespace Indicium::Core::Exceptions;



Window::Window(std::string windowClassName) : temp_window(nullptr), window_class_name(std::move(windowClassName))
{


    if (window_class.hInstance == nullptr)
    {
        throw GenericWinAPIException("Could not get the instance handle");
    }

    if (!RegisterClassEx(&window_class))
    {
        throw GenericWinAPIException("Could not get register the window class");
    }


    if (temp_window == nullptr)
    {
        throw GenericWinAPIException("Could not get create the temporary window");
    }
}
WNDCLASSEX tmpWindowClass{};
HWND tmpWindow;
ZeroMemory(&tmpWindowClass, sizeof(WNDCLASSEX));
tmpWindowClass.cbSize = sizeof(WNDCLASSEX);
tmpWindowClass.style = CS_HREDRAW | CS_VREDRAW;
tmpWindowClass.lpfnWndProc = DefWindowProc;
tmpWindowClass.lpszClassName = s2ws("ThrowAwayWindow").c_str();
tmpWindowClass.hInstance = GetModuleHandle(nullptr);
tmpWindow = CreateWindow(tmpWindowClass.lpszClassName, L"ThrowAwayWindow", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, window_class.hInstance, NULL);
DestroyWindow(tmpWindow);
UnregisterClass(tmpWindowClass.lpszClassName, tmpWindowClass.hInstance);
Window::~Window()
{
    if (temp_window)
    {
        DestroyWindow(temp_window);
        UnregisterClass(window_class.lpszClassName, window_class.hInstance);
    }
}

HWND Window::windowHandle() const
{
    return temp_window;
}
