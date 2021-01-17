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

#ifndef ADDIMLISTMODEL_H
#define ADDIMLISTMODEL_H

#include <QAbstractListModel>

#include <fcitxqtinputmethoditem.h>

class AddIMListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AddIMListModel(QObject *parent = nullptr);

    enum {FcitxRowTypeRole = 0x324da8fc, FcitxLanguageRole, FcitxIMUniqueNameRole};
    enum {LanguageType, IMType};

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    void filterAddModelIMList(const FcitxQtInputMethodItemList &imEntryList, const QString &selection = QString());

signals:
    void updateIm();

public slots:
    void addSelectedItem(QModelIndex index);

private:
    FcitxQtInputMethodItemList disableImItemList;
};

#endif // IMLISTMODEL_H
