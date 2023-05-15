import QtQuick 2.15
import QtQuick.Controls 2.15
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        anchors.fill: parent
        model: NetworkInterfaceModel {}

        delegate: Text {
            text: model.name
        }
    }
}
