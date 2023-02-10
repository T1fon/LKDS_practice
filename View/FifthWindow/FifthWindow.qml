import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle
{
    id: fifthwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F5F5F5"

    signal buttonFirstWindowClicked()

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
        id: table
        width: swidth * 58.3333
        height: sheight * 66.9531
        x: swidth * 3.125
        y: sheight * 11.796875
        color: "red"
    }

    Rectangle
    {
        id: buttoncase
        width: swidth * 27.9688
        height: sheight * 37.1875
        x: swidth * 66.7187
        y: sheight * 11.796875
        color: "#F5F5F5"
        Button
        {
            id: add
            width: parent.width
            height: sheight * 7.6563
            text:"Добавить"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
        }
        Button
        {
            id: redact
            width: parent.width
            height: sheight * 7.6563
            y: sheight * 9.5
            text:"Редактировать"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }

        }
        Button
        {
            id: delet
            width: parent.width
            height: sheight * 7.6563
            y: sheight * 19
            text:"Удалить"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }

        }
        Button
        {
            id: unload
            width: parent.width
            height: sheight * 7.6563
            anchors.bottom: parent.bottom
            text:"Выгрузить"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }

        }
    }
    Button
    {
        width: swidth * 27.9688
        height: sheight * 7.6563
        x: swidth * 66.5625
        y: sheight * 71.0937
        text:"Вернуться"
        font.family: "Helvetica"
        font.pointSize: sheight * 1.5
        background: Rectangle
        {
            color: "#D3B992"
        }
        onClicked:
        {
            fifthwindow.buttonFirstWindowClicked()
        }
    }
}
