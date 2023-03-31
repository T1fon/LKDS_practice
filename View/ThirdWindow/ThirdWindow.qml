import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import KeyTable 1.0
import "../FirstWindow/"

Rectangle
{
    id: thirdwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    property bool redactKey: false
    color: "#F5F5F5"

    signal buttonSecondWindowClicked()
    signal buttonFouthWindowClicked()
    signal recieveTW(sdo: Controller_KeyTable)
    signal changeData()
    signal sendInformationAboutKey(int firstKey, string pref, string numKey, bool redact)
    signal checkRedact(bool flag)

    property Controller_KeyTable c_KT: null

    onRecieveTW: (value) =>
    {
        c_KT = value
    }

    Rectangle
    {
        id: companyinfo_r
        width: swidth * 58.3333
        height: sheight * 6.09375
        color: "white"
        y: sheight * 2.969
        x: swidth * 3.125
        TextEdit
        {
            id: companiinfo_t
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
        id: thirdwindow_table
        width: swidth * 58.3333
        height: sheight * 64.921875
        x: swidth * 3.125
        y: sheight * 11.796875
        visible: true
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 5
            id: ff

            TableModeler_th {
                id: table
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: c_KT
                columnWidths: [10 * swidth, 14 * swidth, 8 * swidth, 12 * swidth, 12 * swidth]
            }
        }
    }


    Rectangle
    {
        id: buttonmenu1
        width: swidth * 27.96875
        height: sheight * 27.8125
        x: swidth * 67.03125
        y: sheight * 12.3438
        //color: "red"
        color: "#F5F5F5"
        Rectangle
        {
            id:numKey
            width: parent.width
            height: sheight * 10
            //color: "red"
            color: "#F5F5F5"

            Rectangle
            {
                height: parent.height
                width: parent.width/2
                color: "#F5F5F5"
                Text
                {
                    id: numKeyText
                    text: qsTr("Кол-во ключей")
                    font.family: "Helvetica"
                    font.pointSize: sheight * 2
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

            }
            Rectangle
            {
                id :textRect
                height: sheight * 7
                width: swidth * 7
                y: sheight * 1.5
                x: swidth * 15
                color: "white"
                TextEdit
                {
                    id: tI
                    height: parent.height
                    width: parent.width
                    font.family: "Helvetica"
                    font.pointSize: swidth * 1.5
                    color: "black"
                    topPadding: sheight * 2.5
                    leftPadding: swidth * 1.5
                    text: "1"
                    onFocusChanged:
                    {
                        if(tI.focus){
                            tI.readOnly = false
                        }
                        table.block()
                    }

                }
            }
        }

        Button
        {
            id: addkey
            width: parent.width
            height: sheight * 7.65625
            y: sheight * 11
            text: "Добавить ключ"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                if (c_KT.getReg() !== "")
                    c_KT.addKey(tI.text)
                else
                    addkey.enabled
            }
        }
        Button
        {
            id: fourthwindow_button
            width: parent.width
            height: sheight * 7.65625
            anchors.bottom: parent.bottom
            text: "Программировать"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                thirdwindow.buttonFouthWindowClicked()
                thirdwindow.sendInformationAboutKey(c_KT.getKey(), c_KT.getReg(), tI.text, redactKey)

            }
        }
    }
    Button
    {
        id: secondwindow_button
        width: swidth * 27.96875
        height: sheight * 7.6563
        x: swidth * 67.03125
        y: sheight * 65.0781
        text: "Вернуться"
        font.family: "Helvetica"
        font.pointSize: sheight * 1.5
        background: Rectangle
        {
            color: "#D3B992"
        }
        onClicked:
        {
            thirdwindow.buttonSecondWindowClicked()
        }
    }
    onChangeData:
    {
        companiinfo_t.text = c_KT.printData()
    }
    onCheckRedact: (flag) =>
    {
        redactKey = flag
      //  tI.readOnly = true
    }
}
