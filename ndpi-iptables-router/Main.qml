import QtQuick 2.15
import QtQuick.Controls 2.15

import ProtocolModel 1.0
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("nDPI ipTables Router")

    footer: Rectangle {
        height: parent.height * 0.1
        color: "Gray"

        TextInput {
            id: inputIptablesCommand

            height: parent.height * 0.9
            width: parent.width *  0.8
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 5
            }
            text: "Input Command"
        }

        Button {
            id: buttonExecute

            implicitWidth: 100
            height: parent.height * 0.8
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 5
            }
            text: "Execute"
        }
    }

    Rectangle {
        id: header

        height: parent.height * 0.1
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        color: "Grey"

        ComboBox {
            id: interfacesDropDown

            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            width: parent.width * 0.2
            model: NetworkInterfaceModel {}
        }

        Button {
            id: btnStart

            property bool enabled: false

            width: 100
            height: 25
            anchors {
                left: interfacesDropDown.right
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }
            text: "Start"
            onClicked: {
                if (!enabled) {
                    console.log("Started")
                    enabled = !enabled
                    btnStart.text = "Stop"
                    worker.packetProcessed.connect(function(info) {
                        console.log(info)
                        listModelNDPI.append({"text": info});})
                    worker.start();
                } else {
                    console.log("quit")
                    enabled = !enabled
                    btnStart.text = "Start"
                    worker.stop()
                }
            }
        }
    }

    TableView {
        id: tabletest

        clip: true
        columnSpacing: 5
        rowSpacing: 5
        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        model: ProtocolModel {}

        delegate: Rectangle {
            implicitWidth: 150
            implicitHeight: 100
            Text {
                text: display
                anchors.centerIn: parent
            }
        }
        ScrollBar.vertical: ScrollBar {}
        ScrollBar.horizontal: ScrollBar {}
    }

    TableView {
        id: tableNDPI

        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        clip: true
        model: listModelNDPI
        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            border.width: 1

            Text {
                text: info
                anchors.centerIn: parent
            }
        }
    }

    ListModel {
        id: listModelNDPI
    }
}
