#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include "Exception.h"
#include "Keyboard.h"



class Windows
{
public:
	class WindowException : public CatchException
	{
	public :
		WindowException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorSring() const noexcept;
	private:
		HRESULT hr;
	};


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

public:
	Keyboard Key;

private:
	int width;
	int height;
	HWND hWnd;

};










#define CHWND_EXCEPT(hr) Windows::WindowException(_LINE_,_FILE_,hr)