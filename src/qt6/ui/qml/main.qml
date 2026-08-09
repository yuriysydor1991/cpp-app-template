import QtQuick
import QtQuick.Controls 2.12
import QtQuick.Layouts

import components
import glarea 1.0

ApplicationWindow {
  visible: true

  width: 500
  height: 520
  minimumWidth: 400
  minimumHeight: 420

  ColumnLayout {
    anchors.fill: parent

    DefaultWelcome {
      Layout.fillWidth: true
      Layout.fillHeight: true
    }

    GLTriangleItem {
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.minimumHeight: 140
    }
  }
}
