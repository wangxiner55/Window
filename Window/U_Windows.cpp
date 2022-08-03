#include "U_Windows.h"
#include "resource.h"


U_Windows::windowClass U_Windows::windowClass::wndClass;

const wchar_t* U_Windows::windowClass::GetName() noexcept
{
    return wndClassName;
}

HINSTANCE U_Windows::windowClass::GetInstance() noexcept
{
    return wndClass.hInst;
}

U_Windows::windowClass::windowClass() noexcept : hInst(GetModuleHandle(nullptr))
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

U_Windows::windowClass::~windowClass()
{
    UnregisterClass(wndClassName, GetInstance());
}

U_Windows::U_Windows(int width, int height, const wchar_t* name) noexcept
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

    pGfx = std::make_unique<Graphics>(hWnd);

}

U_Windows::~U_Windows()
{
    DestroyWindow(hWnd);
}

void U_Windows::SetWindowName(const std::string& name)
{
    SetWindowText(hWnd, tool.StringToWstring(name).c_str());
}

void U_Windows::SetWindowNameZN(const std::string& name)
{
    SetWindowText(hWnd, tool.StringToWstringZN(name).c_str());
}

std::optional<int> U_Windows::ProcessMessages()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
        {
            return msg.wParam;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        

        
    }
    return {};
}

Graphics& U_Windows::Gfx()
{
    return *pGfx;
}

LRESULT WINAPI U_Windows::HandleMegSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        U_Windows* const pWnd = static_cast<U_Windows*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&U_Windows::HandleMegThunk));

        return pWnd->HandleMeg(hWnd, msg, wParam, lParam);

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI U_Windows::HandleMegThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    U_Windows* const pWnd = reinterpret_cast<U_Windows*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    return pWnd->HandleMeg(hWnd, msg, wParam, lParam);
}






LRESULT U_Windows::HandleMeg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(1001);
        return 0;
    case WM_KILLFOCUS:
        Key.ClearState();
        break;

        /*********KeyBoard Message**********/
    case WM_KEYDOWN:
        if (!(lParam & 0x40000000) || Key.AutoreapectIsEnable())
        {
            Key.OnKeyPressed(static_cast<unsigned char>(wParam));
        }break;
    case WM_KEYUP:
    {
        Key.OnKeyReleased(static_cast<unsigned char>(wParam));
        break; 
    }
    case WM_CHAR:
    {
        Key.OnChar(static_cast<unsigned char>(wParam));
        break; 
    }
    
    /*********KeyBoard Message**********/

    /***********Mouse Message**********/

    case WM_MOUSEMOVE:
    {
        POINTS pt = MAKEPOINTS(lParam);
        mouse.OnMouseMove(pt.x, pt.y);
    }
    case WM_LBUTTONDOWN:
    {   
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnLeftPressed(pt.x, pt.y);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightPressed(pt.x, pt.y);
        break;
    }
    case WM_LBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnLeftReleased(pt.x, pt.y);
        break;
    }
    case WM_RBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightReleased(pt.x, pt.y);
        break;
    }
    case WM_MOUSEWHEEL:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
        {
            mouse.OnWheelUp(pt.x, pt.y);
        }
        else if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
        {
            mouse.OnWheelDown(pt.x, pt.y);
        }
        break;
    }

    }
    /***********Mouse Message**********/

    return DefWindowProc(hWnd, msg, wParam, lParam);
}









U_Windows::WindowException::WindowException(int line, const char* file, HRESULT hr) noexcept :CatchException(line, file), hr(hr)
{
}

const char* U_Windows::WindowException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << std::endl << "[Error Code]" << GetErrorCode() << std::endl << "[Description]" << GetErrorSring() << std::endl << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* U_Windows::WindowException::GetType() const noexcept
{
    return "Windows Error Exception";
}

std::string U_Windows::WindowException::TranslateErrorCode(HRESULT hr) noexcept
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

HRESULT U_Windows::WindowException::GetErrorCode() const noexcept
{
    return hr;
}

std::string U_Windows::WindowException::GetErrorSring() const noexcept
{
    return TranslateErrorCode(hr);
}
