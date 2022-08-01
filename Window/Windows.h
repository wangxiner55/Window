#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

class Windows
{
private:
	class windowClass
	{
	public:
		static const wchar_t* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		windowClass() noexcept;
		~windowClass();
		windowClass(const windowClass&) = delete;
		windowClass& operator = (const windowClass&) = delete;
		static constexpr const wchar_t* wndClassName = L"DX11";
		static windowClass wndClass;
		HINSTANCE hInst;
	};

public:
	Windows(int width, int height, const wchar_t* name) noexcept;
	~Windows();
	Windows(const Windows&) = delete;
	Windows& operator = (const Windows&) = delete;

private:
	static LRESULT CALLBACK HandleMegSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMegThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMeg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;

};