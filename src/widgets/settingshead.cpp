/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
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

#include "settingshead.h"
#include "labels/normallabel.h"

#include <DCommandLinkButton>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <DFontSizeManager>

using namespace dcc_fcitx_configtool::widgets;
DWIDGET_USE_NAMESPACE

Fcitx_SettingsHead::Fcitx_SettingsHead(QFrame *parent)
    : Fcitx_SettingsItem(parent)
    , m_title(new Fcitx_TitleLabel)
    , m_edit(new DCommandLinkButton(""))
    , m_state(Cancel)
{
    m_title->setObjectName("SettingsHeadTitle");

    // can not translate correctly just using tr()
    m_edit->setText(qApp->translate("Fcitx_SettingsHead", "Edit"));
    DFontSizeManager::instance()->bind(m_title, DFontSizeManager::T5, QFont::DemiBold);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(20, 20, 10, 0);
    mainLayout->addWidget(m_title);
    mainLayout->addStretch();
    mainLayout->addWidget(m_edit);

    setLayout(mainLayout);

    connect(m_edit, &DCommandLinkButton::clicked, this, &Fcitx_SettingsHead::onClicked);
}

void Fcitx_SettingsHead::setTitle(const QString &title)
{
    m_title->setText(title);
    m_edit->setAccessibleName(title);
}

void Fcitx_SettingsHead::setEditEnable(bool state)
{
    m_edit->setVisible(state);
}

void Fcitx_SettingsHead::toEdit()
{
    m_state = Edit;
    refershButton();

    Q_EMIT editChanged(true);
}

void Fcitx_SettingsHead::toCancel()
{
    m_state = Cancel;
    refershButton();

    Q_EMIT editChanged(false);
}

void Fcitx_SettingsHead::setEdit(bool flag)
{
    if (flag) {
        m_state = Edit;
        refershButton();
    } else {
        m_state = Cancel;
        refershButton();
    }
}

void Fcitx_SettingsHead::onClicked()
{
    if (m_state == Cancel) {
        toEdit();
    } else {
        toCancel();
    }
}

void Fcitx_SettingsHead::refershButton()
{
    if (m_state == Cancel) {
        m_edit->setText(qApp->translate("Fcitx_SettingsHead", "Edit"));
    } else {
        m_edit->setText(qApp->translate("Fcitx_SettingsHead", "Done"));
    }
}
