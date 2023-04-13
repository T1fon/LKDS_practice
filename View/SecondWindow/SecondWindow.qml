import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.15
import DatabaseManager 1.0
import SecWin 1.0
import KeyTable 1.0
import "../SecondWindow/"
import "../ThirdWindow/"



Rectangle
{
    Controller_KeyTable
    {
        id:contr
    }

    id: secondwindow
    width:800
    height: 600
    property int swidth: this.width/100
    property int sheight: this.height/100
    property bool flagRedact: false
    property int current_dialog_row: 0
    color: "#F7EFD7"

    signal buttonMainWindowClicked()
    signal buttonThirdWindowClicked()
    signal send()
    signal sendTW(ckt: Controller_KeyTable);
    signal changeLastKey()




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
                id: search_tE
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
                id: search
                text: qsTr("Поиск")
                font.family: "Helvetica"
                font.pointSize: sheight * 2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            onClicked:
            {
                if(search_tE.text != "")
                {
                    aa.searchCompany(search_tE.text)
                }
                else{
                    searchbutton.enabled
                }
            }

        }
        Button
        {
            id: cancelButton
            height: parent.height
            width: swidth * 5
            x: swidth * 59
            background: Rectangle
            {
                color: "#D3B992"
            }

            Text {
                id: cancel
                text: qsTr("X")
                font.family: "Helvetica"
                font.pointSize: sheight * 2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            onClicked:
            {
                search_tE.clear()
                aa.refreshTable()

            }
        }
    }

    Rectangle
    {
        id: secondwindow_table
        width: swidth * 58.3333
        height: sheight * 64.921875
        x: swidth * 3.125
        y: sheight * 11.796875
        visible: true
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 5


            TableModeler {
                id : tab
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: Controller_DatabaseManager {id:aa}
                columnWidths: [10 * swidth, 15 * swidth, 10 * swidth, 10 * swidth, 12 *swidth]
            }
        }

    }

    Keys.onEnterPressed: (event)=>{
       thirdwindow_button.clicked()
    }

    Dialog
    {
        id: add
        height: sheight * 51.875
        width: swidth * 46.666
        title: "Добавить компанию"
        x: 30 * swidth
        y: 20 * sheight



        contentItem: Rectangle
        {
            width: parent.width
            height: parent.height
            color: "#F7EFD7"
            Keys.onEnterPressed: {
                okbut.clicked()
            }
            Keys.forwardTo: [tE1, tE2, tE3, tE4]
            Rectangle
           {
               id:e1
               height: sheight * 7.3333
               width: parent.width - swidth*2
               y: sheight * 2
               x: swidth
               color: "#FBFBFB"

               TextInput
               {
                   id: tE1
                   height: parent.height
                   width: swidth * 23.313
                   font.family: "Helvetica"
                   font.pointSize: swidth * 1.5
                   color: "black"
                   topPadding: sheight * 2.5
                   leftPadding: swidth * 1.5
                   focus: true
                   KeyNavigation.tab: tE2
               }
               Rectangle
               {
                   height: parent.height
                   width: swidth * 15.5416
                   color: "#D3B992"
                   anchors.right: parent.right
                   Text {
                       text: qsTr("Название компании")
                       font.family: "Helvetica"
                       font.pointSize: swidth
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter

                   }
               }
           }
           Rectangle
           {
               id:e2
               height: sheight * 7.3333
               width: parent.width - swidth*2
               y: sheight * 11
               x: swidth
               color: "#FBFBFB"

               TextInput
               {
                   id: tE2
                   height: parent.height
                   width: swidth * 23.313
                   font.family: "Helvetica"
                   font.pointSize: swidth * 1.5
                   color: "black"
                   topPadding: sheight * 2.5
                   leftPadding: swidth * 1.5
                    KeyNavigation.tab: tE3
               }
               Rectangle
               {
                   height: parent.height
                   width: swidth * 15.5416
                   color: "#D3B992"
                   anchors.right: parent.right

                   Text {
                       text: qsTr("ИНН")
                       font.family: "Helvetica"
                       font.pointSize: swidth
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter

                   }
               }
           }
           Rectangle
           {
               id:e3
               height: sheight * 7.3333
               width: parent.width - swidth*2
               y: sheight * 20
               x: swidth
               color: "#FBFBFB"

               TextInput
               {
                   id: tE3
                   height: parent.height
                   width: swidth * 23.313
                   font.family: "Helvetica"
                   font.pointSize: swidth * 1.5
                   color: "black"
                   topPadding: sheight * 2.5
                   leftPadding: swidth * 1.5
                    KeyNavigation.tab: tE4
               }
               Rectangle
               {
                   height: parent.height
                   width: swidth * 15.5416
                   color: "#D3B992"
                   anchors.right: parent.right

                   Text {
                       text: qsTr("Название региона")
                       font.family: "Helvetica"
                       font.pointSize: swidth
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter

                   }
               }
           }
           Rectangle
           {
               id:e4
               height: sheight * 7.3333
               width: parent.width - swidth*2
               y: sheight * 29
               x: swidth
               color: "#FBFBFB"

               TextInput
               {
                   id: tE4
                   height: parent.height
                   width: swidth * 23.313
                   font.family: "Helvetica"
                   font.pointSize: swidth * 1.5
                   color: "black"
                   topPadding: sheight * 2.5
                   leftPadding: swidth * 1.5
                   KeyNavigation.tab: tE1
               }
               Rectangle
               {
                   height: parent.height
                   width: swidth * 15.5416
                   color: "#D3B992"
                   anchors.right: parent.right

                   Text {
                       text: qsTr("Название города")
                       font.family: "Helvetica"
                       font.pointSize: swidth
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter

                   }
               }
           }

        }
        footer: Rectangle
        {
            width: parent.width
            height: sheight * 8
            color: "#F7EFD7"
            Button
            {
                id: okbut
                width: swidth * 17
                height: sheight * 5
                x: swidth * 2
                y: sheight
                text: "Добавить"

                background: Rectangle
                {
                    color: "#D3B992"
                }
                onClicked:
                {
                    aa.recieveData(tE1.text, tE2.text, tE3.text, tE4.text, flagRedact);
                    tE1.clear()
                    tE2.clear()
                    tE3.clear()
                    tE4.clear()
                    flagRedact = false

                    add.close()

                }
            }
            Button
            {
                id: exbut
                width: swidth * 17
                height: sheight * 5
                x: swidth * 25
                y: sheight
                text: "Отмена"
                background: Rectangle
                {
                    color: "#D3B992"
                }
                onClicked:
                {
                    tE1.clear()
                    tE2.clear()
                    tE3.clear()
                    tE4.clear()
                    add.close()
                }
            }

        }
    }

    Rectangle
    {
        id: info
        width: swidth * 27.96875
        height: sheight * 36.1718
        x:swidth * 67.552
        y:sheight * 11.71875
        color: "#F7EFD7"
        Rectangle
        {
            height: sheight * 12
            width: parent.width
            color: "white"
            TextEdit
            {
                id: infoKey
                height: parent.height
                width: parent.width
                font.family: "Helvetica"
                font.pointSize: swidth* 1.1
                color: "black"
                topPadding: sheight * 2.5
                leftPadding: swidth * 1.5
                readOnly: true
            }
        }

        Button
        {
            id: addcompany
            height: sheight * 7.65625
            y: sheight * 20
            width: parent.width
            //anchors.bottom: parent.bottom
            text:"Добавить компанию"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                add.open()
            }
        }
        Button
        {
            id: redactcompany
            height: sheight * 7.65625
            width: parent.width
            anchors.bottom: parent.bottom
            text:"Редактировать"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                flagRedact = true
                add.open()
                tE1.text = aa.checkName()
                tE2.text = aa.checkInn()
                tE3.text = aa.checkReg1()
                tE4.text = aa.checkCity()
            }

        }
    }

    Rectangle
    {
        id: travellmenu
        height: sheight * 16.5625
        width: swidth * 27.96875
        color: "#F7EFD7"
        //anchors.right: parent.right
        y: sheight * 60.15625
        x: swidth * 67.552

        Button
        {
            id:thirdwindow_button
            width: parent.width
            height: sheight * 7.65625
            text:"Продолжить"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                if(aa.checkReg() !== ""){
                    contr.recieveRegion(aa.checkCodCust(), aa.checkCity(), aa.checkReg())
                    secondwindow.buttonThirdWindowClicked()
                    secondwindow.sendTW(contr)
                    search_tE.text = ""
                    cancelButton.clicked()
                    thirdwindow.changeData()
                }
            }

        }
        Button
        {
            id:firstwindow_button
            width: parent.width
            height: sheight * 7.65625
            anchors.bottom: parent.bottom
            text:"Назад"
            font.family: "Helvetica"
            font.pointSize: sheight * 1.5
            background: Rectangle
            {
                color: "#D3B992"
            }
            onClicked:
            {
                search_tE.text = ""
                secondwindow.buttonMainWindowClicked()
            }
        }
    }
    onChangeLastKey:
    {
        infoKey.text = aa.lastKey()
    }

}
