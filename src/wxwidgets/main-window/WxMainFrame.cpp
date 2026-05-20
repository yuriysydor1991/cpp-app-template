#include "src/wxwidgets/main-window/WxMainFrame.h"

namespace wxwi::main_window
{

WxMainFrame::WxMainFrame(const helpers::WindowConfig& config)
    : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8(config.title()),
              wxDefaultPosition, wxSize(config.width(), config.height()))
{
  SetMinSize(wxSize(config.min_width(), config.min_height()));

  build_widgets(config);
}

void WxMainFrame::build_widgets(const helpers::WindowConfig& config)
{
  auto* panel = new wxPanel(this, wxID_ANY);
  auto* sizer = new wxBoxSizer(wxVERTICAL);

  auto* header = new wxStaticText(panel, wxID_ANY,
                                  wxString::FromUTF8(config.header_text()));
  auto* explanation = new wxStaticText(
      panel, wxID_ANY, wxString::FromUTF8(config.explanation_text()));

  wxFont headerFont = header->GetFont();
  headerFont.SetPointSize(headerFont.GetPointSize() + 6);
  headerFont.SetWeight(wxFONTWEIGHT_BOLD);
  header->SetFont(headerFont);

  sizer->AddStretchSpacer(1);
  sizer->Add(header, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
  sizer->Add(explanation, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
  sizer->AddStretchSpacer(1);

  panel->SetSizer(sizer);
}

}  // namespace wxwi::main_window
