// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 test <>
import QtQuick 2.5
import QtQuick.Controls 2.5 as QQC2
import QtQuick.Controls 1.4 as QQC1
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.9 as Kirigami
import org.kde.kitemmodels 1.0
import org.kde.test_talbe_sql 1.0

Kirigami.ApplicationWindow {
  id: root

  required property DatabaseQueryModel databaseQueryModel

  title: "test_talbe_sql"

  minimumWidth: Kirigami.Units.gridUnit * 20
  minimumHeight: Kirigami.Units.gridUnit * 20

  globalDrawer: Kirigami.GlobalDrawer {
    title: "test_talbe_sql"
    actions: [
      Kirigami.Action {
        text: "Quit"
        onTriggered: Qt.quit()
      }
    ]
  }

  pageStack.initialPage: page

  Kirigami.Page {
    id: page

    Layout.fillWidth: true

    title: "Main Page"

    ListModel {
      id: columnListCustomer
      ListElement {
        role: "code"
        title: "Code"
      }
      ListElement {
        role: "name"
        title: "Name"
      }
      ListElement {
        role: "address"
        title: "Address"
      }
    }
    ListModel {
      id: listOfAvailableTable
      ListElement {
        role: "customer"
        title: "Customer"
      }
      ListElement {
        role: "item"
        title: "Item"
      }
    }

    header: QQC2.ToolBar {
      RowLayout {
        anchors.right: parent.right
        QQC2.Label {
          text: "Search for:"
        }
        Kirigami.SearchField {
          id: searchField
          Layout.fillWidth: true
        }
        QQC2.Label {
          text: "in:"
        }
        QQC2.ComboBox {
          id: comboBoxList
          textRole: "title"
          valueRole: "role"
          model: columnListCustomer
          Component.onCompleted: currentIndex = indexOfValue("name")
        }
        QQC2.ToolButton {
          icon.name: "list-add-symbolic"
          text: "Add"
          //display: AbstractButton.TextBesideIcon
        }
        QQC2.ToolButton {
          icon.name: "edit-entry"
          text: "Edit"
          //display: AbstractButton.TextBesideIcon
        }
        QQC2.ToolButton {
          icon.name: "edit-delete-remove"
          text: "Remove"
          //display: AbstractButton.TextBesideIcon
        }
        QQC2.Label {
          text: "Table:"
        }
        QQC2.ComboBox {
          textRole: "title"
          valueRole: "role"
          model: listOfAvailableTable
          Component.onCompleted: currentIndex = indexOfValue("customer")
        }
      }
    }

    QQC1.TableView {
      id: tableViewOne
      sortIndicatorVisible: true
      anchors.fill: parent
      model: KSortFilterProxyModel {
        sourceModel: databaseQueryModel
        sortOrder: tableViewOne.sortIndicatorOrder
        sortCaseSensitivity: Qt.CaseInsensitive
        sortRole: tableViewOne.getColumn(tableViewOne.sortIndicatorColumn).role
        filterRole: comboBoxList.currentValue
        filterRegularExpression: {
          if (searchField.text === "")
            return new RegExp()
          return new RegExp("%1".arg(searchField.text), "i")
        }
      }
      QQC1.TableViewColumn {
        role: "code"
        title: "Code"
        width: title.length * Kirigami.Units.gridUnit
      }

      QQC1.TableViewColumn {
        role: "name"
        title: "Name"
        width: title.length * Kirigami.Units.gridUnit
      }
      QQC1.TableViewColumn {
        role: "address"
        title: "Address"
        width: title.length * Kirigami.Units.gridUnit
      }
    }
  }
}
