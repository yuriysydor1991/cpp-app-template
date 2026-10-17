#include "src/winui3/gl-area/GLTriangleArea.h"

#include <memory>

#include "src/log/log.h"
#include "src/winui3/gl-area/RenderState.h"

namespace mux = winrt::Microsoft::UI::Xaml;
namespace muxc = winrt::Microsoft::UI::Xaml::Controls;

namespace winui3::gl_area
{

GLTriangleArea::GLTriangleArea()
    : swap_panel{muxc::SwapChainPanel{}}, state{std::make_shared<RenderState>()}
{
  // (Re)build the Direct3D swap chain whenever the panel gets a real size and
  // draw a frame. SizeChanged also fires for the initial layout pass, which is
  // when the device and swap chain are first created. The handler captures the
  // shared state (so rendering survives this wrapper) and takes the panel from
  // the event sender (so the state never references the panel back -> no
  // cycle). DPI/composition-scale handling is omitted to keep this starting
  // point minimal.
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
