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

#include "mainwindow.h"
#include "imwidgettab.h"
#include "fcitxqthelper.h"

#include <fcitxqtkeyboardlayout.h>
#include <fcitxqtinputmethoditem.h>

#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QLayout>

#include <DTitlebar>
#include <DApplication>

DTK_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : DMainWindow(parent)
{
    FcitxQtInputMethodItem::registerMetaType();
    FcitxQtKeyboardLayout::registerMetaType();
    FcitxQtHelper::instance();

    initUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    //TabWidget
    auto *inputMethodTab = new ImWidgetTab(this);
    auto *globalConfigWidgetsTab = new QLabel(this);
    auto *appearanceWidgetsTab = new QLabel(this);
    auto *addonWidgetsTab = new QLabel(this);

    m_mainTab = new DTabWidget(this);
    m_mainTab->addTab(inputMethodTab, "Input Method");
    m_mainTab->addTab(globalConfigWidgetsTab, "Global Config");
    m_mainTab->addTab(appearanceWidgetsTab, "Appearance");
    m_mainTab->addTab(addonWidgetsTab, "Addon");

    m_mainTab->setCurrentIndex(0);

    //Layout
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->addWidget(m_mainTab);

    auto *centralWidget = new DWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}


