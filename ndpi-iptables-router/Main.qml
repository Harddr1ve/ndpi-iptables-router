import QtQuick 2.15
import QtQuick.Controls 2.15
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        id: interfacesList

        anchors {
            left: parent.left
        }
        height: parent.height
        width: 100
        model: NetworkInterfaceModel {}

        delegate: Text {
            text: model.name
        }
    }
    ListView {
        id: listView
        anchors {
            right: parent.right
            top: parent.top
        }
        width: 200
        height: parent.height
        model: ListModel {
            id: listModel
        }
    }

    Button {
        width: 50
        height: 25
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: {
            worker.packetProcessed.connect(function(info) {
                listModel.append({"text": info});})
            worker.start();
        }
    }
}
