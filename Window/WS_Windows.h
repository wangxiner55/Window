#pragma once
#include <iostream>
#include <string>
#include "Exception.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <sstream>
#include "Tool.h"
#include <optional>
#include "Graphics.h"
#include <memory>

using namespace std;


class WS_Windows
{
public:
	class DefaultException : public CatchException
	{
		using CatchException::CatchException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class WindowException : public DefaultException
	{
	public :
		WindowException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		//static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public DefaultException
	{
	public:
		DefaultException::DefaultException;
		const char* GetType() const noexcept override;
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
	WS_Windows(int width, int height, const wchar_t* name) noexcept;
	~WS_Windows();
	WS_Windows(const WS_Windows&) = delete;
	WS_Windows& operator = (const WS_Windows&) = delete;
	void SetWindowName(const std::string& name);
	void SetWindowNameZN(const std::string& name);
	static std::optional<int> ProcessMessages();
	
	Graphics& Gfx();

private:
	static LRESULT CALLBACK HandleMegSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMegThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMeg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
	Keyboard Key;
	Mouse mouse;
	Tool tool;

private:
	int width;
	int height;
	HWND hWnd;
	unique_ptr<Graphics> pGfx;
	
};


#define CHWND_EXCEPT(hr) WS_Windows::WindowException(_LINE_,_FILE_,hr)