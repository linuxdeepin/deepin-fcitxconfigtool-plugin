/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
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

#include "settingsgroup.h"
#include "settingsitem.h"
#include "settingsheaderitem.h"
#include "settingshead.h"
#include "utils.h"
#include "imsettingsitem.h"
#include <DBackgroundGroup>

#include <QVBoxLayout>
#include <QEvent>
#include <QDebug>

DWIDGET_USE_NAMESPACE

namespace dcc_fcitx_configtool {
namespace widgets {

FcitxSettingsGroup::FcitxSettingsGroup(QFrame *parent, BackgroundStyle bgStyle)
    : FcitxTranslucentFrame(parent)
    , m_layout(new QVBoxLayout)
    , m_headerItem(nullptr)
{
    m_layout->setSpacing(5);
    m_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vLayout = m_layout;
    if (GroupBackground == bgStyle) {
        vLayout = new QVBoxLayout;
        m_bggroup = new DBackgroundGroup(m_layout);
        m_bggroup->setBackgroundRole(QPalette::Window);
        m_bggroup->setItemSpacing(1);
        m_bggroup->setUseWidgetBackground(false);
        vLayout->addWidget(m_bggroup);
        vLayout->setContentsMargins(0, 0, 0, 0);
    }

    m_bgStyle = bgStyle;
    setLayout(vLayout);
}

FcitxSettingsGroup::FcitxSettingsGroup(const QString &title, QFrame *parent)
    : FcitxSettingsGroup(parent)
{
    setHeaderVisible(!title.isEmpty());
    setAccessibleName(title);

    m_headerItem->setTitle(title);
}

FcitxSettingsGroup::~FcitxSettingsGroup()
{
    if (m_headerItem)
        m_headerItem->deleteLater();
}

void FcitxSettingsGroup::setHeaderVisible(const bool visible)
{
    if (visible) {
        if (!m_headerItem)
            m_headerItem = new FcitxSettingsHeaderItem;
        insertItem(0, m_headerItem);
    } else {
        if (m_headerItem) {
            m_headerItem->deleteLater();
            m_headerItem = nullptr;
        }
    }
}

void FcitxSettingsGroup::insertItem(const int index, FcitxSettingsItem *item)
{
    if (ItemBackground == m_bgStyle) {
        //当SettingsItem 被加入　FcitxSettingsGroup　时，为其加入背景
        item->addBackground();
    }

    m_layout->insertWidget(index, item);
    item->installEventFilter(this);

    FcitxIMSettingsItem *mItem = dynamic_cast<FcitxIMSettingsItem *>(item);
    if (mItem)
        connect(mItem, &FcitxIMSettingsItem::itemClicked, [=](FcitxIMSettingsItem *myItem) {
            int i = itemCount();
            for (int j = 0; j < i; ++j) {
                if (this->getItem(j) != myItem) {
                    FcitxIMSettingsItem *Titem = dynamic_cast<FcitxIMSettingsItem *>(this->getItem(j));
                    if (Titem) {
                        Titem->setItemSelected(false);
                    }
                }
            }
        });
}

void FcitxSettingsGroup::appendItem(FcitxSettingsItem *item)
{
    insertItem(m_layout->count(), item);
}

void FcitxSettingsGroup::appendItem(FcitxSettingsItem *item, BackgroundStyle bgStyle)
{
    if ((ItemBackground == bgStyle) && (m_bgStyle == ItemBackground)) {
        //当SettingsItem 被加入　FcitxSettingsGroup　时，为其加入背景
        item->addBackground();
    }

    m_layout->insertWidget(m_layout->count(), item);
    item->installEventFilter(this);

    FcitxIMSettingsItem *mItem = dynamic_cast<FcitxIMSettingsItem *>(item);
    if (mItem)
        connect(mItem, &FcitxIMSettingsItem::itemClicked, [=](FcitxIMSettingsItem *myItem) {
            int i = itemCount();
            for (int j = 0; j < i; ++j) {
                if (this->getItem(j) != myItem) {
                    FcitxIMSettingsItem *Titem = dynamic_cast<FcitxIMSettingsItem *>(this->getItem(j));
                    if (Titem) {
                        Titem->setItemSelected(false);
                    }
                }
            }
        });
}

void FcitxSettingsGroup::removeItem(FcitxSettingsItem *item)
{
    if (!item)
        return;
    m_layout->removeWidget(item);
    item->removeEventFilter(this);
}

void FcitxSettingsGroup::moveItem(FcitxSettingsItem *item, const int index)
{
    const int oldIndex = m_layout->indexOf(item);
    if (oldIndex == index)
        return;

    m_layout->removeWidget(item);
    m_layout->insertWidget(index, item);
}

void FcitxSettingsGroup::setSpacing(const int spaceing)
{
    m_layout->setSpacing(spaceing);
    if (m_bggroup)
        m_bggroup->setItemSpacing(spaceing);
}

int FcitxSettingsGroup::itemCount() const
{
    return m_layout->count();
}

void FcitxSettingsGroup::clear()
{
    const int index = m_headerItem ? 1 : 0;
    const int count = m_layout->count();

    for (int i(index); i != count; ++i) {
        QLayoutItem *item = m_layout->takeAt(index);
        QWidget *w = item->widget();
        w->removeEventFilter(this);
        w->setParent(nullptr);
        delete item;
        w->deleteLater();
    }
}

FcitxSettingsItem *FcitxSettingsGroup::getItem(int index)
{
    if (index < 0)
        return nullptr;

    if (index < itemCount()) {
        return qobject_cast<FcitxSettingsItem *>(m_layout->itemAt(index)->widget());
    }

    return nullptr;
}

void FcitxSettingsGroup::insertWidget(QWidget *widget)
{
    m_layout->insertWidget(m_layout->count(), widget);
}
} // namespace widgets
} // namespace dcc_fcitx_configtool
