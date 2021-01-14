/*****************************************************************************
*
* Copyright (C) 2020 Union Technology Co., Ltd.
*
* Author: Chen Shijie <chenshijie@uniontech.com>
*
* Maintainer:
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/

#include <fcitxqtinputmethodproxy.h>
#include "imlistmodel.h"
#include "fcitxqthelper.h"
#include <algorithm>

IMListModel::IMListModel(QObject *parent) : QAbstractListModel(parent)
{
}

QVariant IMListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= enableImItemList.size()) {
        return QVariant();
    }

    const auto &imEntry = enableImItemList.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return imEntry.name();
    case FcitxRowTypeRole:
        return IMType;
    case FcitxIMUniqueNameRole:
        return imEntry.uniqueName();
    case FcitxLanguageRole:
        return imEntry.langCode();
    }

    return QVariant();
}

int IMListModel::rowCount(const QModelIndex &) const
{
    return enableImItemList.count();
}

void IMListModel::filterIMEntryList(const FcitxQtInputMethodItemList &imEntryList, const QString &selection)
{
    int selectionRow = -1;
    enableImItemList.clear();

    beginResetModel();
    for (const auto &im : imEntryList) {
        if (im.enabled()) {
            enableImItemList.append(im);
            if (im.uniqueName() == selection) {
                selectionRow = enableImItemList.count();
            }
        }
    }
    endResetModel();

    /* 当前输入法列表中有数据才会发送 select 信号 */
    if (-1 != selectionRow) {
        emit select(createIndex(selectionRow, 0, nullptr));
    }
}

void IMListModel::rmSelectedItem(QModelIndex index)
{
    //not realy delete it imputmethod
    auto *imProxy = FcitxQtHelper::instance()->getInputMethodProxy();
    if (imProxy) {
        FcitxQtInputMethodItemList allImItemList = imProxy->iMList();
        FcitxQtInputMethodItem imItem = enableImItemList.at(index.row());
        imItem.setEnabled(false);

        auto res = std::find_if(allImItemList.begin(), allImItemList.end(), [&](const FcitxQtInputMethodItem & val) {
            return val.uniqueName() == imItem.uniqueName();
        });

        if (res != allImItemList.end()) {
            allImItemList.erase(res);
            allImItemList.append(imItem);
            imProxy->setIMList(allImItemList);
        }
    }

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    enableImItemList.removeAt(index.row());
    endRemoveRows();
}

void IMListModel::moveUpItem(QModelIndex index)
{
    //    moveUpItem it imputmethod
    if (index.row() == 0) {
        return;
    }

    swapTarget(index.row(), index.row() - 1, enableImItemList);

    emit updateListViewSelectdIndex(createIndex(index.row() - 1, 0));
    beginMoveRows(QModelIndex(), index.row(), index.row(), QModelIndex(), index.row() - 1);
    enableImItemList.swap(index.row(), index.row() - 1);
    endMoveRows();
}

void IMListModel::moveDownItem(QModelIndex index)
{
    // moveDownItem it imputmethod
    if (index.row() == (enableImItemList.size() - 1)) {
        return;
    }

    swapTarget(index.row(), index.row() + 1, enableImItemList);

    emit updateListViewSelectdIndex(createIndex(index.row() + 1, 0));
    beginMoveRows(QModelIndex(), index.row(), index.row(), QModelIndex(), index.row() + 2);
    enableImItemList.swap(index.row(), index.row() + 1);
    endMoveRows();
}

void IMListModel::swapTarget(const int &oldIndex, const int &newIndex,
                             const FcitxQtInputMethodItemList &itemList)
{
    auto *imProxy = FcitxQtHelper::instance()->getInputMethodProxy();
    if (!imProxy) {
        return;
    }

    auto allImItemList = imProxy->iMList();
    auto imItemNow = itemList.at(oldIndex);
    auto imItemUp = itemList.at(newIndex);

    auto itemNow {allImItemList.end()};
    auto itemUp {allImItemList.end()};
    for (auto begin = allImItemList.begin(); begin != allImItemList.end(); begin++) {
        if (itemNow == allImItemList.end() && begin->uniqueName() == imItemNow.uniqueName()) {
            itemNow = begin;
        }
        if (itemUp == allImItemList.end() && begin->uniqueName() == imItemNow.uniqueName()) {
            itemUp = begin;
        }
        if (itemUp != allImItemList.end() && itemNow != allImItemList.end()) {
            break;
        }
    }

    std::swap(*itemNow, *itemUp);
    imProxy->setIMList(allImItemList);
}

