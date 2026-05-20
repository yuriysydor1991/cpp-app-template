import QtQuick
import QtCharts

/**
 * Default Qt6/QML ChartView example.
 *
 * The example data set represents an exponential growth curve y = exp(x) and
 * is borrowed from the appMatPlotxx and appPLplot template branches (both of
 * them plot an exponential function on a logarithmic scale). Here the very
 * same curve is rendered natively by the Qt6 QtCharts ChartView element with a
 * logarithmic Y axis so the exponent shows up as a straight line.
 */
ChartView {
  id: defaultChart

  title: "Exponential growth example: y = exp(X)"
  titleColor: "black"

  antialiasing: true
  legend.visible: true
  theme: ChartView.ChartThemeLight

  ValueAxis {
    id: axisX

    titleText: "X"
    min: 0.0
    max: 10.0
  }

  LogValueAxis {
    id: axisY

    titleText: "exp(X) (log scale)"
    base: 10.0
    min: 1.0
    max: 100000.0
  }

  LineSeries {
    id: expSeries

    name: "exp(X)"
    axisX: axisX
    axisY: axisY

    // Populate the series with the same exponential data set used by the
    // appPLplot branch: 100 points of y = exp(x) for x in [0.0, 10.0).
    Component.onCompleted: {
      for (var i = 0; i < 100; ++i) {
        var x = i * 0.1;
        expSeries.append(x, Math.exp(x));
      }
    }
  }
}
