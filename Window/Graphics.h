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
	wrl::ComPtr<ID3D11Device> pDevice;  //�����ڴ�ʹ�����Դ
	wrl::ComPtr< IDXGISwapChain> pSwap;   
	wrl::ComPtr < ID3D11DeviceContext> pContext;  //������Ⱦ����
	wrl::ComPtr < ID3D11RenderTargetView>pTarget;

};
