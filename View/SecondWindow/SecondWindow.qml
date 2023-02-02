import QtQuick 2.6
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle
{
    id: secondwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F5F5F5"

    Rectangle
    {
        width: swidth * 58.333333
        height: sheight * 6.09375
        color: "#F5F5F5"
        y: sheight * 2.969
        x: swidth * 3.125

       Rectangle
       {
           width: swidth * 46.87
           height: sheight * 6.09375
           //y: sheight * 3.01204
           color: "white"
            TextEdit
            {

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
        height: sheight * 64.921875
        x: swidth * 3.125
        y: sheight * 11.796875
        color: "red"
    }

    Rectangle
    {
        id: info
        width: swidth * 27.96875
        height: sheight * 36.1718
        x:swidth * 67.552
        y:sheight * 11.71875
        color: "red"
        Button
        {
            id: addcompany
            height: sheight * 7.65625
            width: parent.width
        }
    }

}
