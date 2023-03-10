import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import QtQml.Models 2.15
import COMPortModel 1.0

Rectangle {
    id: settings_window
    width: 800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    color: "#F7EFD7"

    signal buttonFirstWindowClicked()
    //signal updateModel()

    COM_Port_Model{
        id: com_port_model
    }

    function onAct(index) {
        device_name_t_e_text.text = com_port_model.getDeviceName(index)
        device_id_t_e_text.text = com_port_model.getDeviceId(index)
        manufacturer_name_t_e_text.text = com_port_model.getManufacturerName(index)
        manufacturer_id_t_e_text.text = com_port_model.getManufacturerId(index)
    }
    Rectangle{
        id: com_box
        x: swidth * 26.5625
        y: sheight * 5.5555
        width: swidth * 46.875
        height: sheight * 14.9074
        Rectangle{
            width: parent.width
            height: parent.height/2

            color:"#F7EFD7"
            Text{
                id: com_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
                text: "COM порт"
            }
        }


        ComboBox{
            id:com_c_box

            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height/2
            model: com_port_model
            onActivated: onAct(index)
        }
    }



    Rectangle{
        id: device_name_box
        x: swidth * 12.5
        y: sheight * 27.3148
        width: swidth * 28.125
        height: sheight * 14.9074
        Rectangle{
            width: parent.width
            height: parent.height/2

            color:"#F7EFD7"
            Text{
                id: device_name_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
                text: "Имя устройства"
            }
        }

        TextEdit{
            id: device_name_t_e
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height/2
            readOnly: true
            Text{
                id: device_name_t_e_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
            }
        }
    }
    Rectangle{
        id: device_id_box
        x: swidth * 12.5
        y: sheight * 44.5370
        width: swidth * 28.125
        height: sheight * 14.9074
        Rectangle{
            width: parent.width
            height: parent.height/2

            color:"#F7EFD7"
            Text{
                id: device_id_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
                text: "ID устройства"
            }
        }

        TextEdit{
            id: device_id_t_e
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height/2
            readOnly: true
            Text{
                id: device_id_t_e_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
            }
        }
    }
    Rectangle{
        id: manufacturer_name_box
        x: swidth * 59.375
        y: sheight * 27.3148
        width: swidth * 28.125
        height: sheight * 14.9074
        Rectangle{
            width: parent.width
            height: parent.height/2

            color:"#F7EFD7"
            Text{
                id: manufacturer_name_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
                text: "Производитель"
            }
        }

        TextEdit{
            id: manufacturer_name_t_e
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height/2
            readOnly: true
            Text{
                id: manufacturer_name_t_e_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
            }
        }
    }
    Rectangle{
        id: manufacturer_id_box
        x: swidth * 59.375
        y: sheight * 44.5370
        width: swidth * 28.125
        height: sheight * 14.9074
        Rectangle{
            width: parent.width
            height: parent.height/2

            color:"#F7EFD7"
            Text{
                id: manufacturer_id_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
                text: "ID производителя"
            }
        }

        TextEdit{
            id: manufacturer_id_t_e
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height/2
            readOnly: true
            Text{
                id: manufacturer_id_t_e_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 1.5
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
            }
        }
    }

    Rectangle{
        id: bottons_box
        x: swidth * 20
        y: sheight * 79.4444
        width: swidth * 59.9479
        height: sheight * 9.074
        color: "#F7EFD7"

        Button
        {
            id: but_save
            anchors.left: parent.left
            width: swidth * 27.9687
            height: parent.height
            font.family: "Helvetica"
            font.pointSize: swidth * 1.5
            clip: true

            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 2
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
                text: "Сохранить"
                color: "#FBFBFB"
            }
            background: Rectangle{
                width: parent.width
                height: parent.height
                color: "#D3B992"
            }
        }
        Button
        {
            id: but_back
            anchors.right: parent.right
            width: swidth * 27.9687
            height: parent.height
            font.family: "Helvetica"
            font.pointSize: swidth * 1.5
            clip: true
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.family: "Helvetica"
                font.pointSize: swidth * 2
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                clip: true
                text: "Вернуться"
                color: "#FBFBFB"
            }
            background: Rectangle{
                width: parent.width
                height: parent.height
                color: "#D3B992"
            }
            onClicked:{
                buttonFirstWindowClicked()
            }
        }
    }

    /*Connections:{
        target: com_c_box
        function onActivated(index){
            /*device_name_text.text = com_port_model.getDeviceName(index)
            device_id_text.text = com_port_model.getDeviceId(index)
            manufacturer_name_text.text = com_port_model.getManufacturerName(index)
            manufacturer_id_text = com_port_model.getManufacturerId(index)
        }
    }*/
}
