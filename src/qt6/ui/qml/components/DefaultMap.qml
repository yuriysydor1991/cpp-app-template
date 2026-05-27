import QtQuick
import QtLocation
import QtPositioning

/**
 * Default Qt6/QML native map example.
 *
 * Renders OpenStreetMap raster tiles natively through the Qt Location module's
 * Map element (backed by the QtPositioning coordinate types) using the bundled
 * "osm" geo services plugin. Unlike the appQt6LeafLet branch there is no
 * embedded web engine here - the tiles are drawn directly by the Qt Quick
 * scene graph, which makes this the native counterpart of the Leaflet/WebView
 * based map branch.
 */
Map {
  id: defaultMap

  // The "osm" plugin ships with the Qt Location module and fetches raster
  // tiles from the OpenStreetMap tile servers over the network.
  plugin: Plugin {
    name: "osm"
  }

  // Centred on Kyiv, Ukraine - the very same coordinates the Leaflet based
  // appQt6LeafLet branch starts at.
  center: QtPositioning.coordinate(50.4501, 30.5234)
  zoomLevel: 12

  // Coordinate kept under the pinch centroid while a pinch-to-zoom gesture is
  // in progress (see the PinchHandler below).
  property geoCoordinate startCentroid

  PinchHandler {
    id: pinch
    target: null
    onActiveChanged: if (active) {
      defaultMap.startCentroid =
          defaultMap.toCoordinate(pinch.centroid.position, false)
    }
    onScaleChanged: (delta) => {
      defaultMap.zoomLevel += Math.log2(delta)
      defaultMap.alignCoordinateToPoint(defaultMap.startCentroid,
                                        pinch.centroid.position)
    }
  }

  WheelHandler {
    id: wheel
    // Zoom with the mouse wheel - one notch (120 angle-delta units) per level.
    onWheel: (event) => {
      defaultMap.zoomLevel += event.angleDelta.y / 120
    }
  }

  DragHandler {
    id: drag
    target: null
    // Pan the map by dragging it with the pointer.
    onTranslationChanged: (delta) => defaultMap.pan(-delta.x, -delta.y)
  }
}
