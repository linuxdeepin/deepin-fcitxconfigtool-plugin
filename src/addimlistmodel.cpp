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
#include "addimlistmodel.h"
#include "fcitxqthelper.h"

AddIMListModel::AddIMListModel(QObject *parent) : QAbstractListModel(parent)
{
}

QVariant AddIMListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= disableImItemList.size()) {
        return QVariant();
    }

    const auto &imEntry = disableImItemList.at(index.row());

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

int AddIMListModel::rowCount(const QModelIndex &) const
{
    return disableImItemList.count();
}

void AddIMListModel::filterAddModelIMList(const FcitxQtInputMethodItemList &imEntryList, const QString &)
{
    disableImItemList.clear();
    beginResetModel();
    for (const auto &im : imEntryList) {
        if (!im.enabled()) {
            disableImItemList.append(im);
        }
    }
    endResetModel();
}

void AddIMListModel::addSelectedItem(QModelIndex index)
{
    //not realy delete it imputmethod
    auto *imProxy = FcitxQtHelper::instance()->getInputMethodProxy();
    if (imProxy) {
        FcitxQtInputMethodItemList allImItemList = imProxy->iMList();
        FcitxQtInputMethodItem imItem = disableImItemList.at(index.row());
        imItem.setEnabled(true);

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
    disableImItemList.removeAt(index.row());
    endRemoveRows();

    emit updateIm();
}
