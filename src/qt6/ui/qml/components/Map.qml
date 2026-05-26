import QtQuick
import QtWebEngine

WebEngineView {
  // The bundled page pulls Leaflet and OpenStreetMap tiles from the network.
  settings.localContentCanAccessRemoteUrls: true
  url: Qt.resolvedUrl("map.html")
}
