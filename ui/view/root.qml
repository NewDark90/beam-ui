import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import QtQuick.Window 2.9
import "controls"
import Beam.Wallet 1.0

Window  {
    id: appWindow
    property alias source: rootLoader.source
    flags: Qt.Window | Qt.WindowFullscreenButtonHint
    title: BeamGlobals.getAppName()

    function setMinMax () {
        var wlimit = appWindow.screen.width
        var hlimit = appWindow.screen.height - 80
        var wmin = Math.min(1024, wlimit)
        var hmin = Math.min(852, hlimit)

        appWindow.minimumWidth = wmin
        appWindow.minimumHeight = hmin

        if(appWindow.visibility != ApplicationWindow.Maximized) {
            if (appWindow.width == 0) appWindow.width = wmin
            if (appWindow.width > wlimit) appWindow.width = wlimit
            if (appWindow.height == 0) appWindow.height = hmin
            if (appWindow.height > hlimit) appWindow.height = hlimit
        }
    }

    onScreenChanged: function() {
        appWindow.setMinMax()
    }

    Component.onCompleted: function() {
        appWindow.setMinMax();
    }

    SFFontLoader {}
    
    Popup {
        id: notifications
        closePolicy: Popup.NoAutoClose
        palette.window : Style.background_main
		MessagesViewModel {id: viewModel}

        parent: Overlay.overlay
        width: parent.width
        height: Math.min(100, viewModel.messages.length * 30 + 10)
        clip: true
        visible:  viewModel.messages.length > 0
        background: Item {
            anchors.fill: parent
            Rectangle {
                color: "red"
                opacity: 0.4
                anchors.fill: parent
            }
            ListView {
                id: sampleListView
                anchors.fill: parent
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                //spacing: 4
                clip: true
                model: viewModel.messages

                delegate: RowLayout {
                    width: parent.width
                    height: 30

                    SFText {
                        Layout.fillWidth: true
                        Layout.leftMargin: 30
                        Layout.minimumWidth: 100
                        Layout.alignment: Qt.AlignVCenter
                        text: modelData
                        font.pixelSize: 14
                        color: Style.content_main
                        height: 16
                    }
                    CustomToolButton {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.minimumHeight: 20
                        Layout.minimumWidth: 20
                        Layout.rightMargin: 30
                        icon.source: "qrc:/assets/icon-save.svg"
                        text: qsTrId("settings-report-problem-save-log-button")
                        onClicked: viewModel.saveLogs()
                        font { 
                            family: "Proxima Nova"
                            pixelSize: 14
                            weight: Font.Bold
                            capitalization: Font.AllLowercase
                        }
                        visible: viewModel.enableSaveReport(index)
                    }
                    CustomToolButton {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.minimumHeight: 20
                        Layout.minimumWidth: 20
                        Layout.rightMargin: 30
                        icon.source: "qrc:/assets/icon-cancel.svg"
                        onClicked: viewModel.deleteMessage(index)
                        visible: viewModel.enableCloseMessage(index)
                    }
                }
            }
        }
    }

    Loader {
        id: rootLoader
        width: parent.width
        height: parent.height
	    focus: true
        source : "qrc:/start.qml"
        signal activated()
    }

    onActiveChanged: {
        BeamGlobals.setAppActive(this.active);

        if (this.active) {
            rootLoader.activated();
        }
    }
}
