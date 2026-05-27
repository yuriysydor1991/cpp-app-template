import QtQuick
import QtQuick.Layouts

/**
 * Default Qt6/QML system information view.
 *
 * Binds to the "systemInfo" context property published by the Qt6Initer - a
 * SystemInformation object populated by the native Qt D-Bus (Qt6::DBus) client
 * from the org.freedesktop.hostname1 (systemd-hostnamed) service. This is the
 * Qt6 framework counterpart of the sdbus-c++ based appSDBusCxxClient branch,
 * the difference being that the obtained data is shown right in the window
 * instead of being only logged.
 */
ColumnLayout {
  id: root

  spacing: 10

  // Returns a dash placeholder for the empty (unset) properties.
  function display(value) {
    return value && value.length > 0 ? value : "—"
  }

  Text {
    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
    Layout.fillWidth: true
    Layout.topMargin: 10

    horizontalAlignment: Text.AlignHCenter
    wrapMode: Text.WordWrap

    color: "black"
    font.pointSize: 16

    text: "General system information"
  }

  Text {
    Layout.alignment: Qt.AlignHCenter
    Layout.fillWidth: true

    horizontalAlignment: Text.AlignHCenter
    wrapMode: Text.WordWrap

    color: "#555555"
    font.pointSize: 9

    text: "Read over the system D-Bus from org.freedesktop.hostname1 "
          + "(systemd-hostnamed)"
  }

  GridLayout {
    Layout.alignment: Qt.AlignHCenter
    Layout.fillWidth: true
    Layout.leftMargin: 24
    Layout.rightMargin: 24

    columns: 2
    columnSpacing: 18
    rowSpacing: 6

    visible: systemInfo.error.length === 0

    Text { text: "Hostname:"; font.bold: true; color: "black" }
    Text {
      text: root.display(systemInfo.hostname)
      color: "black"; Layout.fillWidth: true; elide: Text.ElideRight
    }

    Text { text: "Pretty hostname:"; font.bold: true; color: "black" }
    Text {
      text: root.display(systemInfo.prettyHostname)
      color: "black"; Layout.fillWidth: true; elide: Text.ElideRight
    }

    Text { text: "Operating system:"; font.bold: true; color: "black" }
    Text {
      text: root.display(systemInfo.operatingSystemPrettyName)
      color: "black"; Layout.fillWidth: true; elide: Text.ElideRight
    }

    Text { text: "Kernel name:"; font.bold: true; color: "black" }
    Text {
      text: root.display(systemInfo.kernelName)
      color: "black"; Layout.fillWidth: true; elide: Text.ElideRight
    }

    Text { text: "Kernel release:"; font.bold: true; color: "black" }
    Text {
      text: root.display(systemInfo.kernelRelease)
      color: "black"; Layout.fillWidth: true; elide: Text.ElideRight
    }

    Text { text: "Chassis:"; font.bold: true; color: "black" }
    Text {
      text: root.display(systemInfo.chassis)
      color: "black"; Layout.fillWidth: true; elide: Text.ElideRight
    }
  }

  Text {
    Layout.alignment: Qt.AlignHCenter
    Layout.fillWidth: true
    Layout.leftMargin: 24
    Layout.rightMargin: 24

    visible: systemInfo.error.length > 0

    horizontalAlignment: Text.AlignHCenter
    wrapMode: Text.WordWrap

    color: "darkred"
    font.pointSize: 11

    text: "Could not read the system information over D-Bus:\n"
          + systemInfo.error
  }

  // Pushes the content to the top of the window.
  Item { Layout.fillHeight: true; Layout.fillWidth: true }
}
