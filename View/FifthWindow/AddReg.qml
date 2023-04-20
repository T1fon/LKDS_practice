import QtQuick 2.6
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15
import AllBase 1.0

Dialog
{
    property Controller_allBase c_ab: null
    property bool flagRedact: false

    signal redact

        id: add
        height: sheight * 51.875
        width: swidth * 46.666
        title: "Добавить компанию"
        x: 30 * swidth
        y: 20 * sheight
        contentItem: Rectangle
        {
            width: parent.width
            height: parent.height
           Rectangle
           {
               id:e1
               height: sheight * 7.3333
               width: parent.width
               y: sheight * 2
               color: "grey"

               TextInput
               {
                   id: tE1
                   height: parent.height
                   width: swidth * 23.313
                   font.family: "Helvetica"
                   font.pointSize: swidth * 1.5
                   color: "black"
                   topPadding: sheight * 2.5
                   leftPadding: swidth * 1.5
               }
               Rectangle
               {
                   height: parent.height
                   width: swidth * 15.5416
                   color: "red"
                   anchors.right: parent.right

                   Text {
                       text: qsTr("Номер региона")
                       font.family: "Helvetica"
                       font.pointSize: swidth
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter

                   }
               }
           }
           Rectangle
           {
               id:e2
               height: sheight * 7.3333
               width: parent.width
               y: sheight * 11
               color: "grey"

               TextInput
               {
                   id: tE2
                   height: parent.height
                   width: swidth * 23.313
                   font.family: "Helvetica"
                   font.pointSize: swidth * 1.5
                   color: "black"
                   topPadding: sheight * 2.5
                   leftPadding: swidth * 1.5
               }
               Rectangle
               {
                   height: parent.height
                   width: swidth * 15.5416
                   color: "red"
                   anchors.right: parent.right

                   Text {
                       text: qsTr("Название региона")
                       font.family: "Helvetica"
                       font.pointSize: swidth
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter

                   }
               }
           }

        }
        footer: Rectangle
        {
            width: parent.width
            height: sheight * 8
            Button
            {
                id: okbut
                width: swidth * 17
                height: sheight * 5
                x: swidth * 2
                y: sheight
                text: "Добавить"
                background: Rectangle
                {
                    color: "#D3B992"
                }
                onClicked:
                {
                    c_ab.addRegData(tE1.text, tE2.text, flagRedact);
                    tE1.clear()
                    tE2.clear()
                    flagRedact = false

                    add.close()
                    c_ab.refreshTable()

                }
            }
            Button
            {
                id: exbut
                width: swidth * 17
                height: sheight * 5
                x: swidth * 25
                y: sheight
                text: "Отмена"
                background: Rectangle
                {
                    color: "#D3B992"
                }
                onClicked:
                {
                    tE1.clear()
                    tE2.clear()
                    add.close()
                }
            }

        }
    onRedact:
    {
        tE1.text = c_ab.checkRegKodReg()
        tE2.text = c_ab.checkRegNameReg()
        flagRedact = true
    }
}
