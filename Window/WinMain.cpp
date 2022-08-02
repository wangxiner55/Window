#include "Windows.h"
#include <sstream>




LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(1001);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, L"Surprise");
		}
	case WM_CHAR:
		{
		static std::wstring title;
		title.push_back(char(wParam));
		SetWindowText(hWnd, title.c_str());
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(lParam);
			std::ostringstream oss;
			oss << "(" << pt.x << "," << pt.y << ")";

			std::string os = oss.str().c_str();
			std::wstring ws;
			ws.assign(os.begin(), os.end());
			SetWindowText(hWnd, ws.c_str());
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	Windows wnd(300, 300, L"Xiner");
	MSG msg;
	BOOL gResult;
	while (gResult =  GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (wnd.Key.KeyIsPressed(VK_MENU))
		{
			MessageBox(nullptr, L"Pressed", L"Pressed", MB_OKCANCEL);
		}
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}

}