#include "availwidget.h"
#include <QScrollArea>
#include <QVBoxLayout>

static QString languageName(const QString& langCode)
{
    if (langCode.isEmpty()) {
        return QString("Unknown");
    }
    else if (langCode == "*")
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
            //languageName = i18nd("iso_639", QLocale::languageToString(locale.language()).toUtf8());
            languageName = "iso_639";
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
            return languageName;
            //return i18nc("%1 is language name, %2 is country name", "%1 (%2)", languageName, countryName);
        }
    }
}


AvailWidget::AvailWidget(QWidget* parent)
    :QWidget(parent)
{
    QVBoxLayout*vlayout = new QVBoxLayout(this);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget * scrollAreaWidgetContents = new QWidget(scrollArea);
    QGridLayout * gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    QVBoxLayout* scrollAreaLayout = new QVBoxLayout();
    scrollAreaLayout->setSpacing(6);
    gridLayout_2->addLayout(scrollAreaLayout, 0, 0, 1, 1);
    scrollArea->setWidget(scrollAreaWidgetContents);
    vlayout->addWidget(scrollArea);
    m_group = new SettingsGroup();
    scrollAreaLayout->addWidget(m_group);
    scrollAreaLayout->addStretch();

    this->setLayout(vlayout);
}

AvailWidget::~AvailWidget()
{

}

void AvailWidget::updateUI(const FcitxQtInputMethodItemList &IMlist)
{
    m_imlist = IMlist;
    QMap<QString, int> languageMap;
    m_filteredIMEntryList.clear();
    Q_FOREACH(const FcitxQtInputMethodItem & im, IMlist) {
        if (!im.enabled()) {
            int idx;
            if (!languageMap.contains(im.langCode())) {
                idx = m_filteredIMEntryList.count();
                languageMap[im.langCode()] = idx;
                m_filteredIMEntryList.append(QPair<QString, FcitxQtInputMethodItemList>(im.langCode(), FcitxQtInputMethodItemList()));
            } else {
                idx = languageMap[im.langCode()];
            }
            m_filteredIMEntryList[idx].second.append(im);
        }
    }



    m_group->clear();

    QMap<QString,FcitxQtInputMethodItemList>t2;
    for(auto it = m_filteredIMEntryList.begin();it!=m_filteredIMEntryList.end();++it) {
         for(auto it2 = it->second.begin();it2 != it->second.end();++it2) {
             QString imcodeName = languageName(it2->langCode());
             if( t2.find(imcodeName)==t2.end()) {
                 t2.insert(imcodeName,FcitxQtInputMethodItemList());
             }
             t2[imcodeName].push_back(*it2);
         }
    }
    bool flag = m_search.isEmpty();
    for(auto it = t2.begin();it!=t2.end();++it) {
        SettingsHead *head = new SettingsHead();
        head->setEditEnable(false);
        head->setTitle(it.key());
        QHBoxLayout *headLayout = new QHBoxLayout();
        headLayout->addWidget(head);
        headLayout->setContentsMargins(15,0,0,0);
        m_group->getLayout()->setMargin(0);
        m_group->appendItem(head, SettingsGroup::NoneBackground);
        if(flag) {
            head->hide();
        }else {
            head->show();
        }
        for(auto it2 = it->begin();it2!=it->end();++it2) {
            IMSettingsItem*item = new IMSettingsItem();
            item->setParent(m_group);
            item->setFcitxItem(*it2);
            m_group->appendItem(item);
            if(it2->name().indexOf(m_search)!=-1 || it2->uniqueName().indexOf(m_search) !=-1 || it2->langCode().indexOf(m_search) !=-1) {
                item->show();
            }else {
                item->hide();
            }
        }
    }
}

void AvailWidget::slot_searchIM(const QString &str)
{
    m_search = str;

    for (int i=0;i<m_group->itemCount();++i) {
        IMSettingsItem*item  = dynamic_cast<IMSettingsItem*>(m_group->getItem(i));
        if(item) {
            auto it = item->m_item;
            if(!(it.name().indexOf(m_search)!=-1 || it.uniqueName().indexOf(m_search) !=-1 || it.langCode().indexOf(m_search) !=-1)) {
                item->hide();
            }else {
                item->show();
            }
        }
    }
}



