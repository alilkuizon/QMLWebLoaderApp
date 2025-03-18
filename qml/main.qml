import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    ColumnLayout {
        id: counterContainer
        spacing: 10
        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            color: "black"
            Text {
                text: viewModel.elapsedTime
                color: "white"
            }
        }

        Rectangle {
            id: button
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            color: "green"

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    console.log("Pressed")
                    viewModel.toggleTimer()
                }
            }
        }
    }

    ColumnLayout {
        anchors.top: counterContainer.bottom
        anchors.left: parent.left
        spacing: 10

        Button {
            text: "Fetch USB Devices"
            onClicked: {
                viewModel.fetchUSBDeviceList()
            }
        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100

            model: viewModel.devices

            delegate: Item {
                width: parent.width
                height: 40

                Text {
                    anchors.centerIn: parent
                    text: modelData
                }
            }
        }
    }
}
