import QtQuick
import QtQuick.Controls 2.12
import QtQuick.Layouts

import constants

ColumnLayout {  
  Text {
    id: windowHeader
    
    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
    Layout.fillWidth: true
    
    horizontalAlignment: Text.AlignHCenter
    elide: Text.ElideRight
    wrapMode: Text.WordWrap

    color: "black"
    font.pointSize: 20

    text: "The main Qt6/QML window example"
  }

  Text {
    id: testExplanation
    
    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
    Layout.fillWidth: true
    
    horizontalAlignment: Text.AlignHCenter
    elide: Text.ElideRight
    wrapMode: Text.WordWrap

    color: "black"
    font.pointSize: 12

    text: "Register new QML files in the appropriate CMakeLists.txt project files"
  }

  Image {
    id: mainWindowImage

    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
    Layout.fillHeight: true
    Layout.fillWidth: true
    
    fillMode: Image.PreserveAspectFit

    source: Constants.mainImageSource
  }
}
