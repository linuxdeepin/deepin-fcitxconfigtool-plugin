#include "availwidget.h"
#include "widgets/titlelabel.h"
#include "publisherdef.h"
#include "immodel/immodel.h"
<<<<<<< HEAD
=======
#include "fcitxInterface/global.h"
#include "../i18n.h"
>>>>>>> cdc386b... feat: 添加输入法界面完成
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QList>
<<<<<<< HEAD
#include <fcitxInterface/global.h>
=======
>>>>>>> cdc386b... feat: 添加输入法界面完成

using namespace Fcitx;
using namespace Dtk::Widget;
bool operator==(const FcitxQtInputMethodItem &item, const FcitxQtInputMethodItem &item2);
// kcm代码 获取语言名称 简体中文 繁体中文 英文等 需要优化
static QString languageName(const QString &langCode)
{
<<<<<<< HEAD
=======
    //QLocale locale("es_PE");
    // fcitx::translateDomain("iso_638", QLocale::languageToString(locale.language()).toUtf8());

>>>>>>> cdc386b... feat: 添加输入法界面完成
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
<<<<<<< HEAD
            //languageName = i18nd("iso_639", QLocale::languageToString(locale.language()).toUtf8());
            languageName = "iso_639";
=======
            languageName = fcitx::translateDomain("iso_639", QLocale::languageToString(locale.language()).toUtf8());
>>>>>>> cdc386b... feat: 添加输入法界面完成
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
<<<<<<< HEAD
            return languageName;
            //return i18nc("%1 is language name, %2 is country name", "%1 (%2)", languageName, countryName);
=======
            return languageName + " (" + countryName + ")";
>>>>>>> cdc386b... feat: 添加输入法界面完成
        }
    }
}

AvailWidget::AvailWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnect();
    slot_updateUI(IMModel::instance()->availIMList());
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
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollAreaWidgetContents = new QWidget(scrollArea);
    QGridLayout *gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout();
    scrollAreaLayout->setSpacing(6);
    gridLayout_2->addLayout(scrollAreaLayout, 0, 0, 1, 1);
    scrollArea->setWidget(scrollAreaWidgetContents);
    vlayout->addWidget(scrollArea);

    m_allIMGroup = new SettingsGroup();
    m_allIMGroup->getLayout()->setMargin(0);
    scrollAreaLayout->addWidget(m_allIMGroup);
    m_searchIMGroup = new SettingsGroup();
    m_searchIMGroup->getLayout()->setMargin(0);
    scrollAreaLayout->addWidget(m_searchIMGroup);
    scrollAreaLayout->addStretch();

    this->setLayout(vlayout);
}

void AvailWidget::initConnect()
{
    connect(IMModel::instance(), &IMModel::sig_availIMList, this, &AvailWidget::slot_updateUI);
}

<<<<<<< HEAD
void AvailWidget::clearItemStatus()
{
    m_selectItem = FcitxQtInputMethodItem();
    cleareItemStatusAndFilter(m_allIMGroup, true);
    //cleareFcitxItemAndFilter(m_searchIMGroup);  //不需要清除搜索m_searchIMGroup 搜索框信号会触发清除
}

void AvailWidget::cleareItemStatusAndFilter(SettingsGroup *group, bool flag)
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

void AvailWidget::slot_updateUI(FcitxQtInputMethodItemList IMlist)
{
    if (!Global::instance()->inputMethodProxy()) {
        m_allIMGroup->hide();
        m_searchIMGroup->hide();
        emit sig_seleteIM(false);
        return;
    }

=======
void AvailWidget::slot_updateUI(FcitxQtInputMethodItemList IMlist)
{
>>>>>>> cdc386b... feat: 添加输入法界面完成
    if (m_searchStr.isEmpty()) {
        m_allIMGroup->show();
        m_searchIMGroup->hide();
    } else {
        m_searchIMGroup->show();
        m_allIMGroup->hide();
    }

    if (m_allAvaiIMlList == IMlist) {
<<<<<<< HEAD
=======
        emit sig_seleteIM(!(m_selectItem.name().isEmpty()));
>>>>>>> cdc386b... feat: 添加输入法界面完成
        return;
    }
    m_allAvaiIMlList = IMlist;

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
        connect(item, &IMSettingsItem::sig_itemClicked, [=](IMSettingsItem *item) {
            m_selectItem = item->m_item;
            emit sig_seleteIM(true);
        });
        item->setParent(m_allIMGroup);
        item->setFcitxItem(imItem);
        group->appendItem(item);
        if (group == m_searchIMGroup) {
            item->setFilterStr(m_searchStr);
        }
        if (imItem.name() == m_selectItem.name()
            && imItem.langCode() == m_selectItem.langCode()
            && imItem.uniqueName() == m_selectItem.uniqueName()) {
            item->setItemSelected(true);
            emit sig_seleteIM(true);
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

<<<<<<< HEAD
=======
void AvailWidget::clearItemStatus()
{
    m_selectItem = FcitxQtInputMethodItem();
    cleareItemStatusAndFilter(m_allIMGroup, true);
    //cleareFcitxItemAndFilter(m_searchIMGroup);  //不需要清除搜索m_searchIMGroup 搜索框信号会触发清除
}

void AvailWidget::cleareItemStatusAndFilter(SettingsGroup *group, bool flag)
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

>>>>>>> cdc386b... feat: 添加输入法界面完成
void AvailWidget::slot_searchIM(const QString &str)
{
    m_searchStr = str;
    m_allIMGroup->hide();
    m_searchIMGroup->hide();
    m_selectItem = FcitxQtInputMethodItem();
    emit sig_seleteIM(false);

<<<<<<< HEAD
    if (Global::instance()->inputMethodProxy()) {
        if (m_searchStr.isEmpty()) {
            m_allIMGroup->show();
            cleareItemStatusAndFilter(m_allIMGroup, false);
        } else {
            m_searchIMGroup->show();
            cleareItemStatusAndFilter(m_searchIMGroup, true);
        }
=======
    if (m_searchStr.isEmpty()) {
        m_allIMGroup->show();
        m_searchIMGroup->hide();
        cleareItemStatusAndFilter(m_allIMGroup, false);
    } else {
        m_searchIMGroup->show();
        m_allIMGroup->hide();
        cleareItemStatusAndFilter(m_searchIMGroup, true);
>>>>>>> cdc386b... feat: 添加输入法界面完成
    }
}
