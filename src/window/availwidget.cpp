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
#include "availwidget.h"
#include "immodel/immodel.h"
#include "widgets/settingshead.h"
#include "widgets/settingsgroup.h"
#include "widgets/imsettingsitem.h"
#include "publisher/publisherdef.h"
#include "fcitxInterface/global.h"
#include "fcitxInterface/i18n.h"
#include "widgets/contentwidget.h"
#include <QVBoxLayout>

using namespace Fcitx;

bool operator==(const FcitxQtInputMethodItem &item, const FcitxQtInputMethodItem &item2);
// kcm代码 获取语言名称 简体中文 繁体中文 英文等 需要优化
static QString languageName(const QString &langCode)
{
    if (langCode.isEmpty()) {
        return QString("Unknown");
    } else if (langCode == "*")
        return QString("Multilingual");
    else {
        QLocale locale(langCode);
        if (locale.language() == QLocale::C) {
            return langCode;
        }
        const bool hasCountry = langCode.indexOf("_") != -1 && locale.country() != QLocale::AnyCountry;
        QString languageName;
        if (hasCountry) {
            languageName = locale.nativeLanguageName();
        }
        if (languageName.isEmpty()) {
            languageName = fcitx::translateDomain("iso_639", QLocale::languageToString(locale.language()).toUtf8());
        }
        if (languageName.isEmpty()) {
            languageName = QString("Other");
        }
        QString countryName;
        // QLocale will always assign a default country for us, check if our lang code

        if (langCode.indexOf("_") != -1 && locale.country() != QLocale::AnyCountry) {
            countryName = locale.nativeCountryName();
            if (countryName.isEmpty()) {
                countryName = QLocale::countryToString(locale.country());
            }
        }

        if (countryName.isEmpty()) {
            return languageName;
        } else {
            return languageName + " (" + countryName + ")";
        }
    }
}

AvailWidget::AvailWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnect();
    onUpdateUI(IMModel::instance()->getAvailIMList());
}

AvailWidget::~AvailWidget()
{
    m_allIMGroup->clear();
    m_searchIMGroup->clear();
    deleteObject_Null(m_allIMGroup);
    deleteObject_Null(m_searchIMGroup);
}

void AvailWidget::initUI()
{
    //界面布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    //滑动窗口
    ContentWidget *scrollArea = new ContentWidget(this);
    QWidget *scrollAreaWidgetContents = new QWidget(scrollArea);
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(scrollAreaWidgetContents);
    scrollAreaLayout->setSpacing(0);
    scrollArea->setContent(scrollAreaWidgetContents);
    scrollAreaWidgetContents->setLayout(scrollAreaLayout);
    //搜索输入法列表 可用输入法列表
    m_allIMGroup = new SettingsGroup;
    m_searchIMGroup = new SettingsGroup;
    //控件添加至滑动窗口内
    scrollAreaLayout->addWidget(m_allIMGroup);
    scrollAreaLayout->addSpacing(10);
    scrollAreaLayout->addWidget(m_searchIMGroup);
    scrollAreaLayout->addStretch();
    //添加至主界面内
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

void AvailWidget::initConnect()
{
    connect(IMModel::instance(), &IMModel::availIMListChanged, this, &AvailWidget::onUpdateUI);
}

void AvailWidget::onUpdateUI(FcitxQtInputMethodItemList IMlist)
{
    if (!Global::instance()->inputMethodProxy()) {
        m_allIMGroup->clear(); //清空group
        m_searchIMGroup->clear();
        m_allAvaiIMlList.clear();
        emit seleteIM(false);
        return;
    }

    if (m_searchStr.isEmpty()) {
        m_allIMGroup->show();
        m_searchIMGroup->hide();
    } else {
        m_allIMGroup->hide();
        m_searchIMGroup->show();
    }

    if (m_allAvaiIMlList == IMlist) {
        emit seleteIM((m_allAvaiIMlList.indexOf(m_selectItem) != 0));
        return;
    }
    m_allAvaiIMlList.swap(IMlist);

    QMap<QString, int> languageMap;
    QList<QPair<QString, FcitxQtInputMethodItemList>> filteredIMEntryList;
    Q_FOREACH (const FcitxQtInputMethodItem &im, m_allAvaiIMlList) {
        if (!im.enabled()) {
            int idx;
            if (!languageMap.contains(im.langCode())) {
                idx = filteredIMEntryList.count();
                languageMap[im.langCode()] = idx;
                filteredIMEntryList.append(QPair<QString, FcitxQtInputMethodItemList>(im.langCode(), FcitxQtInputMethodItemList()));
            } else {
                idx = languageMap[im.langCode()];
            }
            filteredIMEntryList[idx].second.append(im);
        }
    }

    std::map<QString, FcitxQtInputMethodItemList> tmpIM;
    for (auto it = filteredIMEntryList.begin(); it != filteredIMEntryList.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            QString imcodeName = languageName(it2->langCode());
            if (tmpIM.find(imcodeName) == tmpIM.end()) {
                tmpIM.insert(std::pair<QString, FcitxQtInputMethodItemList>(imcodeName, FcitxQtInputMethodItemList()));
            }
            tmpIM[imcodeName].push_back(*it2);
        }
    }

    auto createIMSttings = [=](SettingsGroup *group, FcitxQtInputMethodItem imItem) {
        IMSettingsItem *item = new IMSettingsItem();
        connect(item, &IMSettingsItem::itemClicked, [=](IMSettingsItem *item) {
            m_selectItem = item->m_item;
            emit seleteIM(true);
        });
        item->setParent(group);
        item->setFcitxItem(imItem);
        group->appendItem(item);
        if (group == m_searchIMGroup) {
            item->setFilterStr(m_searchStr);
        }
        if (imItem.name() == m_selectItem.name()
            && imItem.langCode() == m_selectItem.langCode()
            && imItem.uniqueName() == m_selectItem.uniqueName()) {
            item->setItemSelected(true);
            emit seleteIM(true);
        }
    };

    //清空group
    m_allIMGroup->clear();
    m_searchIMGroup->clear();
    //添加item
    for (auto it = tmpIM.rbegin(); it != tmpIM.rend(); ++it) {
        SettingsHead *head = new SettingsHead();
        head->setEditEnable(false);
        head->setTitle(it->first);
        m_allIMGroup->appendItem(head, SettingsGroup::NoneBackground);
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            createIMSttings(m_allIMGroup, *it2);
            createIMSttings(m_searchIMGroup, *it2);
        }
    }
}

void AvailWidget::clearItemStatus()
{
    m_selectItem = FcitxQtInputMethodItem();
    clearItemStatusAndFilter(m_allIMGroup, true);
    //cleareFcitxItemAndFilter(m_searchIMGroup);  //不需要清除搜索m_searchIMGroup 搜索框信号会触发清除
}

void AvailWidget::clearItemStatusAndFilter(SettingsGroup *group, bool flag)
{
    if (!group) {
        return;
    }

    for (int i = 0; i < group->itemCount(); ++i) {
        IMSettingsItem *item = dynamic_cast<IMSettingsItem *>(group->getItem(i));
        if (item) {
            item->setItemSelected(false);
            if (flag)
                item->setFilterStr(m_searchStr);
        }
    }
}

void AvailWidget::onSearchIM(const QString &str)
{
    m_searchStr = str;
    m_selectItem = FcitxQtInputMethodItem();
    emit seleteIM(false);

    if (m_searchStr.isEmpty()) {
        m_allIMGroup->show();
        m_searchIMGroup->hide();
        clearItemStatusAndFilter(m_allIMGroup, false);
    } else {
        m_searchIMGroup->show();
        m_allIMGroup->hide();
        clearItemStatusAndFilter(m_searchIMGroup, true);
    }
}
