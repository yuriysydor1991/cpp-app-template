#include "src/plotgencpp/PlotGenCppController.h"

#include <cassert>
#include <cmath>
#include <memory>
#include <vector>

#include "plotgen.h"

#include "src/log/log.h"

namespace plotgencppi
{

bool PlotGenCppController::run(std::shared_ptr<app::ApplicationContext> ctx)
{
    assert(ctx != nullptr);

    if (ctx == nullptr) {
        LOGE("No valid context provided");
        return false;
    }

    LOGI("Your plot implementation goes here");

    return drawTheExamplePlot();
}

PlotGenCppControllerPtr PlotGenCppController::create()
{
    return std::make_shared<PlotGenCppController>();
}

bool PlotGenCppController::drawTheExamplePlot()
{
    static constexpr const unsigned int n = 100;
    static constexpr const unsigned int width = 1024;
    static constexpr const unsigned int height = 724;

    // Create an 800x600 window
    PlotGen plt(width, height);

    std::vector<double> x(n), y(n);

    std::generate(x.begin(), x.end(), [i = 0]() mutable { return i++ * 0.1 - 5.0; });
    std::generate(y.begin(), y.end(),
                    [xter = x.begin()]() mutable { return std::sin(*(xter++)) ; });
    
    // Configure and plot
    auto& fig = plt.subplot(0, 0);
    PlotGen::Style style;
    style.color = sf::Color::Blue;
    style.legend = "sin(x)";
    
    plt.set_title(fig, "Sine Wave Plot");
    plt.set_xlabel(fig, "x");
    plt.set_ylabel(fig, "sin(x)");
    plt.set_axis_limits(fig, -5, 5, -1.2, 1.2);
    plt.grid(fig, true, false);
    plt.plot(fig, x, y, style);
    
    // Position the legend in the top-left corner
    plt.set_legend_position(fig, "top-left");
    
    // Add a circle and text annotation
    PlotGen::Style circle_style;
    circle_style.color = sf::Color::Red;
    circle_style.thickness = 2.0;
    plt.circle(fig, 0, 0, 1.0, circle_style);
    
    PlotGen::Style text_style;
    text_style.color = sf::Color::Green;
    plt.text(fig, 0, 1.5, "Maximum value", text_style);
    
    // Uncomment to save as PNG/JPG and SVG
    // plt.save("sinusoid.png");
    // plt.save_svg("sinusoid.svg");

    // Display the plot
    plt.show();
    
    return true;
}

}  // namespace plotgencppi
