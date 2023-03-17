import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import WindowWriteKey 1.0
Rectangle
{

    Fouth_Window
    {
        id: window_write_key
    }

    id: thirdwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    property string access_level: "0"
    color: "#F5F5F5"
    signal buttonFirstWindowClicked();
    signal connectToDevice(port_name: string);

    onConnectToDevice: (port_name) =>
    {
        log_panel_area.text = ""
        window_write_key.setPortName(port_name);
    }

    Rectangle
    {
        id: info_panel
        width: swidth * 92.8125
        height: sheight * 8.0469
        x: swidth * 3.2292
        y: sheight * 2.9688
        color: "white"

        TextEdit
        {
            id: info_panel_edit
            width: parent.width
            height: parent.height
            font.family: "Helvetica"
            font.pointSize: swidth * 1.5
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
                objectName: "meckanik_radiobutton"
                checked: true
                text: qsTr("Механик")
                contentItem: Text
                {
                    text: meckanik.text
                    color: "red"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                    bottomPadding : 1 * swidth
                }
                onClicked:
                {
                    access_level = "0"
                }
            }

            RadioButton
            {
                id: operator
                objectName: "operator_radiobutton"
                text: qsTr("Оператор")
                //color: "green"
                contentItem: Text
                {
                    text: operator.text
                    color: "green"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                    bottomPadding : 1 * swidth
                }
                onClicked:
                {
                    access_level = "1"
                }
            }

            RadioButton
            {
                id: administrator
                objectName: "administrator_radiobutton"
                text: qsTr("Администратор")
                contentItem: Text
                {
                    text: administrator.text
                    color: "blue"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                    bottomPadding : 1 * swidth
                }
                onClicked:
                {
                    access_level = "2"
                }
            }
            RadioButton
            {
                id: developer
                objectName: "developer_radiobutton"
                text: qsTr("Разработчик")
                contentItem: Text
                {
                    text: developer.text
                    color: "#f6fa20"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                    bottomPadding : 1 * swidth
                }
                onClicked:
                {
                    access_level = "3"
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
            id: write_button
            objectName: "write_button"
            width: swidth * 27.9687
            height: sheight * 7.6562
            text: "Записать"
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                window_write_key.write(info_panel_edit.text,access_level)
            }
        }
        Button
        {
            id: check_button
            objectName: "check_button"
            width: swidth * 27.9687
            height: sheight * 7.6562
            anchors.right: parent.right
            text: "Проверить"
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                window_write_key.check()
            }
        }
        Button
        {
            id: read_button
            objectName: "read_button"
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
            onClicked:
            {
                window_write_key.read()
            }
        }
        Button
        {
            id: clean_button
            objectName: "clean_button"
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
            onClicked:
            {
                window_write_key.clear()
            }
        }
        Button
        {
            id: end_button
            objectName: "end_button"
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
        id: log_panel
        objectName: "log_panel"
        width: swidth * 93.5416
        height: sheight * 39.2187
        x: swidth * 3.2292
        y: sheight * 51.0156
        color: "#D9D9D9"

        ScrollView {
            id: scroll_bar
            width: parent.width
            height: parent.height
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            clip: true

            TextEdit
            {
                id: log_panel_area
                width: parent.width
                height: parent.height
                leftPadding: swidth * 1
                topPadding: swidth * 1
                rightPadding: swidth * 1
                bottomPadding: swidth * 1
                color:"#000000"
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignLeft"
                verticalAlignment: "AlignBottom"
                clip: true
                readOnly: true
            }

        }
    }

    Connections
    {
        target: window_write_key
        function onSendToQml(message) {
            log_panel_area.text = log_panel_area.text + message
        }
    }
}
