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
#include "imsettingwindow.h"
#include "immodel/immodel.h"
#include "immodel/imconfig.h"
#include "widgets/utils.h"
#include "widgets/titlelabel.h"
#include "widgets/keysettingsitem.h"
#include "widgets/settingsgroup.h"
#include "widgets/settingshead.h"

#include <QComboBox>
#include <QGroupBox>
#include <QScrollArea>
#include <fcitxInterface/global.h>
#include <libintl.h>

using namespace Fcitx;

IMSettingWindow::IMSettingWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnect();
    updateUI();
}

IMSettingWindow::~IMSettingWindow()
{
    //writeConfig();
}

void IMSettingWindow::updateUI()
{
    if (IMModel::instance()->isEdit())
        slot_editBtnClicked();
    readConfig();
}

void IMSettingWindow::initUI()
{
    auto createTitle = [this](QString str) {
        TitleLabel *title = new TitleLabel(str, this);
        DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
        return title;
    };

    auto createGroup = [this](QWidget *widget) {
        QGroupBox *groupBox = new QGroupBox(this);
        groupBox->setFixedHeight(60);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(widget);
        groupBox->setLayout(layout);
        return groupBox;
    };

    //界面布局
    //输入法标签
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createTitle(tr("Input Method")));
    //默认输入法
    m_defualtIMCbox = new ComboxWidget(tr("Default"));
    m_defualtIMCbox->setParent(this);
    foreach (auto it, IMModel::instance()->curIMList()) {
        m_defualtIMCbox->comboBox()->addItem(it.name());
    }

    mainLayout->addWidget(createGroup(m_defualtIMCbox));
    mainLayout->addSpacing(20);
    //输入法管理标签 编辑按钮
    QHBoxLayout *headLayout = new QHBoxLayout(this);
    headLayout->setContentsMargins(0, 0, 0, 0);

    headLayout->addWidget(createTitle(tr("Manage Input Methods")));
    m_editBtn = new DCommandLinkButton(tr("Edit"), this);
    headLayout->addStretch();
    headLayout->addWidget(m_editBtn);
    mainLayout->addLayout(headLayout);
    //输入法列表
    m_IMCurrentView = new DListView(this);
    m_IMCurrentView->setDragEnabled(true);
    m_IMCurrentView->setAcceptDrops(true);
    m_IMCurrentView->setDropIndicatorShown(true);
    m_IMCurrentView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_IMCurrentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_IMCurrentView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_IMCurrentView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_IMCurrentView->setItemSpacing(2);
    m_IMCurrentView->setItemSize(QSize(100, 48));
    m_IMCurrentView->setModel(IMModel::instance());
    mainLayout->addWidget(m_IMCurrentView);
    mainLayout->addSpacing(20);

    //滑动窗口
    mainLayout->addWidget(createTitle(tr("Shortcuts")));
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollAreaWidgetContents = new QWidget(scrollArea);
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 382, 209));
    QGridLayout *gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setSpacing(6);
    gridLayout_2->addLayout(vLayout, 0, 0, 1, 1);
    scrollArea->setWidget(scrollAreaWidgetContents);
    mainLayout->addWidget(scrollArea);
    scrollArea->setMinimumHeight(190);
    //快捷键标签
    m_shortGroup = new SettingsGroup;
    m_shortGroup->setParent(this);
    //快捷键设置 切换输入法 切换虚拟键盘 切换至默认输入法
    m_imSwitchCbox = new ComBoboxSettingsItem(tr("Switch input methods"), {"CTRL_SHIFT", "ALT_SHIFT", "CTRL_SUPER", "ALT_SUPER"});
    m_imSwitchCbox->setParent(this);
    m_defualtIMKey = new KeySettingsItem(tr("Switch to default input method"));
    m_defualtIMKey->setParent(this);
    m_virtualKey = new KeySettingsItem(tr("Call out Onboard"));
    m_virtualKey->setParent(this);
    m_shortGroup->appendItem(m_imSwitchCbox);
    m_shortGroup->appendItem(m_defualtIMKey);
    m_shortGroup->appendItem(m_virtualKey);
    vLayout->addWidget(m_shortGroup);

    //切换方式
    m_systemAppCbox = new ComboxWidget(tr("切换方式"));
    m_systemAppCbox->setParent(this);
    m_systemAppCbox->comboBox()->addItems({tr("系统"), tr("应用")});
    mainLayout->addWidget(m_systemAppCbox);
    mainLayout->addStretch();
    m_systemAppCbox->hide();
    //添加界面按钮
    QHBoxLayout *headLayout2 = new QHBoxLayout(this);
    headLayout2->setContentsMargins(0, 0, 0, 0);
    headLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_addIMBtn = new DFloatingButton(DStyle::SP_IncreaseElement, this);
    headLayout2->addWidget(m_addIMBtn);
    headLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(headLayout2);
    this->setLayout(mainLayout);
    readConfig();
}

void IMSettingWindow::initConnect()
{
    connect(m_addIMBtn, &DFloatingButton::clicked, this, &IMSettingWindow::sig_popIMAddWindow);
    connect(m_editBtn, &DCommandLinkButton::clicked, this, &IMSettingWindow::slot_editBtnClicked);
    connect(m_defualtIMCbox, &ComboxWidget::onSelectChanged, this, &IMSettingWindow::slot_defualtIMChanged);
    connect(IMModel::instance(), &IMModel::sig_curIMList, this, &IMSettingWindow::slot_curIMChanged);

    auto reload = [=]() {
        if (Global::instance()->inputMethodProxy())
            Global::instance()->inputMethodProxy()->ReloadConfig();
    };
    connect(m_defualtIMKey, &KeySettingsItem::editedFinish, [=]() {
        IMConfig::setDefualtIMKey(m_defualtIMKey->getKeyToStr());
        reload();
    });
    connect(m_virtualKey, &KeySettingsItem::editedFinish, [=]() {
        IMConfig::setVirtualKey(m_virtualKey->getKeyToStr());
        reload();
    });
    connect(m_imSwitchCbox->comboBox(), &QComboBox::currentTextChanged, [=]() {
        IMConfig::setIMSwitch(m_imSwitchCbox->comboBox()->currentText());
        reload();
    });
}

void IMSettingWindow::readConfig()
{
    int index = m_imSwitchCbox->comboBox()->findText(IMConfig::IMSwitch());
    if (index < 0) {
        index = 0;
    }
    m_imSwitchCbox->comboBox()->setCurrentIndex(index);

    index = IMModel::instance()->getIMIndex(IMConfig::defualtIM());
    if (index < 0) {
        index = 0;
    }
    m_defualtIMCbox->comboBox()->setCurrentIndex(index);
    m_defualtIMKey->setList(IMConfig::defualtIMKey().split("_"));
    m_virtualKey->setList(IMConfig::virtualKey().split("_"));
}

void IMSettingWindow::writeConfig()
{
    IMConfig::setIMSwitch(m_imSwitchCbox->comboBox()->currentText());
    FcitxQtInputMethodItem item = IMModel::instance()->getIM(m_defualtIMCbox->comboBox()->currentIndex());
    if (!item.uniqueName().isEmpty())
        IMConfig::setDefualtIM(item.uniqueName());
    if (!m_virtualKey->getKeyToStr().isEmpty())
        IMConfig::setVirtualKey(m_virtualKey->getKeyToStr());
    if (!m_defualtIMKey->getKeyToStr().isEmpty())
        IMConfig::setDefualtIMKey(m_defualtIMKey->getKeyToStr());
    if (Global::instance()->inputMethodProxy())
        Global::instance()->inputMethodProxy()->ReloadConfig();
}

void IMSettingWindow::slot_editBtnClicked()
{
    bool flag = IMModel::instance()->isEdit();
    if (!flag) {
        m_editBtn->setText(tr("完成"));
        m_IMCurrentView->setSelectionMode(QAbstractItemView::NoSelection);
    } else {
        m_editBtn->setText(tr("Edit"));
        m_IMCurrentView->setSelectionMode(QAbstractItemView::SingleSelection);
    }

    m_IMCurrentView->setDragEnabled(flag);
    m_IMCurrentView->setAcceptDrops(flag);
    m_IMCurrentView->setDropIndicatorShown(flag);
    IMModel::instance()->setEdit(!flag);
}

void IMSettingWindow::slot_defualtIMChanged()
{
    FcitxQtInputMethodItem item = IMModel::instance()->getIM(m_defualtIMCbox->comboBox()->currentIndex());
    if (!item.uniqueName().isEmpty()) {
        IMConfig::setDefualtIM(item.uniqueName());
        return;
    }
    if (Global::instance()->inputMethodProxy())
        Global::instance()->inputMethodProxy()->ReloadConfig();
}

void IMSettingWindow::slot_curIMChanged(FcitxQtInputMethodItemList list)
{
    disconnect(m_defualtIMCbox, &ComboxWidget::onSelectChanged, this, &IMSettingWindow::slot_defualtIMChanged);
    m_defualtIMCbox->comboBox()->clear();
    foreach (auto it, list) {
        m_defualtIMCbox->comboBox()->addItem(it.name());
    }
    int index = IMModel::instance()->getIMIndex(IMConfig::defualtIM());
    if (index < 0) {
        index = 0;
        m_defualtIMCbox->comboBox()->setCurrentIndex(index);
        slot_defualtIMChanged();
    }
    m_defualtIMCbox->comboBox()->setCurrentIndex(index);
    connect(m_defualtIMCbox, &ComboxWidget::onSelectChanged, this, &IMSettingWindow::slot_defualtIMChanged);
}
