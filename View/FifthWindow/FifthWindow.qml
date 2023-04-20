import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import AllBase 1.0
import QtQml.Models 2.15
import COMPortModel 1.0
import CBM 1.0
import "../FifthWindow/"

Rectangle
{
    id: fifthwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    property bool checkTouch: false
    color: "#F7EFD7"

    Controller_allBase
    {
        id: c_ab
    }
    CBModel
    {
        id: cbm
    }

    AddCustom
    {
        id: a_c
        c_ab: c_ab
        flagRedact: false
    }
    AddReg
    {
        id: a_r
        c_ab: c_ab
        flagRedact: false
    }

    signal buttonFirstWindowClicked()

    function onAct(index)
    {
        c_ab.setTableNum(index)
        cbm.updateData(index)
        c_ab.setSecTabNum(0)
        com_f_box_two.displayText = cbm.getValue(0)
    }

    function onAction(index)
    {
        c_ab.setSecTabNum(index)
        com_f_box_two.displayText = cbm.getValue(index)

    }
    onWindowChanged: {
        c_ab.setTableNum(0)
        cbm.updateData(0)
        c_ab.setSecTabNum(0)
        com_f_box_two.displayText = cbm.getValue(0)
    }

    Rectangle
    {
        width: swidth * 58.333333
        height: sheight * 6.09375
        color: "#F7EFD7"
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
            onClicked:
            {
                c_ab.search(text.text)
                //text.clear()
            }
        }

        Button
        {
            id: cancelbutton
            height: parent.height
            width: swidth * 5
            x: swidth * 59
            background: Rectangle
            {
                color: "#D3B992"
            }
            Text {
                id: namecancel
                text: qsTr("X")
                font.family: "Helvetica"
                font.pointSize: sheight * 2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            onClicked:
            {
                c_ab.refreshTable()
                text.clear()
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
        visible: true
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 5


            TableModeler_fw {
                id : tab
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: c_ab
                columnWidths: [10 * swidth, 15 * swidth, 10 * swidth, 10 * swidth, 12 *swidth]
            }

        }
    }

    Rectangle
    {
        id: searchCase
        width: swidth * 30.9688
        height: sheight * 7.6563
        x: swidth * 65
        y: sheight * 12.796875
        color: "#F7EFD7"
        Rectangle
        {
            id:firstpanel
            height: parent.height
            width: swidth * 15
            anchors.left: parent.left

            ComboBox
            {
                id: com_f_box
                width: parent.width
                height: parent.height
                model: ["Custom", "ServKey", "Region"]
                onActivated: (index) =>{onAct(index)}

            }

        }
        Rectangle
        {
            id: secondpanel
            height: parent.height
            width: swidth * 15
            anchors.right: parent.right
            ComboBox
            {
                id: com_f_box_two
                width: parent.width
                height: parent.height
                model: cbm
                onActivated: (index)=>{onAction(index)}

            }
        }
    }

    Rectangle
    {
        id: buttoncase
        width: swidth * 27.9688
        height: sheight * 37.1875
        x: swidth * 66.7187
        y: sheight * 22.796875
        color: "#F7EFD7"
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
            onClicked:
            {
                if (c_ab.checkTable() === 0)
                {
                    a_c.flagRedact = false
                    a_c.open()
                    add.background.color = "#D3B992"
                }
                else if(c_ab.checkTable() === 1)
                {
                    add.enabled
                    add.background.color = "grey"
                }
                else if (c_ab.checkTable() === 2 || c_ab.checkTable() === 3)
                {
                    a_r.flagRedact = false
                    a_r.open()
                    c_ab.refreshTable()
                    add.background.color = "#D3B992"
                }
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
            onClicked:
            {
                checkTouch = c_ab.checkTouchFlag()
                if (c_ab.checkTable() === 0 && checkTouch === true )
                {
                    a_c.flagRedact = true
                    a_c.open()
                    a_c.redact()
                    redact.background.color = "#D3B992"
                }
                else if(c_ab.checkTable() === 1)
                {
                    redact.enabled
                    redact.background.color = "grey"
                }
                else if ((c_ab.checkTable() === 2 || c_ab.checkTable() === 3) && checkTouch === true)
                {
                    a_r.flagRedact = true
                    a_r.open()
                    a_r.redact()
                    c_ab.refreshTable()
                    redact.background.color = "#D3B992"
                }

            }

        }

            Dialog
            {
                id: podtv
                height: sheight * 20
                width: swidth * 20
                x: -30 * swidth
                y: 15 * sheight
                title: "Подтверждение"
                contentItem: Rectangle
                {
                    height: parent.height
                    width: parent.width
                    Text {
                        id: podtv_text
                        text: qsTr("Вы уверены в удалении?")
                        font.family: "Helvetica"
                        font.pointSize: swidth
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    color: "#F7EFD7"
                }
                footer: Rectangle
                {
                    height: sheight * 5
                    width: parent.width
                    color: "#F7EFD7"
                    Button
                    {
                        id: okbut
                        width: swidth * 10
                        height: sheight * 5
                        text: "Да"
                        background: Rectangle
                        {
                            color: "#D3B992"
                        }
                        onClicked:
                        {
                            c_ab.deleteRow()
                            podtv.close()
                        }
                    }

                    Button
                    {
                        id: cancelbut
                        width: swidth * 10
                        height: sheight * 5
                        text: "Нет"
                        x: swidth * 10
                        background: Rectangle
                        {
                            color: "#D3B992"
                        }
                        onClicked:
                        {
                            podtv.close()
                        }
                    }
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
            onClicked:
            {
                checkTouch = c_ab.checkTouchFlag()
                if (c_ab.checkTable() !== 1 && checkTouch === true)
                {
                    podtv.open()
                }
                else
                {
                    delet.enabled
                    delet.background.color = "grey"
                }
            }

        }
        Dialog
        {
            id:podtv_file
            height: sheight * 20
            width: swidth * 20
            x: -30 * swidth
            y: 15 * sheight
            title: "Подтверждение"
            contentItem: Rectangle
            {
                height: parent.height
                width: parent.width
                Rectangle
                {
                    height: parent.height / 2
                    width: parent.width
                    color: "#F7EFD7"
                    Text {
                        id: podtv_tex
                        text: qsTr("Введите имя файла")
                        font.family: "Helvetica"
                        font.pointSize: swidth
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Rectangle
                    {
                        height: sheight * 4
                        width: parent.width
                        y: sheight * 5
                        TextInput
                        {
                            id: path
                            height: parent.height
                            width: parent.width
                            font.family: "Helvetica"
                            font.pointSize: swidth * 1.5
                            color: "black"
                        }
                    }
                }
                color: "#F7EFD7"
            }
            footer: Rectangle
            {
                height: sheight * 5
                width: parent.width
                color: "#F7EFD7"
                Button
                {
                    id: okbut1
                    width: swidth * 10
                    height: sheight * 5
                    text: "Да"
                    background: Rectangle
                    {
                        color: "#D3B992"
                    }
                    onClicked:
                    {
                        c_ab.pushDataToFile(path.text)
                        podtv_file.close()
                    }
                }

                Button
                {
                    id: cancelbut1
                    width: swidth * 10
                    height: sheight * 5
                    text: "Нет"
                    x: swidth * 10
                    background: Rectangle
                    {
                        color: "#D3B992"
                    }
                    onClicked:
                    {
                        podtv_file.close()
                    }
                }
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
            onClicked:
            {
                podtv_file.open()
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
