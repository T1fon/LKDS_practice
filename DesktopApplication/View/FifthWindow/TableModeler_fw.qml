import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: table

    required property var model
    required property var columnWidths

    function columnWidthProvider(column) {
        return columnWidths[column]
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        HorizontalHeaderView {
            id: horizontalHeader

            reuseItems: false
            syncView: tableView
            height: 30
            Layout.fillWidth: true
            boundsBehavior:Flickable.StopAtBounds

            delegate: Rectangle {
                id: columnHeader
                color: "#eee"
                border.color: "#bbb"
                border.width: 1
                implicitWidth: headerText.contentWidth + 5*splitter.width
                implicitHeight: 30

                Text {
                    id: headerText
                    anchors.centerIn: parent
                    text: display
                }

                Rectangle {
                    id: splitter
                    x: table.columnWidths[index] - width
                    height: horizontalHeader.height
                    width: 4
                    color: "#999"
                    visible: dragArea.containsMouse || dragArea.drag.active

                    onXChanged: {
                        if (dragArea.drag.active) {
                            table.columnWidths[index] = splitter.x + width;
                            tableView.forceLayout();
                        }
                    }
                } // Rectangle splitter

                MouseArea {
                    id: dragArea
                    anchors.fill: splitter
                    cursorShape: Qt.SizeHorCursor
                    drag.target: splitter
                    drag.axis: Drag.XAxis
                    drag.threshold: 0
                    drag.minimumX: parent.implicitWidth
                    hoverEnabled: true
                }

            } // delegate Rectangle columnHeader

        } // HorizontalHeaderView

        TableView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            boundsBehavior:Flickable.StopAtBounds
            columnWidthProvider: table.columnWidthProvider
            model: table.model

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
                active: true
                onActiveChanged: {
                    if (!active)
                        active = true;
                }
            }

            ScrollBar.horizontal: ScrollBar {
                policy: ScrollBar.AsNeeded
                active: true
                onActiveChanged: {
                    if (!active)
                        active = true;
                }
            }
            selectionModel: ItemSelectionModel
            {
                model: tableView.model
            }

            delegate: Rectangle {
                id: bb
                required property bool current
                color: (row === tableView.currentRow) ? "lightgray" : "white"
                implicitHeight: 26
                border.color: "#bbb"
                border.width: 1
                Text {
                    id: cellText
                    text: display
                    anchors.verticalCenter: parent.verticalCenter
                    x: 4

                }
                onCurrentChanged: ()=>
                {
                    if(current)
                        c_ab.chooseRow(tableView.currentRow)
                        c_ab.redactProfile(tableView.currentRow)
                }
            }
        } // TableView

    } // ColumnLayout

} // Rectangle table
