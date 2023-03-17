import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15
import DatabaseManager 1.0
import SecWin 1.0
import "../SecondWindow/"



Rectangle
{

    id: secondwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F5F5F5"


    signal buttonMainWindowClicked()
    signal buttonThirdWindowClicked()
    signal send()



    Rectangle
    {
        width: swidth * 58.333333
        height: sheight * 6.09375
        color: "#F5F5F5"
        y: sheight * 2.969
        x: swidth * 3.125

       Rectangle
       {
           id: text_button
           width: swidth * 46.87
           height: sheight * 6.09375
           //y: sheight * 3.01204
           color: "white"
            TextEdit
            {
                id: text
                width: swidth * 46.87
                height: parent.height
                font.family: "Helvetica"
                font.pointSize: sheight * 2.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                color: "black"
                clip: true
                //максимальная длина не должна превышать 30

            }
       }

        Button
        {
            id: searchbutton
            height: parent.height
            width: swidth * 10.4166
            anchors.right: parent.right
            background: Rectangle
            {
                color: "#D3B992"
            }

            Text {
                id: name
                text: qsTr("Поиск")
                font.family: "Helvetica"
                font.pointSize: sheight * 2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

        }
    }
    Rectangle
    {
        id: secondwindow_table
        width: swidth * 58.3333
        height: sheight * 64.921875
        x: swidth * 3.125
        y: sheight * 11.796875
        visible: true
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 5

            TableModeler {
                id : tab
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: Controller_DatabaseManager {id:aa}
                columnWidths: [10 * swidth, 15 * swidth, 10 * swidth, 10 * swidth, 12 *swidth]
            }

        }
    }

    Dialog
    {


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
                       text: qsTr("Название компании")
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
                       text: qsTr("ИНН")
                       font.family: "Helvetica"
                       font.pointSize: swidth
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter

                   }
               }
           }
           Rectangle
           {
               id:e3
               height: sheight * 7.3333
               width: parent.width
               y: sheight * 20
               color: "grey"

               TextInput
               {
                   id: tE3
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
           Rectangle
           {
               id:e4
               height: sheight * 7.3333
               width: parent.width
               y: sheight * 29
               color: "grey"

               TextInput
               {
                   id: tE4
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
                       text: qsTr("Название города")
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
                    aa.recieveData(tE1.text, tE2.text, tE3.text, tE4.text);
                    tE1.clear()
                    tE2.clear()
                    tE3.clear()
                    tE4.clear()

                    add.close()

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
                    add.close()
                }
            }

        }
    }

    Rectangle
    {
        id: info
        width: swidth * 27.96875
        height: sheight * 36.1718
        x:swidth * 67.552
        y:sheight * 11.71875
        color: "red"

        Button
        {
            id: addcompany
            height: sheight * 7.65625
            width: parent.width
            anchors.bottom: parent.bottom
            text:"Добавить компанию"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                add.open()
            }
        }
    }

    Rectangle
    {
        id: travellmenu
        height: sheight * 16.5625
        width: swidth * 27.96875
        color: "#F5F5F5"
        //anchors.right: parent.right
        y: sheight * 60.15625
        x: swidth * 67.552

        Button
        {
            id:thirdwindow_button
            width: parent.width
            height: sheight * 7.65625
            text:"Продолжить"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                secondwindow.buttonThirdWindowClicked()
            }

        }
        Button
        {
            id:firstwindow_button
            width: parent.width
            height: sheight * 7.65625
            anchors.bottom: parent.bottom
            text:"Назад"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                secondwindow.buttonMainWindowClicked()
            }
        }
    }
}
