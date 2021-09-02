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

FcitxIMActivityItem::FcitxIMActivityItem(FcitxQtInputMethodItem item, QFrame *parent)
    : FcitxSettingsItem(parent)
    , m_item(item)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(10, 0, 10, 0);
    m_labelText = new FcitxShortenLabel("", this);
    DFontSizeManager::instance()->bind(m_labelText, DFontSizeManager::T6);
    m_labelText->setShortenText(item.name());
    m_labelText->setAccessibleName(item.name());
    m_labelText->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_layout->addWidget(m_labelText);
    m_upBtn = new DToolButton(this);
    m_downBtn = new DToolButton(this);
    m_configBtn = new DToolButton(this);
    m_deleteLabel = new ClickLabel (this);
    m_upBtn->setIcon(QIcon::fromTheme("arrow_up"));
    m_upBtn->setAccessibleName(item.name()+":arrow_up");
    m_downBtn->setIcon(QIcon::fromTheme("arrow_down"));
    m_downBtn->setAccessibleName(item.name()+":arrow_down");
    m_configBtn->setIcon(QIcon::fromTheme("setting"));
    m_configBtn->setAccessibleName(item.name()+":setting");
    m_deleteLabel->setIcon(DStyle::standardIcon(QApplication::style(), DStyle::SP_DeleteButton));
    m_deleteLabel->setAccessibleName(item.name()+":delete");
    m_deleteLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    m_layout->addWidget(m_downBtn);
    m_layout->addWidget(m_upBtn);
    m_layout->addWidget(m_configBtn);
    m_layout->addWidget(m_deleteLabel, 0, Qt::AlignRight);

    m_deleteLabel->hide();
    m_upBtn->hide();
    m_configBtn->hide();
    m_downBtn->hide();

    connect(m_upBtn, &DToolButton::clicked, this, &FcitxIMActivityItem::onUpItem);
    connect(m_downBtn, &DToolButton::clicked, this, &FcitxIMActivityItem::onDownItem);
    connect(m_configBtn, &DToolButton::clicked, this, &FcitxIMActivityItem::onConfigItem);
    connect(m_deleteLabel, &ClickLabel::clicked, this, &FcitxIMActivityItem::onDeleteItem);

    this->setFixedHeight(40);
    this->setLayout(m_layout);
}

FcitxIMActivityItem::~FcitxIMActivityItem()
{
}

void FcitxIMActivityItem::editSwitch(const bool &flag)
{
    m_isEdit = flag;
    if (m_isEdit) {
        m_deleteLabel->show();
        m_configBtn->hide();
        m_upBtn->hide();
        m_downBtn->hide();
    } else {
        m_deleteLabel->hide();
    }
}

void FcitxIMActivityItem::setSelectStatus(const bool &isEnter)
{
    if (!m_bgGroup)
        return;

    if (!isEnter)
        m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
    else {
        m_bgGroup->setBackgroundRole(DPalette::ObviousBackground);
    }
    if (!m_isEdit && isEnter) {
        int index = IMModel::instance()->getIMIndex(m_item);
        int count = IMModel::instance()->getCurIMList().count();

        if (count <= 1) {
            m_upBtn->setEnabled(false);
            m_downBtn->setEnabled(false);
        }else if (index == 0) {
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

void FcitxIMActivityItem::onUpItem()
{
    emit upBtnClicked(m_item);
}

void FcitxIMActivityItem::onDownItem()
{
    emit downBtnClicked(m_item);
}

void FcitxIMActivityItem::onConfigItem()
{
    emit configBtnClicked(m_item);
}

void FcitxIMActivityItem::onDeleteItem()
{
    emit deleteBtnClicked(m_item);
}

void FcitxIMActivityItem::enterEvent(QEvent *event)
{
    setSelectStatus(true);
    FcitxSettingsItem::enterEvent(event);
}

void FcitxIMActivityItem::leaveEvent(QEvent *event)
{
    setSelectStatus(false);
    FcitxSettingsItem::leaveEvent(event);
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
