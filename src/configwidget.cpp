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

#include "configwidget.h"

#include <QSpacerItem>
#include <QHBoxLayout>
#include <QGridLayout>

#include <DComboBox>
#include <DLabel>
#include <DListView>
#include <DKeySequenceEdit>
#include <DToolButton>
#include <DPushButton>

configwidget::configwidget(QWidget *parent) :
    DWidget(parent)
{
    initUI();
}

configwidget::~configwidget()
{
}

void configwidget::initUI()
{
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;

    this->resize(499, 609);
    this->setObjectName(QStringLiteral("configwidget"));

    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    auto *label = new DLabel(this);
    label->setObjectName(QStringLiteral("label"));
    horizontalLayout->addWidget(label);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);
    verticalLayout_2->addLayout(horizontalLayout);

    auto *comboBox = new DComboBox(this);
    comboBox->setObjectName(QStringLiteral("comboBox"));
    verticalLayout_2->addWidget(comboBox);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

    auto *label_2 = new DLabel(this);
    label_2->setObjectName(QStringLiteral("label_2"));
    horizontalLayout_2->addWidget(label_2);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_2->addItem(horizontalSpacer_2);
    verticalLayout_2->addLayout(horizontalLayout_2);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

    auto *label_3 = new DLabel(this);
    label_3->setObjectName(QStringLiteral("label_3"));
    horizontalLayout_3->addWidget(label_3);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_3);
    verticalLayout_2->addLayout(horizontalLayout_3);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));

    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout_5->addItem(horizontalSpacer_5);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    auto *label_4 = new DLabel(this);
    label_4->setObjectName(QStringLiteral("label_4"));
    gridLayout->addWidget(label_4, 0, 0, 1, 1);

    auto *pushButton = new DKeySequenceEdit(this);
    pushButton->setObjectName(QStringLiteral("pushButton"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
    pushButton->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton, 0, 1, 1, 1);

    auto *pushButton_2 = new DKeySequenceEdit(this);
    pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
    sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
    pushButton_2->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_2, 0, 2, 1, 1);

    auto *label_5 = new DLabel(this);
    label_5->setObjectName(QStringLiteral("label_5"));
    gridLayout->addWidget(label_5, 1, 0, 1, 1);

    auto *pushButton_3 = new DKeySequenceEdit(this);
    pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
    sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
    pushButton_3->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_3, 1, 1, 1, 1);

    auto *pushButton_4 = new DKeySequenceEdit(this);
    pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
    sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
    pushButton_4->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_4, 1, 2, 1, 1);

    auto *label_6 = new DLabel(this);
    label_6->setObjectName(QStringLiteral("label_6"));
    gridLayout->addWidget(label_6, 2, 0, 1, 1);

    auto *pushButton_6 = new DKeySequenceEdit(this);
    pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
    sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
    pushButton_6->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_6, 2, 1, 1, 1);

    auto *pushButton_5 = new DKeySequenceEdit(this);
    pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
    sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
    pushButton_5->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_5, 2, 2, 1, 1);

    auto *label_7 = new DLabel(this);
    label_7->setObjectName(QStringLiteral("label_7"));
    gridLayout->addWidget(label_7, 3, 0, 1, 1);

    auto *pushButton_7 = new DKeySequenceEdit(this);
    pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
    sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
    pushButton_7->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_7, 3, 1, 1, 1);

    auto *pushButton_8 = new DKeySequenceEdit(this);
    pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
    sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
    pushButton_8->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_8, 3, 2, 1, 1);

    auto *label_8 = new DLabel(this);
    label_8->setObjectName(QStringLiteral("label_8"));
    gridLayout->addWidget(label_8, 4, 0, 1, 1);

    auto *pushButton_10 = new DKeySequenceEdit(this);
    pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
    sizePolicy.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
    pushButton_10->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_10, 4, 1, 1, 1);

    auto *pushButton_9 = new DKeySequenceEdit(this);
    pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
    sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
    pushButton_9->setSizePolicy(sizePolicy);
    gridLayout->addWidget(pushButton_9, 4, 2, 1, 1);
    horizontalLayout_5->addLayout(gridLayout);
    verticalLayout_2->addLayout(horizontalLayout_5);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));

    auto *label_9 = new DLabel(this);
    label_9->setObjectName(QStringLiteral("label_9"));
    horizontalLayout_4->addWidget(label_9);

    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_4->addItem(horizontalSpacer_4);
    verticalLayout_2->addLayout(horizontalLayout_4);

    horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));

    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));

    horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout_6->addItem(horizontalSpacer_6);

    auto *label_10 = new DLabel(this);
    label_10->setObjectName(QStringLiteral("label_10"));
    horizontalLayout_6->addWidget(label_10);
    verticalLayout->addLayout(horizontalLayout_6);
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);
    horizontalLayout_9->addLayout(verticalLayout);

    auto *listView = new DListView(this);
    listView->setObjectName(QStringLiteral("listView"));
    horizontalLayout_9->addWidget(listView);
    verticalLayout_2->addLayout(horizontalLayout_9);

    horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
    horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_8->addItem(horizontalSpacer_9);

    auto *toolButton = new DToolButton(this);
    toolButton->setObjectName(QStringLiteral("toolButton"));
    horizontalLayout_8->addWidget(toolButton);

    horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_8->addItem(horizontalSpacer_8);
    verticalLayout_2->addLayout(horizontalLayout_8);

    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));

    horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_7->addItem(horizontalSpacer_7);

    auto *pushButton_11 = new DPushButton(this);
    pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
    horizontalLayout_7->addWidget(pushButton_11);

    auto *pushButton_12 = new DPushButton(this);
    pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
    horizontalLayout_7->addWidget(pushButton_12);
    verticalLayout_2->addLayout(horizontalLayout_7);

    label->setText("label");
    label_2->setText("label_2");
    label_3->setText("label_3");
    label_4->setText("label_4");
    label_5->setText("label_5");
    label_6->setText("label_6");
    label_7->setText("label_7");
    label_8->setText("label_8");
    label_9->setText("label_9");
    label_10->setText("label_10");
    toolButton->setText("config");
//    listView->addItem("additem");

}

