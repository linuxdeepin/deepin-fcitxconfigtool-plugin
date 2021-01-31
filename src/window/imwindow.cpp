#include "imwindow.h"
#include <fcitxInterface/config.h>
#include <libintl.h>

using namespace Fcitx;
IMWindow::IMWindow(QWidget *parent) : QWidget(parent)
{
    initFcitxInterface();
    initUI();
    initConnect();
}

IMWindow::~IMWindow()
{

}

void IMWindow::initFcitxInterface()
{
    bindtextdomain("fcitx",LOCALEDIR);
    bind_textdomain_codeset("fcitx","UTF-8");
    FcitxLogSetLevel(FCITX_NONE);
    FcitxQtInputMethodItem::registerMetaType();
    FcitxQtKeyboardLayout::registerMetaType();
}

void IMWindow::initUI()
{
    m_stackedWidget = new QStackedWidget(this);
    m_settingWindow = new IMSettingWindow(this);
    m_addWindow = new IMAddWindow(this);
    m_stackedWidget->addWidget(m_settingWindow);
    m_stackedWidget->addWidget(m_addWindow);
    m_stackedWidget->setCurrentIndex(0);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(m_stackedWidget);
    pLayout->setContentsMargins(0, 10, 0, 10);
    setLayout(pLayout);
}

void IMWindow::initConnect()
{
    connect(m_settingWindow,&IMSettingWindow::sig_popIMListWindow,[=](){
         m_stackedWidget->setCurrentIndex(1);
    });

    connect(m_addWindow,&IMAddWindow::sig_cancel,[=](){
         m_stackedWidget->setCurrentIndex(0);
    });

    connect(m_addWindow,&IMAddWindow::sig_addIM,[=](){
         m_stackedWidget->setCurrentIndex(0);
    });
}



