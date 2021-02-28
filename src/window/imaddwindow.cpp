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
#include "widgets/buttontuple.h"
#include <DCommandLinkButton>
#include <DSearchEdit>
#include <DFontSizeManager>
#include <QProcess>
using namespace dcc_fcitx_configtool::widgets;

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
    //界面布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 10);
    mainLayout->setSpacing(0);
    mainLayout->addSpacing(10);

    //添加输入法标题
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    TitleLabel *title = new TitleLabel(tr("Add Input Method"), this);
    DFontSizeManager::instance()->bind(title, DFontSizeManager::T3, QFont::DemiBold); // 设置label字体
    hlayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlayout->addWidget(title);
    hlayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    //搜索框
    QHBoxLayout *hlayout2 = new QHBoxLayout(this);
    m_searchLEdit = new DSearchEdit(this);
    m_searchLEdit->setText(tr("Search"));
    hlayout2->addSpacing(10);
    hlayout2->addWidget(m_searchLEdit);
    hlayout2->addSpacing(10);

    //可用输入法列表
    m_availWidget = new AvailWidget(this);

    //应用商店按钮
    QHBoxLayout *hlayout3 = new QHBoxLayout(this);
    hlayout3->addStretch();
    m_storeBtn = new DCommandLinkButton(tr("Find more in App Store"), this);
    hlayout3->addWidget(m_storeBtn);
    hlayout3->addSpacing(10);

    //添加 取消按钮
    m_buttonTuple = new ButtonTuple(ButtonTuple::Save);
    m_buttonTuple->rightButton()->setText(tr("Add"));
    m_buttonTuple->rightButton()->setEnabled(false);
    m_buttonTuple->leftButton()->setText(tr("Cancel"));
    QHBoxLayout *hlayout4 = new QHBoxLayout(this);
    hlayout4->addSpacing(10);
    hlayout4->addWidget(m_buttonTuple, 0, Qt::AlignBottom);
    hlayout4->addSpacing(10);

    //添加至主界面内
    mainLayout->addLayout(hlayout);
    mainLayout->addLayout(hlayout2);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(m_availWidget);
    mainLayout->addSpacing(6);
    mainLayout->addLayout(hlayout3);
    mainLayout->addSpacing(7);
    mainLayout->addLayout(hlayout4);
    setLayout(mainLayout);
}

void IMAddWindow::initConnect()
{
    connect(m_storeBtn, &DCommandLinkButton::clicked, this, &IMAddWindow::onOpenStore);
    connect(m_buttonTuple->rightButton(), &QPushButton::clicked, this, &IMAddWindow::onAddIM);
    connect(m_buttonTuple->leftButton(), &QPushButton::clicked, this, &IMAddWindow::popSettingsWindow);
    connect(m_availWidget, &AvailWidget::seleteIM, m_buttonTuple->rightButton(), &QPushButton::setEnabled);
    connect(m_searchLEdit, &DSearchEdit::textChanged, m_availWidget, &AvailWidget::onSearchIM);
    connect(this, &IMAddWindow::addIM, IMModel::instance(), &IMModel::onAddIMItem);
}

void IMAddWindow::updateUI()
{
    m_buttonTuple->rightButton()->setEnabled(false);
    m_buttonTuple->leftButton()->setDefault(true);
    if (!m_searchLEdit->text().isEmpty())
        m_searchLEdit->clear();
    m_availWidget->clearItemStatus();
}

void IMAddWindow::onAddIM()
{
    emit addIM(m_availWidget->getSeleteIm());
    emit popSettingsWindow();
}

void IMAddWindow::onOpenStore()
{
    QProcess::startDetached("deepin-app-store");
}
