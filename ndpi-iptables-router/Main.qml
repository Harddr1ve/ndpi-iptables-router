import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: root

    visible: true
    width: 1024
    height: 768
    title: qsTr("nDPI ipTables Router")
    header: Rectangle {
        id: header

        height: parent.height * 0.1
        color: "Grey"

        ComboBox {
            id: interfacesDropDown

            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            width: parent.width * 0.2
            model: networkInterfaceModel
            onCurrentValueChanged: {
                console.log(interfacesDropDown.currentIndex)
                networkInterfaceModel.handleModelItem(interfacesDropDown.currentIndex)
            }
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
    footer: Rectangle {
        height: parent.height * 0.1
        color: "Gray"

        TextField {
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
            onClicked: {
                console.log("execute")
                commandRunner.runCommand(inputIptablesCommand.text)
                commandRunner.commandFinished.connect(function (output){
                    console.log(output)
                })
            }
        }
    }

    Component.onCompleted: {
        commandRunner.commandFinished.connect(function(output) {
            outputField.text = outputField.text + "\n" + output;
        });
    }

    Rectangle {
        id: rectTopWindow

        height: parent.height * 0.04
        width: parent.width
        anchors.bottom: rectOutputArea.top
        color: "DarkGrey"

        Button {
            id: buttonMinimize

            property bool isExpand: true

            width: parent.width * 0.08
            height: parent.height * 0.8
            anchors {
                left: parent.left
                leftMargin: parent.width * 0.02
                verticalCenter: parent.verticalCenter
            }
            text: isExpand ? "Minimize" : "Maximize"
            onClicked: {
                if (isExpand) {
                    animateMinimize.start()
                    isExpand = !isExpand
                } else {
                    animateMaximize.start()
                    isExpand = !isExpand
                }
            }
        }
        Text {
            anchors.centerIn: parent
            text: "Command output panel"
        }
    }
    Rectangle {
        id: rectOutputArea

        height: parent.height * 0.3
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        color: "Black"

        ScrollView {
            anchors.top: parent.rop
            width: parent.width
            height: parent.height

            TextArea {
                id: outputField

                readOnly: true
            }
        }

        PropertyAnimation {
            id: animateMinimize

            target: rectOutputArea
            property: "height"
            to: 0
            duration: 300
        }
        PropertyAnimation {
            id: animateMaximize

            target: rectOutputArea
            property: "height"
            to: root.height * 0.3
            duration: 300
        }
    }
    TableView {
        id: tabletest

        clip: true
        columnSpacing: 5
        rowSpacing: 5
        anchors {
            top: header.bottom
            bottom: rectTopWindow.top
            left: parent.left
            right: parent.right
        }
        model: protocolModel
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

        visible: false
        anchors {
            top: header.bottom
            bottom: rectOutputArea.top
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
