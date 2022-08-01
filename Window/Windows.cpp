#include "Windows.h"
#include "resource.h"


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
    wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 32, 32, 0));
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = GetName();
    wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, 0));
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


     /*********KeyBoard Message**********/
    case WM_KEYDOWN:
        Key.OnKeyPressed(static_cast<unsigned char>(wParam));
        break;
    case WM_KEYUP:
        Key.OnKeyReleased(static_cast<unsigned char>(wParam));
        break;
    case WM_CHAR:
        Key.OnChar(static_cast<unsigned char>(wParam));
        break;
    }
    /*********KeyBoard Message**********/


    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Windows::WindowException::WindowException(int line, const char* file, HRESULT hr) noexcept :CatchException(line, file), hr(hr)
{
}

const char* Windows::WindowException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << std::endl << "[Error Code]" << GetErrorCode() << std::endl << "[Description]" << GetErrorSring() << std::endl << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* Windows::WindowException::GetType() const noexcept
{
    return "Windows Error Exception";
}

std::string Windows::WindowException::TranslateErrorCode(HRESULT hr) noexcept
{
    char* pMsgBuf = nullptr;
    DWORD nMsgBuf = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
        , nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&pMsgBuf), 0, nullptr); // LPSTR -> LPSWTR

    if (nMsgBuf == 0)
    {
        return "Unidentified error code";
    }
    std::string errorString = pMsgBuf;
    LocalFree(pMsgBuf);
    return errorString;
}

HRESULT Windows::WindowException::GetErrorCode() const noexcept
{
    return hr;
}

std::string Windows::WindowException::GetErrorSring() const noexcept
{
    return TranslateErrorCode(hr);
}
