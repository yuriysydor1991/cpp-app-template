import QtQuick
import QtQuick.Controls 2.12
import QtQuick.Layouts
  
ColumnLayout {
  anchors.fill: parent
  
  Text {
    id: windowHeader
    
    Layout.fillWidth: true
    
    horizontalAlignment: Text.AlignHCenter

    color: "black"
    font.pointSize: 20

    text: "Main Qt6 application"
  }

  Text {
    id: testExplanation
    
    Layout.fillWidth: true
    
    horizontalAlignment: Text.AlignHCenter

    color: "black"
    font.pointSize: 12

    text: "Register new resources in the src/qt6/resources.qrc file."
  }

  Image {
    Layout.fillHeight: true
    Layout.alignment: Qt.AlignHCenter
    
    fillMode: Image.PreserveAspectFit

    source: "qrc:/ui/resources/images/kytok.org.ua-logo.png"
  }
}

