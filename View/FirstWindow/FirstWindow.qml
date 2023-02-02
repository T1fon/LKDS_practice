import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../SecondWindow/"


ApplicationWindow
{
    id: mainwindow
    width:800
    height: 600
    visible: true
    title: qsTr("Проект Арсений")
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F5F5F5"
    property int defMargin: 10

    StackView
    {
        id: stackview
        anchors.fill: parent
        initialItem: firstwindow
    }

    Rectangle
    {
        id: firstwindow
        width:parent.width
        height: parent.height
        color: "#F5F5F5"
        signal button1Clicked();
        signal button2Clicked();

        Rectangle
        {
            id: r_programm_name
            width: swidth * 24.21875
            height: sheight * 6.25
            y: sheight * 10.083
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenterOffset: parent.height/6
            color: "#F5F5F5"

             Text
             {
                 id:t_programm_name
                 text: qsTr("LKDS prog")
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.verticalCenter: parent.verticalCenter
                 font.family: "Helvetica"
                 font.pointSize: sheight * 6.25
                 color: "#749652"

             }

        }

        Rectangle
        {
            id:buttongroup
            color: "#F5F5F5"
            height: sheight * 37.31481
            width: swidth * 39.7395
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: parent.height/15
            Button
            {
                id: firstwindow_button1
                text: "Записать ключ"
                width: swidth * 39.53125
                height: sheight * 12.963
                background: Rectangle
                {
                    color: "#D3B992"
                }
                onClicked:
                {
                    firstwindow.button1Clicked();
                }
            }
            Button
            {
                id: firstwindow_button2
                text: "Просмотреть базу данных"
                width: swidth * 39.53125
                height: sheight * 12.963
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: parent.height/6
                background: Rectangle
                {
                    color: "#D3B992"
                }
            }
        }
        onButton1Clicked:
        {
            stackview.push(secondwindow)
        }
    }
    SecondWindow
    {
        id: secondwindow
        visible: false
        height: parent.height
        width: parent.width
    }
}
