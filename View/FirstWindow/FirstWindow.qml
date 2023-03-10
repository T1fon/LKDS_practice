import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import DatabaseManager
import "../SecondWindow/"
import "../ThirdWindow/"
import "../FouthWindow/"
import "../FifthWindow/"
import "../SettingsWindow/"


ApplicationWindow
{
    id: mainwindow
    width:800
    height: 600
    visible: true
    title: qsTr("Проект Арсений")
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F7EFD7"
    property int defMargin: 10

    StackView
    {
        id: stackview
        anchors.fill: parent
        initialItem: firstwindow
    }

    Rectangle
    {
        Connections
        {
            target: bd
        }
        id: firstwindow
        width:parent.width
        height: parent.height
        color: "#F5F5F5"
        signal button1Clicked();
        signal button2Clicked();
        signal buttonSettingsClicked();

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
                    bd.changeToSecond()
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
                onClicked:
                {
                    firstwindow.button2Clicked()
                }
            }
        }
        onButton1Clicked:
        {
            stackview.push(secondwindow)

        }
        onButton2Clicked:
        {
            stackview.push(fifthwindow)
        }

        Button{
            id: settingswindow_button
            x: swidth * 88.5416
            y: sheight * 81.4814
            width: swidth * 7.7083
            height: swidth * 7.7083
            text: "S"
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                firstwindow.buttonSettingsClicked()
            }
        }
        onButtonSettingsClicked: {
            stackview.push(settings_window)
        }
        Button{
            id: helpwindow_button
            x: swidth * 78.125
            y: sheight * 81.4814
            width: swidth * 7.7083
            height: swidth * 7.7083
            background: Rectangle
            {
                color: "#D3B992"
            }

        }
    }
    SecondWindow
    {
        id: secondwindow
        visible: false
        height: parent.height
        width: parent.width
        onButtonMainWindowClicked:
        {
            stackview.pop(firstwindow)

        }
        onButtonThirdWindowClicked:
        {
            stackview.push(thirdwindow)
        }
    }
    ThirdWindow
    {
        id: thirdwindow
        visible: false
        height: parent.height
        width: parent.width
       onButtonSecondWindowClicked:
       {
           stackview.pop(secondwindow)
       }
       onButtonFouthWindowClicked:
       {
           stackview.push(fouthwindow)
       }
    }
    FouthWindow
    {

        id: fouthwindow
        visible: false
        height: parent.height
        width: parent.width
        onButtonFirstWindowClicked:
        {
            stackview.pop(firstwindow)
        }
    }
    FifthWindow
    {
        id: fifthwindow
        visible: false
        height: parent.height
        width: parent.width
        onButtonFirstWindowClicked:
        {
            stackview.pop(firstwindow)
        }
    }
    SettingsWindow
    {
        id: settings_window
        visible: false
        height: parent.height
        width: parent.width
        onButtonFirstWindowClicked:
        {
            stackview.pop(firstwindow)
        }
    }
}
