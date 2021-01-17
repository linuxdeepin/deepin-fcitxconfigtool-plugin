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

#include "addimwidget.h"

#include <fcitxqtinputmethodproxy.h>
#include "fcitxqthelper.h"

#include <QVBoxLayout>
#include <DListView>
#include <DCheckBox>
#include <DLineEdit>
#include <DPushButton>

AddImWidget::AddImWidget(QWidget *parent) :
    DWidget(parent)
{
    initUI();
    initConnect();
    filterAddIMList();
}

AddImWidget::~AddImWidget()
{
    addimListModel->deleteLater();
}

void AddImWidget::initUI()
{
    addimListModel = new AddIMListModel();

    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;

    this->resize(424, 383);
    auto *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    listview = new DListView(this);
    listview->setModel(addimListModel);
    listview->setObjectName(QStringLiteral("listWidget"));
    verticalLayout->addWidget(listview);
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    checkBox = new DCheckBox(this);
    checkBox->setObjectName(QStringLiteral("checkBox"));
    horizontalLayout->addWidget(checkBox);
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);
    verticalLayout->addLayout(horizontalLayout);

    searchEdit = new DSearchEdit(this);
    searchEdit->setObjectName(QStringLiteral("searchEdit"));
    verticalLayout->addWidget(searchEdit);
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_2->addItem(horizontalSpacer_2);
    ptCancel = new DPushButton(this);
    ptCancel->setObjectName(QStringLiteral("ptCancel"));
    horizontalLayout_2->addWidget(ptCancel);
    ptSure = new DPushButton(this);
    ptSure->setObjectName(QStringLiteral("ptSure"));
    horizontalLayout_2->addWidget(ptSure);
    verticalLayout->addLayout(horizontalLayout_2);

    setWindowTitle("Add input method");
    searchEdit->setPlaceholderText("Search Input Method");

    checkBox->setText("Only Show Current Language");
    ptCancel->setText(tr("Cancle"));
    ptSure->setText("Sure");
}

void AddImWidget::initConnect()
{
    connect(ptSure, &DPushButton::clicked, this, &AddImWidget::onSureBt);
    connect(ptCancel, &DPushButton::clicked, this, &AddImWidget::onCloseBt);
    connect(checkBox, &DCheckBox::stateChanged, this, &AddImWidget::filterAddIMList);
    connect(searchEdit, &DLineEdit::textChanged, this, &AddImWidget::onTextChanged);

    connect(this, &AddImWidget::addIm, addimListModel, &AddIMListModel::addSelectedItem);
}

void AddImWidget::filterAddIMList()
{
    ImItemList.clear();
    auto *imProxy = FcitxQtHelper::instance()->getInputMethodProxy();
    if (imProxy) {
        FcitxQtInputMethodItemList allImItemList = imProxy->iMList();
        if (checkBox->checkState()) {
            //get current language from system api
            QString currLanguageCode = "zh_CN";
            //check language
            for (auto im : allImItemList) {
                if (currLanguageCode == im.langCode()) {
                    ImItemList.append(im);
                }
            }
        } else {
            ImItemList = allImItemList;
        }
        addimListModel->filterAddModelIMList(ImItemList, QString());
    }
}

void AddImWidget::onCloseBt()
{
    this->close();
}

void AddImWidget::onSureBt()
{
    emit addIm(listview->currentIndex());
    emit updateIMList(ImItemList, QString());
    this->close();
}

void AddImWidget::onTextChanged(const QString &str)
{
    if (str.isEmpty()) {
        addimListModel->filterAddModelIMList(ImItemList, QString());
        return ;
    }

    FcitxQtInputMethodItemList currImList ;
    for (auto im : ImItemList) {
        if (-1 != im.name().indexOf(str, 0, Qt::CaseInsensitive)) {
            currImList.append(im);
        }
    }
    addimListModel->filterAddModelIMList(currImList, QString());
}

