import QtQuick
import QtQuick.Controls 2.12

ApplicationWindow {
  visible: true

  width: 500
  height: 300
  minimumWidth: 400
  minimumHeight: 250

  Text {
    id: windowHeader

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top

    color: "black"
    font.pointSize: 20

    text: "Main Qt6 application"
  }

  Text {
    id: testExplanation

    anchors.horizontalCenter: windowHeader.horizontalCenter
    anchors.top: windowHeader.bottom

    color: "black"
    font.pointSize: 12

    text: "Register new resources in the src/qt6/resources.qrc file."
  }

  Image {
    width: 200
    height: 200

    anchors.horizontalCenter: testExplanation.horizontalCenter
    anchors.top: testExplanation.bottom

    source: "qrc:/ui/resources/images/kytok.org.ua-logo.png"
  }
}
