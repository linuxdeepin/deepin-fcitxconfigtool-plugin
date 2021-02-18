/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     liuwenhao <liuwenhao@uniontech.com>
*
* Maintainer: liuwenhao <liuwenhao@uniontech.com>
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
*/
#include "immodel.h"
#include "fcitxInterface/global.h"
#include "publisher/publisherdef.h"
#include "imconfig.h"
#include <QApplication>
#include <DStyle>
#include <DStandardItem>

using namespace Fcitx;
using namespace Dtk::Widget;

IMModel *IMModel::m_ins {nullptr};

bool operator==(const FcitxQtInputMethodItem &item, const FcitxQtInputMethodItem &item2)
{
    return item.name() == item2.name()
           && item.langCode() == item2.langCode()
           && item.uniqueName() == item2.uniqueName() && item.enabled() == item2.enabled();
}

IMModel::IMModel()
    : QStandardItemModel(nullptr)
{
    onUpdateIMList();
    connect(Global::instance(), &Global::connectStatusChanged, this, &IMModel::onUpdateIMList);
}

IMModel::~IMModel()
{
}

IMModel *IMModel::instance()
{
    return m_ins == nullptr ? (m_ins = new IMModel()) : m_ins;
}

void IMModel::deleteIMModel()
{
    deleteObject_Null(m_ins);
}

Qt::DropActions IMModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList IMModel::mimeTypes() const
{
    return QStringList() << "InputMethod";
}

QMimeData *IMModel::mimeData(const QModelIndexList &index) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodeData;

    QDataStream stream(&encodeData, QIODevice::WriteOnly);
    foreach (const QModelIndex &index, index) {
        if (index.isValid()) {
            stream << index.row();
        }
    }
    mimeData->setData("InputMethod", encodeData);
    return mimeData;
}

bool IMModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("InputMethod") || column > 0)
        return false;

    QByteArray encodeData = data->data("InputMethod");
    QDataStream stream(&encodeData, QIODevice::ReadOnly);
    int swapRow = 0;
    if (!stream.atEnd()) {
        stream >> swapRow;
    }

    if (row == 0 || parent.row() == 0)
        return false;

    int insRow;
    if (row != -1) {
        insRow = row;
    } else if (parent.isValid()) {
        insRow = parent.row();
    } else {
        insRow = rowCount() - 1;
    }

    if (swapRow == insRow)
        return false;
    else if (swapRow > insRow) {
        m_curIMList.insert(insRow, m_curIMList[swapRow]);
        m_curIMList.removeAt(swapRow + 1);
    } else {
        FcitxQtInputMethodItem it = m_curIMList[swapRow];
        m_curIMList.removeAt(swapRow);
        m_curIMList.insert(insRow, it);
    }
    loadItem();
    IMListSave();
    return true;
}

Qt::ItemFlags IMModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsSelectable;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled;
}

void IMModel::setEdit(bool flag)
{
    m_isEdit = flag;
    loadItem();
    if (!m_isEdit) {
        IMListSave();
    }
}

int IMModel::getIMIndex(const QString &IM) const
{
    if (IM.isEmpty()) {
        return -1;
    }

    for (int i = 0; i < m_curIMList.count(); ++i) {
        if (m_curIMList[i].name().indexOf(IM, Qt::CaseInsensitive) != -1
            || m_curIMList[i].uniqueName().indexOf(IM, Qt::CaseInsensitive) != -1
            || m_curIMList[i].langCode().indexOf(IM, Qt::CaseInsensitive) != -1) {
            return i;
        }
    }
    return -1;
}

FcitxQtInputMethodItem IMModel::getIM(int index) const
{
    if (index > m_curIMList.count() || index < 0)
        return FcitxQtInputMethodItem();
    return m_curIMList[index];
}

void IMModel::onUpdateIMList()
{
    if (Global::instance()->inputMethodProxy()) {
        FcitxQtInputMethodItemList &&list = Global::instance()->inputMethodProxy()->iMList();
        FcitxQtInputMethodItemList curList, availList;
        Q_FOREACH (const FcitxQtInputMethodItem &im, list) {
            if (im.enabled()) {
                curList.append(im);
            } else {
                availList.append(im);
            }
        }

        if (curList != m_curIMList) {
            m_curIMList.swap(curList);
            loadItem();
            emit curIMListChanaged(m_curIMList);
        }

        if (availList != m_availeIMList) {
            m_availeIMList.swap(availList);
            emit availIMListChanged(m_availeIMList);
        }

    } else {
        m_availeIMList.clear();
        m_curIMList.clear();
        this->clear();
        emit curIMListChanaged(m_curIMList);
        emit availIMListChanged(m_availeIMList);
    }
}

void IMModel::loadItem()
{
    if (0 == m_curIMList.count()) {
        this->clear();
        return;
    }

    int i = 0;
    foreach (FcitxQtInputMethodItem it, m_curIMList) {
        QStandardItem *iter = item(i, 0);
        DStandardItem *item = dynamic_cast<DStandardItem *>(iter);
        if (!item) {
            item = new DStandardItem();
            this->appendRow(item);
        }

        if (item->text() != it.name()) {
            item->setText(it.name());
        }

        if (i > 0) {
            addActionList(item);
        }
        ++i;
    }
    while (rowCount() > m_curIMList.count()) {
        this->removeRow(rowCount() - 1);
    }
}

void IMModel::addIMItem(FcitxQtInputMethodItem item)
{
    if (item.name().isEmpty() || item.uniqueName().isEmpty())
        return;

    m_availeIMList.removeAll(item);
    item.setEnabled(true);
    m_curIMList.insert(1, item);
    DStandardItem *tmp = new DStandardItem();
    tmp->setText(item.name());
    addActionList(tmp);
    insertRow(1, tmp);
    IMListSave();
    emit availIMListChanged(m_availeIMList);
}

void IMModel::deleteItem(DStandardItem *item)
{
    if (!item || !item->index().isValid())
        return;

    m_availeIMList.append(m_curIMList[item->row()]);
    m_availeIMList.rbegin()->setEnabled(false);
    m_curIMList.removeAt(item->row());
    this->removeRow(item->row());
    emit curIMListChanaged(m_curIMList);
}

void IMModel::itemUp(DStandardItem *item)
{
    if (!item || !item->index().isValid() || item->row() < 2)
        return;

    itemSawp(item->row(), item->row() - 1);
}

void IMModel::itemDown(DStandardItem *item)
{
    if (!item || !item->index().isValid() || item->row() == m_curIMList.count() - 1)
        return;

    itemSawp(item->row(), item->row() + 1);
}

void IMModel::itemSawp(int index, int index2)
{
    if (index < 0 || index > m_curIMList.count() - 1 || index2 < 0 || index2 > m_curIMList.count() - 1)
        return;

    m_curIMList.swap(index, index2);
    loadItem();
    IMListSave();
}

void IMModel::configShow(DStandardItem *item)
{
    if (!item || !item->index().isValid())
        return;

    QString imName = m_curIMList[item->row()].name();
    QString imLangCode = m_curIMList[item->row()].langCode();
    QString imUniqueName = m_curIMList[item->row()].uniqueName();

    QStringList closeSrcImList {
        "chineseime", "iflyime", "huayupy", "sogoupinyin", "baidupinyin"};

    if (closeSrcImList.contains(imUniqueName)) {
        QProcess::startDetached(IMConfig::IMPluginKey(imUniqueName));
    } else {
        QDBusPendingReply<QString>
            result = Global::instance()->inputMethodProxy()->GetIMAddon(imUniqueName);
        result.waitForFinished();
        if (result.isValid()) {
            QProcess::startDetached("fcitx-config-gtk3 " + result.value());
        }
    }
}

void IMModel::IMListSave()
{
    if (Global::instance()->inputMethodProxy()) {
        FcitxQtInputMethodItemList &&list = (m_curIMList + m_availeIMList);
        if (list == Global::instance()->inputMethodProxy()->iMList())
            return;
        if (Global::instance()->inputMethodProxy()) {
            Global::instance()->inputMethodProxy()->setIMList(m_curIMList + m_availeIMList);
            Global::instance()->inputMethodProxy()->ReloadConfig();
        }
        emit curIMListChanaged(m_curIMList);
    }
}

void IMModel::addActionList(DStandardItem *item)
{
    if (!item || !item->index().isValid())
        return;

    DViewItemActionList list;
    if (m_isEdit) {
        DViewItemAction *iconAction = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
        iconAction->setIcon(DStyle::standardIcon(QApplication::style(), DStyle::SP_DeleteButton));
        connect(iconAction, &DViewItemAction::triggered, [=]() { deleteItem(item); });
        list.push_back(iconAction);
    } else {
        DViewItemAction *iconAction = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
        iconAction->setIcon(QIcon(":/icons/arrow_up.svg"));
        DViewItemAction *iconAction2 = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
        iconAction2->setIcon(QIcon(":/icons/arrow_down.svg"));
        DViewItemAction *iconAction3 = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
        iconAction3->setIcon(QIcon(":/icons/setting.svg"));
        connect(iconAction, &DViewItemAction::triggered, [=]() { itemUp(item); });
        connect(iconAction2, &DViewItemAction::triggered, [=]() { itemDown(item); });
        connect(iconAction3, &DViewItemAction::triggered, [=]() { configShow(item); });
        list.push_back(iconAction);
        list.push_back(iconAction2);
        list.push_back(iconAction3);
    }
    item->setActionList(Qt::RightEdge, list);
}
