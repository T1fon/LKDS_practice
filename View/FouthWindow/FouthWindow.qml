import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import WindowWriteKey 1.0
import KeyTable 1.0

Rectangle
{

    Fouth_Window
    {
        id: window_write_key
        onSignalClearLog:  ()=>
        {
            log_panel_area.text = ""
        }
        onSuccefulWrite: (result, current_access_level, back_step)=>
        {
            if(result === true){
                var operation;
                info_panel_edit.text = window_write_key.getKeyParametr();
                if(back_step === false){
                    key_table.addKey(getCurrentKey()-1)
                    operation = 1;
                }
                else{
                    operation = -1;
                }

                if(current_access_level === 0){
                    meckanik_count.text = Number(meckanik_count.text)+operation
                }
                else if(current_access_level === 1){
                    operator_count.text = Number(operator_count.text)+operation
                }
                else if(current_access_level === 2){
                    administrator_count.text = Number(administrator_count.text)+operation
                }
                else if(current_access_level === 3){
                    developer_count.text = Number(developer_count.text)+operation
                }
            }
        }
    }

    id: thirdwindow
    width:800
    height: 600
    color: "#F7EFD7"

    property int swidth: this.width/100
    property int sheight: this.height/100
    property string access_level: "0"
    property Controller_KeyTable key_table: null

    signal buttonFirstWindowClicked();
    signal connectToDevice(port_name: string);
    signal sendInformationAboutKey(first_key: string, prefix: string, count_key: string, overwriting: bool);
    signal recieveTW(table_view: Controller_KeyTable)
    function backStep(){
        window_write_key.backStep(key_table);
    }
    onRecieveTW: (value) =>
    {
        key_table = value
    }

    onSendInformationAboutKey: (first_key, prefix, count_key, overwriting) =>
    {
        window_write_key.setKeyParametr(prefix,first_key,count_key, overwriting);
        info_panel_edit.text = window_write_key.getKeyParametr();
    }
    onConnectToDevice: (port_name) =>
    {
        log_panel_area.text = ""
        window_write_key.setPortName(port_name);
    }

    function onKeyPressed (event){
        if(event.key === Qt.Key_F5){
            window_write_key.write(window_write_key.getPrefix(),window_write_key.getCurrentKey(),access_level)
        }
        else if(event.key === Qt.Key_F6){
            window_write_key.read()
        }
        else if(event.key === Qt.Key_F7){
            window_write_key.check()
        }
        else if(event.key === Qt.Key_F8){
            window_write_key.clear()
        }
        else if(event.key === Qt.Key_F10){
            fouthwindow.buttonFirstWindowClicked()
        }
    }

    Keys.onPressed: onKeyPressed(event);

    Button{
        id: programmer_back
        x: swidth * 3.2291
        y: sheight * 2.9688
        width: swidth * 6.0937
        height: sheight * 8.0469
        text: "<-"
        background: Rectangle{
            color: "#D3B992"
        }
        onClicked: backStep()
    }

    Rectangle
    {
        id: info_panel
        width: swidth * 85.2083
        height: sheight * 8.0469
        x: swidth * 10.83333
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
            readOnly: true
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
                    color: "#FAFF00"
                    leftPadding: 2 * swidth
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                    bottomPadding : 1 * swidth
                    anchors.left: parent.left
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
        width: swidth * 42.3958
        height: sheight * 24.8438
        y: sheight * 16.7187
        x: swidth * 28.9062
        color: "#F7EFD7"
        Button
        {
            id: write_button
            objectName: "write_button"
            width: swidth * 19.427
            height: sheight * 6.2962
            text: "(F5) Записать"
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                window_write_key.write(window_write_key.getPrefix(),window_write_key.getCurrentKey(),access_level)
            }
        }
        Button
        {
            id: check_button
            objectName: "check_button"
            width: swidth * 19.427
            height: sheight * 6.2962
            anchors.right: parent.right
            text: "(F7) Проверить"
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
            width: swidth * 19.427
            height: sheight * 6.2962
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.verticalCenterOffset: -swidth * 0.25
            text: "(F6) Считать"
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
            width: swidth * 19.427
            height: sheight * 6.2962
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.verticalCenterOffset: -swidth * 0.25
            text: "(F8) Очистить"
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
            width: swidth * 19.427
            height: sheight * 6.2962
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: "(F10) Завершить"
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
        id: status_group
        width: swidth * 24.9479
        height: sheight * 24.8438
        x: swidth * 71.8229
        y: sheight * 16.7187
        color: "#D9D9D9"

        Column
        {
            id: text_column
            width: parent.width
            height: parent.height
            leftPadding: swidth * 2
            topPadding: sheight * 4

            Row{
                id: text_row_mechanic
                width: parent.width - swidth * 4
                height: parent.height/6
                Text{
                    text: "Механик"
                    color: "red"
                    anchors.left: parent.left
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
                Text{
                    id: meckanik_count
                    text: "0"
                    color: "black"
                    anchors.right: parent.right
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
            }
            Row{
                id: text_row_operator
                width: parent.width - swidth * 4
                height: parent.height/6
                Text{
                    text: "Оператор"
                    color: "green"
                    anchors.left: parent.left
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
                Text{
                    id: operator_count
                    text: "0"
                    color: "black"
                    anchors.right: parent.right
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
            }
            Row{
                id: text_row_administrator
                width: parent.width - swidth * 4
                height: parent.height/6
                Text{
                    text: "Администратор"
                    color: "blue"
                    anchors.left: parent.left
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
                Text{
                    id: administrator_count
                    text: "0"
                    color: "black"
                    anchors.right: parent.right
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
            }
            Row{
                id: text_row_developer
                width: parent.width - swidth * 4
                height: parent.height/6
                Text{
                    text: "Разработчик"
                    color: "#FAFF00"
                    anchors.left: parent.left
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
                Text{
                    id: developer_count
                    text: "0"
                    color: "black"
                    anchors.right: parent.right
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                }
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
                textFormat: TextEdit.RichText
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
