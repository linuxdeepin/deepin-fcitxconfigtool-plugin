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
#include "widgets/titlelabel.h"

#include <QComboBox>
#include <QGroupBox>
#include <QScrollArea>
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
}

void IMSettingWindow::updateUI()
{
    if (IMModel::instance()->isEdit()) {
        onEditBtnClicked();
    }
    readConfig();
}

void IMSettingWindow::initUI()
{
    auto createTitleLayout = [this](QString str) {
        QHBoxLayout *headLayout = new QHBoxLayout(this);
        headLayout->setContentsMargins(10, 0, 0, 10);
        TitleLabel *title = new TitleLabel(str, this);
        DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
        headLayout->addWidget(title);
        return headLayout;
    };

    auto createGroup = [this](QWidget *widget) {
        QGroupBox *groupBox = new QGroupBox(this);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setMargin(0);
        layout->addWidget(widget);
        groupBox->setLayout(layout);
        groupBox->setFixedHeight(48);
        return groupBox;
    };

    //界面布局

    //输入法标签
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(createTitleLayout(tr("Input Method")));

    //默认输入法
    m_defualtIMCbox = new ComboxWidget(tr("Default"));
    m_defualtIMCbox->setParent(this);
    foreach (auto it, IMModel::instance()->getCurIMList()) {
        m_defualtIMCbox->comboBox()->addItem(it.name());
    }
    mainLayout->addWidget(createGroup(m_defualtIMCbox));
    mainLayout->addSpacing(20);

    //输入法管理标签 编辑按钮
    QHBoxLayout *headLayout = createTitleLayout(tr("Manage Input Methods"));
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
    //  m_IMCurrentView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_IMCurrentView->setItemSpacing(2);
    m_IMCurrentView->setItemSize(QSize(100, 36));
    m_IMCurrentView->setModel(IMModel::instance());
    mainLayout->addWidget(m_IMCurrentView);
    mainLayout->addSpacing(20);

    //快捷键标签 切换输入法 切换虚拟键盘 切换至默认输入法
    mainLayout->addLayout(createTitleLayout(tr("Shortcuts")));
    m_shortcutGroup = new SettingsGroup;
    m_imSwitchCbox = new ComBoboxSettingsItem(tr("Switch input methods"), {"CTRL_SHIFT", "ALT_SHIFT", "CTRL_SUPER", "ALT_SUPER"});
    m_defualtIMKey = new KeySettingsItem(tr("Switch to default input method"));
    m_virtualKey = new KeySettingsItem(tr("Call out Onboard"));
    m_shortcutGroup->setParent(this);
    m_imSwitchCbox->setParent(this);
    m_defualtIMKey->setParent(this);
    m_virtualKey->setParent(this);
    m_shortcutGroup->appendItem(m_imSwitchCbox);
    m_shortcutGroup->appendItem(m_defualtIMKey);
    m_shortcutGroup->appendItem(m_virtualKey);
    mainLayout->addWidget(m_shortcutGroup);

    //切换方式
    m_systemAppCbox = new ComboxWidget(tr("Applies to"));
    m_systemAppCbox->setParent(this);
    m_systemAppCbox->layout()->setContentsMargins(10, 0, 0, 0);
    m_systemAppCbox->comboBox()->addItems({tr("System"), tr("Application")});
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_systemAppCbox);
    mainLayout->addStretch();

    //添加界面按钮
    QHBoxLayout *headLayout2 = new QHBoxLayout(this);
    headLayout2->setMargin(0);
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
    connect(m_addIMBtn, &DFloatingButton::clicked, this, &IMSettingWindow::onAddBtnCilcked);
    connect(m_editBtn, &DCommandLinkButton::clicked, this, &IMSettingWindow::onEditBtnClicked);
    connect(m_defualtIMCbox, &ComboxWidget::onSelectChanged, this, &IMSettingWindow::onDefualtIMChanged);
    connect(IMModel::instance(), &IMModel::curIMListChanaged, this, &IMSettingWindow::onCurIMChanged);

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

void IMSettingWindow::onEditBtnClicked()
{
    bool flag = IMModel::instance()->isEdit();
    if (!flag) {
        m_editBtn->setText(tr("Done"));
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

void IMSettingWindow::onDefualtIMChanged()
{
    FcitxQtInputMethodItem item = IMModel::instance()->getIM(m_defualtIMCbox->comboBox()->currentIndex());
    if (!item.uniqueName().isEmpty()) {
        IMConfig::setDefualtIM(item.uniqueName());
        return;
    }
    if (Global::instance()->inputMethodProxy())
        Global::instance()->inputMethodProxy()->ReloadConfig();
}

void IMSettingWindow::onCurIMChanged(FcitxQtInputMethodItemList list)
{
    disconnect(m_defualtIMCbox, &ComboxWidget::onSelectChanged, this, &IMSettingWindow::onDefualtIMChanged);

    m_defualtIMCbox->comboBox()->clear();
    foreach (auto it, list) {
        m_defualtIMCbox->comboBox()->addItem(it.name());
    }
    int index = IMModel::instance()->getIMIndex(IMConfig::defualtIM());
    if (index < 0) {
        index = 0;
        m_defualtIMCbox->comboBox()->setCurrentIndex(index);
        onDefualtIMChanged();
    } else {
        m_defualtIMCbox->comboBox()->setCurrentIndex(index);
    }
    connect(m_defualtIMCbox, &ComboxWidget::onSelectChanged, this, &IMSettingWindow::onDefualtIMChanged);
}

void IMSettingWindow::onAddBtnCilcked()
{
    if (IMModel::instance()->isEdit())
        onEditBtnClicked();
    emit popIMAddWindow();
}
