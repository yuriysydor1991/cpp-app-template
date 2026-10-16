pragma Singleton

import QtQuick

QtObject {
    // Resolved against this file, so the logo follows the PROJECT_URI resource
    // prefix of every QML module of the project.
    readonly property url mainImageSource: Qt.resolvedUrl("../resources/images/kytok.org.ua-logo.png")
}
