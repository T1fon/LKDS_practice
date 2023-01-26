import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Controls 2.5


Window
{
    id: mainwindow
    width:800
    height: 600
    visible: true
    title: qsTr("Проект Арсений")
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F5F5F5"

    Rectangle
    {
        width:parent.width
        height: parent.height
        property int swidth: this.width/100
        property int sheight: this.height/100
        color: "#F5F5F5"

        Rectangle
        {
            id: r_programm_name
            width: swidth * 24.21875
            height: sheight * 6.25
            y: sheight * 10.083
            anchors.horizontalCenter: parent.horizontalCenter
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
            color: "red"
            height: sheight * 37.31481
            width: swidth * 39.7395
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            //anchors.verticalCenterOffset: parent.height/4
            /*Button
            {
                text: "Записать ключ"
                width: swidth * 39.53125
                height: sheight * 12.963

            }*/
        }
    }
}
