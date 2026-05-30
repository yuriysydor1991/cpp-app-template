#include "src/winui3/gl-area/GLTriangleArea.h"

#include <d3d11.h>
#include <dxgi1_2.h>
#include <microsoft.ui.xaml.media.dxinterop.h>

#include "src/log/log.h"

namespace mux = winrt::Microsoft::UI::Xaml;
namespace muxc = winrt::Microsoft::UI::Xaml::Controls;

namespace winui3::gl_area
{

// The Direct3D device + swap chain backing a SwapChainPanel. Kept behind a
// shared_ptr captured by the panel's SizeChanged handler so its lifetime is
// tied to the panel (the visual tree), not to the GLTriangleArea wrapper.
struct RenderState
{
  winrt::com_ptr<ID3D11Device> device;
  winrt::com_ptr<ID3D11DeviceContext> context;
  winrt::com_ptr<IDXGISwapChain1> swap_chain;
  winrt::com_ptr<ID3D11RenderTargetView> rtv;

  void ensure_device();
  void create_swapchain(const muxc::SwapChainPanel& panel, float width,
                        float height);
  void render();
};

void RenderState::ensure_device()
{
  if (device) {
    return;
  }

  // BGRA support is required to drive a composition (SwapChainPanel) swap chain.
  const UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

  winrt::check_hresult(D3D11CreateDevice(
      nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0,
      D3D11_SDK_VERSION, device.put(), nullptr, context.put()));
}

void RenderState::create_swapchain(const muxc::SwapChainPanel& panel,
                                   float width, float height)
{
  if (!device) {
    return;
  }

  // Drop the view onto the old back buffer before (re)sizing the chain.
  rtv = nullptr;

  if (swap_chain) {
    context->OMSetRenderTargets(0, nullptr, nullptr);
    winrt::check_hresult(swap_chain->ResizeBuffers(
        2, static_cast<UINT>(width), static_cast<UINT>(height),
        DXGI_FORMAT_B8G8R8A8_UNORM, 0));
  }
  else {
    const auto dxgi_device = device.as<IDXGIDevice>();
    winrt::com_ptr<IDXGIAdapter> adapter;
    winrt::check_hresult(dxgi_device->GetAdapter(adapter.put()));
    winrt::com_ptr<IDXGIFactory2> factory;
    winrt::check_hresult(
        adapter->GetParent(__uuidof(IDXGIFactory2), factory.put_void()));

    DXGI_SWAP_CHAIN_DESC1 desc{};
    desc.Width = static_cast<UINT>(width);
    desc.Height = static_cast<UINT>(height);
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = 2;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;

    winrt::check_hresult(factory->CreateSwapChainForComposition(
        device.get(), &desc, nullptr, swap_chain.put()));

    // Bind the swap chain to the XAML SwapChainPanel so it composes on screen.
    const auto native = panel.as<ISwapChainPanelNative>();
    winrt::check_hresult(native->SetSwapChain(swap_chain.get()));
  }

  // (Re)create the render target view onto the current back buffer.
  winrt::com_ptr<ID3D11Texture2D> back_buffer;
  winrt::check_hresult(swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                                             back_buffer.put_void()));
  winrt::check_hresult(
      device->CreateRenderTargetView(back_buffer.get(), nullptr, rtv.put()));
}

void RenderState::render()
{
  if (!context || !rtv || !swap_chain) {
    return;
  }

  ID3D11RenderTargetView* const targets[] = {rtv.get()};
  context->OMSetRenderTargets(1, targets, nullptr);

  const float black[4] = {0.0F, 0.0F, 0.0F, 1.0F};
  context->ClearRenderTargetView(rtv.get(), black);

  // Blank black canvas. Enter your own Direct3D draw commands below to render
  // a scene into the SwapChainPanel back buffer.
  LOGI("WinUI 3 GLTriangleArea blank frame rendered - add your Direct3D "
       "commands in RenderState::render()");

  winrt::check_hresult(swap_chain->Present(1, 0));
}

GLTriangleArea::GLTriangleArea()
    : swap_panel{muxc::SwapChainPanel{}}, state{std::make_shared<RenderState>()}
{
  // (Re)build the Direct3D swap chain whenever the panel gets a real size and
  // draw a frame. SizeChanged also fires for the initial layout pass, which is
  // when the device and swap chain are first created. The handler captures the
  // shared state (so rendering survives this wrapper) and takes the panel from
  // the event sender (so the state never references the panel back -> no cycle).
  // DPI/composition-scale handling is omitted to keep this starting point minimal.
  const auto st = state;
  swap_panel.SizeChanged(
      [st](const winrt::Windows::Foundation::IInspectable& sender,
           const mux::SizeChangedEventArgs& args) {
        const auto size = args.NewSize();
        if (size.Width <= 0 || size.Height <= 0) {
          return;
        }
        const auto panel = sender.as<muxc::SwapChainPanel>();
        try {
          st->ensure_device();
          st->create_swapchain(panel, size.Width, size.Height);
          st->render();
        }
        catch (const winrt::hresult_error& ex) {
          LOGE("WinUI 3 GLTriangleArea Direct3D setup failed: "
               << winrt::to_string(ex.message()));
        }
      });
}

muxc::SwapChainPanel GLTriangleArea::panel() const { return swap_panel; }

}  // namespace winui3::gl_area
