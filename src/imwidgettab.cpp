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

#include "imwidgettab.h"
#include "addimlistmodel.h"
#include "fcitxqthelper.h"

#include <fcitxqtinputmethodproxy.h>

#include <DWidget>
#include <DWidgetUtil>

#include <QVBoxLayout>
#include <QDebug>

ImWidgetTab::ImWidgetTab(QWidget *parent) : QLabel(parent)
{
    initUI();
    initSubUI();
    initConnect();
    fcitxUpdateIMList();
}

ImWidgetTab::~ImWidgetTab()
{
    imListModel->deleteLater();
    addImWidget->deleteLater();
}

void ImWidgetTab::initUI()
{
    imListModel = new IMListModel();

    auto *centralWidget = new DWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    auto *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    listView = new DListView(centralWidget);
    listView->setModel(imListModel);
    listView->setObjectName(QStringLiteral("listView"));
    verticalLayout->addWidget(listView);

    auto *label_2 = new QLabel(centralWidget);
    label_2->setObjectName(QStringLiteral("label_2"));
    verticalLayout->addWidget(label_2);

    auto *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    addimbutton = new DPushButton(centralWidget);
    addimbutton->setObjectName(QStringLiteral("addimbutton"));
    horizontalLayout->addWidget(addimbutton);
    delimbutton = new DPushButton(centralWidget);
    delimbutton->setObjectName(QStringLiteral("delimbutton"));
    horizontalLayout->addWidget(delimbutton);
    moveupbutton = new DPushButton(centralWidget);
    moveupbutton->setObjectName(QStringLiteral("moveupbutton"));
    horizontalLayout->addWidget(moveupbutton);
    movedownbutton = new DPushButton(centralWidget);
    movedownbutton->setObjectName(QStringLiteral("movedownbutton"));
    horizontalLayout->addWidget(movedownbutton);
    configurebutton = new DPushButton(centralWidget);
    configurebutton->setObjectName(QStringLiteral("configurebutton"));
    horizontalLayout->addWidget(configurebutton);
    defaultlayoutbutton = new DPushButton(centralWidget);
    defaultlayoutbutton->setObjectName(QStringLiteral("defaultlayoutbutton"));
    horizontalLayout->addWidget(defaultlayoutbutton);
    auto *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);

    addimbutton->setIcon(QIcon::fromTheme("list-add"));
    delimbutton->setIcon(QIcon::fromTheme("list-remove"));
    moveupbutton->setIcon(QIcon::fromTheme("go-up"));
    movedownbutton->setIcon(QIcon::fromTheme("go-down"));
    configurebutton->setIcon(QIcon::fromTheme("configure"));
    defaultlayoutbutton->setIcon(QIcon::fromTheme("preferences-desktop-keyboard"));

    configurebutton->setEnabled(false);

    label_2->setText("The first input method will be inactive state. Usually you need to put " \
                     "<b>Keyboard</b> or <b>Keyboard - <i>layout name</i></b> in the first place." \
                     "msgstr ");
    verticalLayout->addLayout(horizontalLayout);
}

void ImWidgetTab::initSubUI()
{
    addImWidget = new AddImWidget();
    addImWidget->hide();
}

void ImWidgetTab::fcitxUpdateIMList()
{
    auto *imProxy = FcitxQtHelper::instance()->getInputMethodProxy();
    if (imProxy) {
        imItemList = imProxy->iMList();
        std::stable_sort(imItemList.begin(), imItemList.end());
        emit updateIMList(imItemList, imProxy->currentIM());
    }
}

void ImWidgetTab::initConnect()
{
    connect(addimbutton, SIGNAL(clicked()), this, SLOT(fcitxImWidgetAddimButtonClicked()));
    connect(delimbutton, SIGNAL(clicked()), this, SLOT(fcitxImWidgetDelimButtonClicked()));
    connect(moveupbutton, SIGNAL(clicked()), this, SLOT(fcitxImWidgetMoveupButtonClicked()));
    connect(movedownbutton, SIGNAL(clicked()), this, SLOT(fcitxImWidgetMovedownButtonClicked()));
    connect(configurebutton, SIGNAL(clicked()), this, SLOT(fcitxImWidgetConfigureButtonClicked()));
    connect(defaultlayoutbutton, SIGNAL(clicked()), this, SLOT(fcitxImWidgetConfigureButtonClicked()));

    connect(imListModel, &IMListModel::updateListViewSelectdIndex,
            listView, &DListView::scrollTo);

    connect(this, &ImWidgetTab::updateIMList, imListModel, &IMListModel::filterIMEntryList);
    connect(addImWidget, &AddImWidget::updateIMList, imListModel, &IMListModel::filterIMEntryList);

    connect(imListModel, &IMListModel::select, [&](QModelIndex index) {
        listView->setCurrentIndex(index);
    });
}

void ImWidgetTab::fcitxImWidgetAddimButtonClicked()
{
    addImWidget->filterAddIMList();
    addImWidget->show();
    Dtk::Widget::moveToCenter(addImWidget);
}

void ImWidgetTab::fcitxImWidgetDelimButtonClicked()
{
    if (0 >= listView->count()) {
        return;
    }
    // remove item
    imListModel->rmSelectedItem(listView->currentIndex());
}

void ImWidgetTab::fcitxImWidgetMoveupButtonClicked()
{
    if (0 >= listView->count()) {
        return;
    }
    // remove item
    imListModel->moveUpItem(listView->currentIndex());
}

void ImWidgetTab::fcitxImWidgetMovedownButtonClicked()
{
    if (0 >= listView->count()) {
        return;
    }
    // remove item
    imListModel->moveDownItem(listView->currentIndex());
}

void ImWidgetTab::fcitxImWidgetConfigureButtonClicked()
{
    qDebug() << "fcitx_im_widget_configure_button_clicked";
}

void ImWidgetTab::fcitxImWidgetDefaultLayoutButtonClicked()
{
    qDebug() << "fcitx_im_widget_defaultlayoutbutton_clicked";
}

void ImWidgetTab::fcitxImWidgetRowActivated()
{
    qDebug() << "fcitx_im_widget_row_activated";
}

