import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15
import DatabaseManager 0.1



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
    signal buttonCHangeTableToThirdClicked()


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
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: Controller_DatabaseManager {}
                columnWidths: [10 * swidth, 15 * swidth, 10 * swidth, 10 * swidth, 12 *swidth]
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
