#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_GLTRIANGLEAREA_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_GLTRIANGLEAREA_CLASS_H

#include <memory>

#include "src/winui3/winui3_includes.h"

namespace winui3::gl_area
{

struct RenderState;  // Direct3D device + swap chain; defined in the .cpp

/**
 * @brief A minimal, self-contained GPU rendering canvas - the WinUI 3
 * counterpart of the GLArea widget on the other framework branches.
 *
 * WinUI 3 has no native OpenGL; its surface for custom GPU rendering is the
 * Microsoft.UI.Xaml.Controls.SwapChainPanel driven by Direct3D. This class owns
 * a SwapChainPanel, wires a Direct3D 11 swap chain to it through
 * ISwapChainPanelNative and clears the back buffer to black every frame,
 * leaving a blank canvas. Add your own Direct3D rendering commands inside
 * RenderState::render() (and create your resources in ensure_device()/
 * create_swapchain()) to draw a real scene.
 *
 * The Direct3D device and swap chain live in a RenderState kept alive by the
 * SwapChainPanel's SizeChanged handler, so rendering keeps working even after
 * this lightweight wrapper goes out of scope - as long as the panel() stays in
 * the visual tree.
 */
class GLTriangleArea
{
 public:
  GLTriangleArea();

  /// @brief The XAML element to place into the window content tree.
  winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel panel() const;

 private:
  winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel swap_panel{nullptr};
  std::shared_ptr<RenderState> state;
};

}  // namespace winui3::gl_area

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_GLTRIANGLEAREA_CLASS_H
