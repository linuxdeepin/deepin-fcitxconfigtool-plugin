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
#include "imsettingsitem.h"
#include "settingsitem.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QLabel>
#include <QApplication>
#include <QFrame>
#include <DPalette>

DWIDGET_USE_NAMESPACE
namespace dcc_fcitx_configtool {
namespace widgets {
IMSettingsItem::IMSettingsItem(QString str, QFrame *parent)
    : SettingsItem(parent)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(20, 0, 10, 0);
    this->setLayout(m_layout);
    m_labelText = new QLabel(this);
    QFont ft;
    ft.setPointSize(12);
    m_labelText->setFont(ft);

    m_labelText->setText(str);
    m_labelIcon = new QLabel(this);
    m_layout->addWidget(m_labelText);
    m_layout->addStretch();
    m_layout->addWidget(m_labelIcon);
    this->setFixedHeight(40);
}

IMSettingsItem::~IMSettingsItem()
{
}

void IMSettingsItem::setFcitxItem(const FcitxQtInputMethodItem &item)
{
    m_item = item;
    m_labelText->setText(m_item.name());
    m_labelText->adjustSize();
}

void IMSettingsItem::setFilterStr(QString str)
{
    if (!(m_item.name().indexOf(str, Qt::CaseInsensitive) != -1
          || m_item.uniqueName().indexOf(str, Qt::CaseInsensitive) != -1
          || m_item.langCode().indexOf(str, Qt::CaseInsensitive) != -1)) {
        this->hide();
    } else {
        this->show();
    }
}

void IMSettingsItem::setItemSelected(bool status)
{
    if (status) {
        QIcon icon = DStyle::standardIcon(QApplication::style(), DStyle::SP_IndicatorChecked);
        m_labelIcon->setPixmap(icon.pixmap(QSize(20, 20)));
    } else {
        m_labelIcon->clear();
    }
}

void IMSettingsItem::mousePressEvent(QMouseEvent *event)
{
    setItemSelected(true);
    emit itemClicked(this);
}

void IMSettingsItem::enterEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ObviousBackground);
}

void IMSettingsItem::leaveEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
}
}
}
