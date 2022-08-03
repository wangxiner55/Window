#pragma once

#include <d3d11.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void Draw();

private:
	wrl::ComPtr<ID3D11Device> pDevice;  //分配内存和创建资源
	wrl::ComPtr< IDXGISwapChain> pSwap;   
	wrl::ComPtr < ID3D11DeviceContext> pContext;  //发布渲染命令
	wrl::ComPtr < ID3D11RenderTargetView>pTarget;

};
