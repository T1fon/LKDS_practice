import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3



Rectangle
{
    id: thirdwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F5F5F5"

    signal buttonFirstWindowClicked()

    Rectangle
    {
        id: infopanel
        width: swidth * 92.8125
        height: sheight * 8.0469
        x: swidth * 3.2292
        y: sheight * 2.9688
        color: "white"

        TextEdit
        {
            width: parent.width
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

    Rectangle
    {
        id: buttongroup1
        width: swidth * 24.9479
        height: sheight * 24.8438
        x: swidth * 3.2292
        y: sheight * 16.7187
        color: "#D9D9D9"
        ButtonGroup
        {
            buttons: column.children
        }
        Column
        {
            id: column
            leftPadding: swidth * 2
            topPadding: sheight * 4

            RadioButton
            {
                id: meckanik
                checked: true
                text: qsTr("Механик")
                contentItem: Text
                {
                    text: meckanik.text
                    color: "red"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: sheight * 2
                    bottomPadding : 1 * swidth
                }
            }

            RadioButton
            {
                id: operator
                text: qsTr("Оператор")
                //color: "green"
                contentItem: Text
                {
                    text: operator.text
                    color: "green"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: sheight * 2
                    bottomPadding : 1 * swidth
                }
            }

            RadioButton
            {
                id: administrator
                text: qsTr("Администратор")
                contentItem: Text
                {
                    text: administrator.text
                    color: "blue"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: sheight * 2
                    bottomPadding : 1 * swidth
                }
            }
            RadioButton
            {
                id: developer
                text: qsTr("Разработчик")
                contentItem: Text
                {
                    text: developer.text
                    color: "#f6fa20"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: sheight * 2
                    bottomPadding : 1 * swidth
                }
            }
        }

    }

    Rectangle
    {
        id: buttongroup2
        width: swidth * 61.25
        height: sheight * 27.1875
        y: sheight * 16.7187
        x: swidth * 34.7916
        color: "#F5F5F5"
        Button
        {
            id: writebutton
            width: swidth * 27.9687
            height: sheight * 7.6562
            text: "Записать"
            background: Rectangle
            {
                color: "#D3B992"
            }
        }
        Button
        {
            id: checkbutton
            width: swidth * 27.9687
            height: sheight * 7.6562
            anchors.right: parent.right
            text: "Проверить"
            background: Rectangle
            {
                color: "#D3B992"
            }
        }
        Button
        {
            id: countbutton
            width: swidth * 27.9687
            height: sheight * 7.6562
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.verticalCenterOffset: -swidth * 0.25
            text: "Считать"
            background: Rectangle
            {
                color: "#D3B992"
            }
        }
        Button
        {
            id: cleanbutton
            width: swidth * 27.9687
            height: sheight * 7.6562
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.verticalCenterOffset: -swidth * 0.25
            text: "Отчистить"
            background: Rectangle
            {
                color: "#D3B992"
            }
        }
        Button
        {
            id: endbutton
            width: swidth * 27.9687
            height: sheight * 7.6562
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Завершить"
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                fouthwindow.buttonFirstWindowClicked()
            }
        }
    }

    Rectangle
    {
        id: log
        width: swidth * 93.5416
        height: sheight * 39.2187
        x: swidth * 3.2292
        y: sheight * 51.0156
        color: "#D9D9D9"
    }
}
