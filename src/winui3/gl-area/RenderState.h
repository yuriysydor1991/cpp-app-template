#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_RENDERSTATE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_RENDERSTATE_CLASS_H

#include <d3d11.h>
#include <dxgi1_2.h>

#include "src/winui3/winui3_includes.h"

namespace winui3::gl_area
{

/**
 * @brief The Direct3D 11 device and swap chain backing a SwapChainPanel.
 *
 * Kept behind a shared_ptr captured by the panel SizeChanged handler, so its
 * lifetime is tied to the panel (the visual tree), not to the GLTriangleArea
 * wrapper.
 */
class RenderState
{
 public:
  /// @brief Creates the Direct3D device and its immediate context once.
  void ensure_device();

  /// @brief (Re)creates the swap chain of the given size, bound to the panel.
  void create_swapchain(
      const winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel& panel,
      float width, float height);

  /// @brief Clears the back buffer to black and presents it; add your own
  /// Direct3D draw commands here.
  void render();

 private:
  winrt::com_ptr<ID3D11Device> device;
  winrt::com_ptr<ID3D11DeviceContext> context;
  winrt::com_ptr<IDXGISwapChain1> swap_chain;
  winrt::com_ptr<ID3D11RenderTargetView> rtv;
};

}  // namespace winui3::gl_area

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_RENDERSTATE_CLASS_H
