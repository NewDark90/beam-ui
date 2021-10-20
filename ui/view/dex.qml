import QtQuick          2.11
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4
import Beam.Wallet      1.0
import "controls"
import "wallet"
import "dex"

Item {
    id: control
    Layout.fillWidth:  true
    Layout.fillHeight: true

    DexViewModel {
        id: viewModel
    }

    //
    // Page Header (Title + Status Bar)
    //
    RowLayout {
        Title {
            //% "Swap"
            text: qsTrId("dex-title")
        }
        SvgImage {
            Layout.alignment: Qt.AlignLeft | Qt.AlignHCenter
            Layout.maximumHeight: 15
            Layout.maximumWidth: 51
            Layout.topMargin: 8
            source: "qrc:/assets/beta-label.svg"
        }
    }

    StatusBar {
        id: statusBar
        model: statusbarModel
        z: 33
    }

    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.topMargin: 30
            spacing: 20

            /*
            CustomButton {
                id: acceptOfferButton
                Layout.preferredWidth: 172
                Layout.preferredHeight: 32
                palette.button: Style.accent_outgoing
                palette.buttonText: Style.content_opposite
                font.pixelSize: 12
                icon.source: "qrc:/assets/icon-accept-offer.svg"
                //% "Accept offer"
                text: qsTrId("dex-accept-offer")
                onClicked: function () {
                }
            }
            */

            CustomButton {
                id: sendOfferButton
                Layout.preferredWidth: 172
                Layout.preferredHeight: 32
                palette.button: Style.accent_incoming
                palette.buttonText: Style.content_opposite
                font.pixelSize: 12
                icon.source: "qrc:/assets/icon-create-offer.svg"
                //% "Create offer"
                text: qsTrId("dex-create-ovver")
                onClicked: function () {
                }
            }
        }

        /*
        MarketPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            Layout.topMargin: 26
        }
        */

        AssetsPanel {
            id: assets
            Layout.topMargin: 20
            Layout.fillWidth: true

            Binding {
                target:    marketTable
                property:  "selectedAsset"
                value:     assets.selectedId
            }
        }

        Row {
            Layout.topMargin: 15
            Layout.bottomMargin: 15
            spacing: 15

            CustomButton {
                height: 28
                text: "Buy 10 DEMOX"
                onClicked: {
                    viewModel.buyBEAMX()
                }
            }

            CustomButton {
                height: 28
                text: "Sell 10 DEMOX"
                onClicked: {
                    viewModel.sellBEAMX()
                }
            }

            CustomButton {
                height: 28
                text: "Buy 10 NONE"
                onClicked: {
                    viewModel.buyNONE()
                }
            }

            CustomButton {
                height: 28
                text: "Sell 10 NONE"
                onClicked: {
                    viewModel.sellNONE()
                }
            }
        }

        MarketTable {
            id: marketTable
            Layout.fillWidth: true
            Layout.fillHeight: true
            viewModel: viewModel
        }
    }
}
