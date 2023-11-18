import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import DatabaseManager 1.0
import SecWin 1.0
import KeyTable 1.0
import AllBase 1.0
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
    title: program_name
    property int swidth: this.width/100
    property int sheight: this.height/100
    property string program_name: "Key programmer"
    property string program_version: "Версия 1.1"

    property int defMargin: 10

    Controller_DatabaseManager
    {
        id:c_DB_M
    }

    StackView
    {
        id: stackview
        anchors.fill: parent
        initialItem: firstwindow
    }

    Text{
        text: program_version
        x:  swidth * 93
        y:  sheight * 97
        font.pointSize: 1 * swidth


    }

    Rectangle
    {
        id: firstwindow
        width:parent.width
        height: parent.height
        color: "#F7EFD7"
        signal button1Clicked();
        signal button2Clicked();
        signal changeTable();
        signal keyInformation(int firstKey, string pref, string numKey, bool redact)

        signal buttonSettingsClicked();

        Rectangle
        {
            id: r_programm_name
            width: swidth * 24.21875
            height: sheight * 6.25
            y: sheight * 10.083
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenterOffset: parent.height/6
            color: "#F7EFD7"

             Text
             {
                 id:t_programm_name
                 text: program_name
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
            color: "#F7EFD7"
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
                onClicked:
                {
                    firstwindow.button2Clicked()
                }
            }
        }

        onButton1Clicked:
        {
            secondwindow.windowChanged(mainwindow)
            stackview.push(secondwindow)

        }
        onButton2Clicked:
        {
            fifthwindow.windowChanged(mainwindow)
            stackview.push(fifthwindow)
        }

        Button{
            id: settingswindow_button
            x: swidth * 88.5416
            y: sheight * 81.4814
            width: swidth * 7.7083
            height: swidth * 7.7083
            display: AbstractButton.IconOnly
            icon.width: width
            icon.height: height
            icon.color: "transparent"
            icon.source: "/Source/settings.png"
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
        onSendTW: (value) =>
        {
            thirdwindow.recieveTW(value)
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
       /*onSendInformationAboutKey: ( firstKey,  pref,  numKey, redact) =>
       {
            firstwindow.keyInformation(firstKey,  pref,  numKey, redact)
       }*/
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
        onSetDevice: (port_name)=>
        {
            fouthwindow.connectToDevice(port_name)
        }
    }

}
