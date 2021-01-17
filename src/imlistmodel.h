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

#ifndef IMLISTMODEL_H
#define IMLISTMODEL_H

#include <QAbstractListModel>

#include <fcitxqtinputmethoditem.h>
#include <QAbstractItemView>

class IMListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit IMListModel(QObject *parent = nullptr);

    enum {FcitxRowTypeRole = 0x324da8fc, FcitxLanguageRole, FcitxIMUniqueNameRole};
    enum {LanguageType, IMType};

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

public slots:
    void filterIMEntryList(const FcitxQtInputMethodItemList &imEntryList, const QString &selection = QString());
    void rmSelectedItem(QModelIndex index);
    void moveUpItem(QModelIndex index);
    void moveDownItem(QModelIndex index);

private:
    void swapTarget(const int &oldIndex, const int &newIndex,
                    const FcitxQtInputMethodItemList &itemList);

signals:
    void select(QModelIndex index);
    void updateListViewSelectdIndex(const QModelIndex &index, QAbstractItemView::ScrollHint
                                    hint = QAbstractItemView::EnsureVisible);

private:
    FcitxQtInputMethodItemList enableImItemList;
};


#endif // IMLISTMODEL_H
