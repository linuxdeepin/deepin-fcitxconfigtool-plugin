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
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <libintl.h>

using namespace Fcitx;
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
    slot_updateIMList();
    connect(Global::instance(), &Global::connectStatusChanged, [=]() {
        m_timer2.start(IMConTime);
    });
    connect(&m_timer, &QTimer::timeout, this, &IMModel::IMListSvae);
    connect(&m_timer2, &QTimer::timeout, this, &IMModel::slot_updateIMList);
}

IMModel::~IMModel()
{
    qDebug() << "IMModel delete";
    IMListSvae();
}

IMModel *IMModel::instance()
{
    if (nullptr == m_ins) {
        m_ins = new IMModel();
    }
    return m_ins;
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
    foreach (const QModelIndex &ind, index) {
        if (ind.isValid()) {
            stream << ind.row();
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
    int rows = 0;
    if (!stream.atEnd()) {
        stream >> rows;
    }

    if (row == 0 || parent.row() == 0)
        return false;

    int insRow;
    if (row != -1)
        insRow = row;
    else if (parent.isValid())
        insRow = parent.row();
    else
        insRow = rowCount() - 1;

    if (rows == insRow)
        return false;
    else if (rows > insRow) {
        m_curIMList.insert(insRow, m_curIMList[rows]);
        m_curIMList.removeAt(rows + 1);
    } else {
        FcitxQtInputMethodItem it = m_curIMList[rows];
        m_curIMList.removeAt(rows);
        m_curIMList.insert(insRow, it);
    }
    loadItem();
    m_timer.start(IMchangedTime);
    emit sig_curIMList(m_curIMList);
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
        IMListSvae();
        emit sig_availIMList(m_availeIMList);
    }
}

void IMModel::addIMItem(FcitxQtInputMethodItem item)
{
    m_availeIMList.removeAll(item);
    item.setEnabled(true);
    m_curIMList.insert(1, item);
    DStandardItem *tmp = new DStandardItem();
    tmp->setText(item.name());
    addActionList(tmp);
    insertRow(1, tmp);
    IMListSvae();
    emit sig_availIMList(m_availeIMList);

    emit sig_curIMList(m_curIMList);
}

const FcitxQtInputMethodItemList &IMModel::availIMList() const
{
    return m_availeIMList;
}

const FcitxQtInputMethodItemList &IMModel::curIMList() const
{
    return m_curIMList;
}

int IMModel::getIMIndex(const QString &IM) const
{
    qDebug() << IM;
    for (int i = 0; i < m_curIMList.count(); ++i) {
        qDebug() << m_curIMList[i].name() << m_curIMList[i].uniqueName() << m_curIMList[i].langCode();
        if (m_curIMList[i].name().indexOf(IM, Qt::CaseInsensitive) != -1
            || m_curIMList[i].uniqueName().indexOf(IM, Qt::CaseInsensitive) != -1
            || m_curIMList[i].langCode().indexOf(IM, Qt::CaseInsensitive) != -1) {
            return i;
        }
    }

    return -1;
}

void IMModel::slot_updateIMList()
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
        }

        if (availList != m_availeIMList) {
            m_availeIMList.swap(availList);
            emit sig_availIMList(m_availeIMList);
        }
#if Debug
        foreach (FcitxQtInputMethodItem item, m_curIMList) {
            qDebug() << item.name();
        }

        qDebug() << m_curIMList.count() << m_availeIMList.count();
#endif
    } else {
        m_availeIMList.clear();
        m_curIMList.clear();
        this->clear();
        emit sig_availIMList(m_availeIMList);
    }
    m_timer2.stop();
    emit sig_curIMList(m_curIMList);
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

void IMModel::deleteItem(DStandardItem *item)
{
    if (!item || !item->index().isValid())
        return;
    m_availeIMList.append(m_curIMList[item->row()]);
    m_availeIMList.rbegin()->setEnabled(false);
    m_curIMList.removeAt(item->row());
    this->removeRow(item->row());
    emit sig_curIMList(m_curIMList);
}

void IMModel::itemUp(DStandardItem *item)
{
    if (item->row() < 2)
        return;
    itemSawp(item->row(), item->row() - 1);
}

void IMModel::itemDown(DStandardItem *item)
{
    if (item->row() == m_curIMList.count() - 1)
        return;
    itemSawp(item->row(), item->row() + 1);
}

void IMModel::itemSawp(int index, int index2)
{
    if (index < 0 || index > m_curIMList.count() - 1 || index2 < 0 || index2 > m_curIMList.count() - 1)
        return;
    m_curIMList.swap(index, index2);
    loadItem();
    m_timer.start(IMchangedTime);
    emit sig_curIMList(m_curIMList);
}

void IMModel::configShow(DStandardItem *item)
{
    qDebug() << m_curIMList[item->row()].name();
    qDebug() << m_curIMList[item->row()].langCode();
    qDebug() << m_curIMList[item->row()].uniqueName();
    QProcess::startDetached("fcitx-config-gtk3 shuangpin");
}

void IMModel::IMListSvae()
{
    if (Global::instance()->inputMethodProxy()) {
        FcitxQtInputMethodItemList &&list = (m_curIMList + m_availeIMList);
        if (list == Global::instance()->inputMethodProxy()->iMList())
            return;
#if Debug
        int a = 0, b = 0;
        foreach (FcitxQtInputMethodItem item, list) {
            if (item.enabled()) {
                qDebug() << "IMListSvae" << item.name();
                a++;
            } else {
                b++;
            }
        }
        qDebug() << "IMListSvae" << m_curIMList.count() << m_availeIMList.count() << a << b;
#endif
        Global::instance()->inputMethodProxy()->setIMList(m_curIMList + m_availeIMList);
        QProcess::startDetached("fcitx -r");
        m_timer.stop();
    }
}

void IMModel::addActionList(DStandardItem *item)
{
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
        connect(iconAction, &DViewItemAction::hovered, [=]() {
            qDebug() << "hover";
        });
        connect(iconAction2, &DViewItemAction::triggered, [=]() { itemDown(item); });
        connect(iconAction3, &DViewItemAction::triggered, [=]() { configShow(item); });
        list.push_back(iconAction);
        list.push_back(iconAction2);
        list.push_back(iconAction3);
    }
    item->setActionList(Qt::RightEdge, list);
}
