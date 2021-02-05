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
#include "imaddwindow.h"
#include "availwidget.h"
#include "immodel/immodel.h"
#include "widgets/titlelabel.h"
#include <QGroupBox>
#include <QProcess>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QApplication>
#include <fcitxInterface/global.h>

using namespace Fcitx;

IMAddWindow::IMAddWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnect();
}

IMAddWindow::~IMAddWindow()
{
}

void IMAddWindow::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 0, 10, 0);
    mainLayout->setSpacing(0);
    {
        QHBoxLayout *hlayout = new QHBoxLayout();
        TitleLabel *title = new TitleLabel(tr("Add Input Method"), this);
        DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
        hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        hlayout->addWidget(title);
        hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        mainLayout->addLayout(hlayout);
    }
    m_searchLEdit = new DSearchEdit(this);
    m_searchLEdit->setText(tr("Search"));

    {
        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Maximum));
        hlayout->addWidget(m_searchLEdit);
        hlayout->addItem(new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Maximum));

        mainLayout->addLayout(hlayout);
    }

    mainLayout->addSpacing(20);
    m_availWidget = new AvailWidget(this);
    mainLayout->addWidget(m_availWidget);

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addStretch();
    m_storeBtn = new DCommandLinkButton(tr("Find more in App Store"), this);

    hlayout2->addWidget(m_storeBtn);
    mainLayout->addLayout(hlayout2);

    m_buttonTuple = new ButtonTuple(ButtonTuple::Save);
    m_buttonTuple->rightButton()->setText(tr("Add"));
    m_buttonTuple->rightButton()->setEnabled(false);
    m_buttonTuple->leftButton()->setText(tr("Cancel"));

    mainLayout->addWidget(m_buttonTuple, 0, Qt::AlignBottom);
}

void IMAddWindow::initConnect()
{
    connect(m_storeBtn, &DCommandLinkButton::clicked, this, &IMAddWindow::slot_openStore);
    connect(m_buttonTuple->rightButton(), &QPushButton::clicked, this, &IMAddWindow::slot_addIM);
    connect(m_buttonTuple->leftButton(), &QPushButton::clicked, this, &IMAddWindow::sig_popSettingsWindow);
    connect(m_availWidget, &AvailWidget::sig_seleteIM, m_buttonTuple->rightButton(), &QPushButton::setEnabled);
    connect(m_searchLEdit, &DSearchEdit::textChanged, m_availWidget, &AvailWidget::slot_searchIM);
}

void IMAddWindow::updateUI()
{
    m_buttonTuple->rightButton()->setEnabled(false);
    m_buttonTuple->leftButton()->setDefault(true);
    if (!m_searchLEdit->text().isEmpty())
        m_searchLEdit->clear();
    m_availWidget->clearItemStatus();
}

void IMAddWindow::slot_addIM()
{
    IMModel::instance()->addIMItem(m_availWidget->getSeleteIm());
    emit sig_popSettingsWindow();
}

void IMAddWindow::slot_openStore()
{
    QProcess::startDetached("deepin-app-store");
}
