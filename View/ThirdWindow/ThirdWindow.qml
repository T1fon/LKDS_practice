import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import KeyTable 1.0

Rectangle
{
    id: thirdwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F5F5F5"

    signal buttonSecondWindowClicked()
    signal buttonFouthWindowClicked()

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

            TableModeler_th {
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: Controller_KeyTable {}
                columnWidths: [11 * swidth, 15 * swidth, 13 * swidth, 13 * swidth]
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
        color: "#F5F5F5"

        Button
        {
            id: addkey
            width: parent.width
            height: sheight * 7.65625
            text: "Добавить ключ"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
        }
        Button
        {
            id: deletekey
            width: parent.width
            height: sheight * 7.65625
            anchors.verticalCenter : addkey.bottom
            anchors.verticalCenterOffset: parent.height *0.22
            text: "Удалить ключ"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
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
}
