#include "Windows.h"


Windows::windowClass Windows::windowClass::wndClass;

const wchar_t* Windows::windowClass::GetName() noexcept
{
    return wndClassName;
}

HINSTANCE Windows::windowClass::GetInstance() noexcept
{
    return wndClass.hInst;
}

Windows::windowClass::windowClass() noexcept : hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX wc = {};

    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMegSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetInstance();
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = GetName();
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);

}

Windows::windowClass::~windowClass()
{
    UnregisterClass(wndClassName, GetInstance());
}

Windows::Windows(int width, int height, const wchar_t* name) noexcept
{
    RECT wr;
    wr.left = 100;
    wr.right = width + wr.left;
    wr.top = 100;
    wr.bottom = height + wr.top;
    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false);

    hWnd = CreateWindow(
        windowClass::GetName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, windowClass::GetInstance(), this
    );

    ShowWindow(hWnd, SW_SHOWDEFAULT);


}

Windows::~Windows()
{
    DestroyWindow(hWnd);
}

LRESULT WINAPI Windows::HandleMegSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Windows* const pWnd = static_cast<Windows*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Windows::HandleMegThunk));

        return pWnd->HandleMeg(hWnd, msg, wParam, lParam);

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Windows::HandleMegThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Windows* const pWnd = reinterpret_cast<Windows*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    return pWnd->HandleMeg(hWnd, msg, wParam, lParam);
}

LRESULT Windows::HandleMeg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(1001);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
