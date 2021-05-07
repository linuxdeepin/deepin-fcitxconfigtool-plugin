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

#include "imactivityitem.h"
#include "publisher/publisherdef.h"
#include "window/immodel/immodel.h"
#include <DToolButton>
#include <DFontSizeManager>
#include <QTimer>
using namespace Dtk::Widget;
namespace dcc_fcitx_configtool {
namespace widgets {

Fcitx_IMActivityItem::Fcitx_IMActivityItem(FcitxQtInputMethodItem item, bool isFirst, QFrame *parent)
    : Fcitx_SettingsItem(parent)
    , m_isFirst(isFirst)
    , m_item(item)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(10, 0, 10, 0);
    m_labelText = new Fcitx_ShortenLabel("", this);
    DFontSizeManager::instance()->bind(m_labelText, DFontSizeManager::T6);
    m_labelText->setShortenText(item.name());
    m_layout->addWidget(m_labelText);
    if (!m_isFirst) {
        m_upBtn = new DToolButton(this);
        m_downBtn = new DToolButton(this);
        m_configBtn = new DToolButton(this);
        m_deleteBtn = new DToolButton(this);//input_method
        m_upBtn->setIcon(QIcon::fromTheme("arrow_up"));
        m_downBtn->setIcon(QIcon::fromTheme("arrow_down"));
        m_configBtn->setIcon(QIcon::fromTheme("setting"));
        m_deleteBtn->setIcon(DStyle::standardIcon(QApplication::style(), DStyle::SP_DeleteButton));

        m_layout->addWidget(m_downBtn);
        m_layout->addWidget(m_upBtn);
        m_layout->addWidget(m_configBtn);
        m_layout->addWidget(m_deleteBtn);
        m_deleteBtn->hide();
        m_upBtn->hide();
        m_configBtn->hide();
        m_downBtn->hide();

        connect(m_upBtn, &DToolButton::clicked, this, &Fcitx_IMActivityItem::onUpItem);
        connect(m_downBtn, &DToolButton::clicked, this, &Fcitx_IMActivityItem::onDownItem);
        connect(m_configBtn, &DToolButton::clicked, this, &Fcitx_IMActivityItem::onConfigItem);
        connect(m_deleteBtn, &DToolButton::clicked, this, &Fcitx_IMActivityItem::onDeleteItem);
    }

    this->setFixedHeight(40);
    this->setLayout(m_layout);
}

Fcitx_IMActivityItem::~Fcitx_IMActivityItem()
{
}

void Fcitx_IMActivityItem::editSwitch(const bool &flag)
{
    if (m_isFirst)
        return;
    m_isEdit = flag;
    if (m_isEdit) {
        m_deleteBtn->show();
        m_configBtn->hide();
        m_upBtn->hide();
        m_downBtn->hide();
    } else {
        m_deleteBtn->hide();
    }
}

void Fcitx_IMActivityItem::setSelectStatus(const bool &isEnter)
{
    if (m_isFirst || !m_bgGroup)
        return;

    if (!isEnter)
        m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
    else {
        m_bgGroup->setBackgroundRole(DPalette::ObviousBackground);
    }
    if (!m_isEdit && isEnter) {
        int index = IMModel::instance()->getIMIndex(m_item);
        int count = IMModel::instance()->getCurIMList().count();

        if (count <= 2) {
            m_upBtn->setEnabled(false);
            m_downBtn->setEnabled(false);
        }else if (index == 1) {
            m_upBtn->setEnabled(false);
            m_downBtn->setEnabled(true);
        } else if (index == count - 1) {
            m_upBtn->setEnabled(true);
            m_downBtn->setEnabled(false);
        } else {
            m_upBtn->setEnabled(true);
            m_downBtn->setEnabled(true);
        }
        m_configBtn->show();
        m_upBtn->show();
        m_downBtn->show();
        update();
    } else {
        m_configBtn->hide();
        m_upBtn->hide();
        m_downBtn->hide();
    }
}

void Fcitx_IMActivityItem::onUpItem()
{
    emit upBtnClicked(m_item);
}

void Fcitx_IMActivityItem::onDownItem()
{
    emit downBtnClicked(m_item);
}

void Fcitx_IMActivityItem::onConfigItem()
{
    emit configBtnClicked(m_item);
}

void Fcitx_IMActivityItem::onDeleteItem()
{
    emit deleteBtnClicked(m_item);
}

void Fcitx_IMActivityItem::enterEvent(QEvent *event)
{
    setSelectStatus(true);
    Fcitx_SettingsItem::enterEvent(event);
}

void Fcitx_IMActivityItem::leaveEvent(QEvent *event)
{
    setSelectStatus(false);
    Fcitx_SettingsItem::leaveEvent(event);
}

void ToolButton::paintEvent(QPaintEvent *e)
{
    if (isEnabled()) {
        QToolButton::paintEvent(e);
    } else {
        QPainter p(this);
        p.drawPixmap({(width() - 16) / 2, (height() - 16) / 2, 16, 16}, icon().pixmap(16, 16, QIcon::Mode::Disabled));
    }
}

} // namespace widgets
} // namespace dcc_fcitx_configtool
