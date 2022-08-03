#pragma once
#pragma comment(lib,"d3d11.lib")
#include <d3d11.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;

private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;

};
