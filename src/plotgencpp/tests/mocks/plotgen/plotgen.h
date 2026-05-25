#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGENCPP_TESTS_MOCK_PLOTGEN_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGENCPP_TESTS_MOCK_PLOTGEN_H

#include <algorithm>
#include <string>
#include <vector>

/**
 * @brief Minimal drop-in replacement for the PlotGenCpp public header used by
 * the plotgencpp component tests.
 *
 * It mirrors only the slice of the PlotGen API that PlotGenCppController.cpp
 * touches, so the real controller source compiles and runs against it without
 * the PlotGenCpp/SFML libraries - and, crucially, without PlotGen::show()
 * opening an on-screen window, which is impossible on a headless CI agent.
 *
 * Every drawing call is a no-op; the calls a test wants to assert on (the
 * data-feeding plot() and the render-triggering show(), plus the window
 * construction) are tallied into the static counters below. Call
 * PlotGen::reset() between tests.
 */

// Minimal stand-in for the SFML sf::Color referenced by PlotGen::Style.
namespace sf
{

struct Color
{
  unsigned char r{0};
  unsigned char g{0};
  unsigned char b{0};
  unsigned char a{255};

  Color() = default;
  Color(unsigned char red, unsigned char green, unsigned char blue,
        unsigned char alpha = 255)
      : r{red}, g{green}, b{blue}, a{alpha}
  {
  }

  static const Color Blue;
  static const Color Red;
  static const Color Green;
};

inline const Color Color::Blue{0, 0, 255};
inline const Color Color::Red{255, 0, 0};
inline const Color Color::Green{0, 255, 0};

}  // namespace sf

class PlotGen
{
 public:
  struct Style
  {
    sf::Color color;
    double thickness{2.0};
    std::string line_style{"solid"};
    std::string legend;
    std::string symbol_type{"none"};
    double symbol_size{6.0};
  };

  struct Figure
  {
    std::string title, xlabel, ylabel;
  };

  /// @brief Number of PlotGen windows constructed since the last reset().
  inline static unsigned int constructed{0};
  /// @brief Number of plot() invocations since the last reset().
  inline static unsigned int plot_calls{0};
  /// @brief Number of show() invocations since the last reset().
  inline static unsigned int show_calls{0};

  static void reset()
  {
    constructed = 0;
    plot_calls = 0;
    show_calls = 0;
  }

  PlotGen(unsigned int = 1200, unsigned int = 900, unsigned int = 1,
          unsigned int = 1)
  {
    ++constructed;
  }

  Figure& subplot(unsigned int, unsigned int) { return figure; }

  void set_title(Figure&, const std::string&) {}
  void set_xlabel(Figure&, const std::string&) {}
  void set_ylabel(Figure&, const std::string&) {}
  void set_axis_limits(Figure&, double, double, double, double) {}
  void grid(Figure&, bool = true, bool = false) {}
  void set_legend_position(Figure&, const std::string&) {}

  void plot(Figure&, const std::vector<double>&, const std::vector<double>&,
            const Style&)
  {
    ++plot_calls;
  }

  void circle(Figure&, double, double, double, const Style&) {}
  void text(Figure&, double, double, const std::string&, const Style&) {}

  void show() { ++show_calls; }

  void save(const std::string&) {}
  void save_svg(const std::string&) {}

 private:
  Figure figure;
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGENCPP_TESTS_MOCK_PLOTGEN_H
