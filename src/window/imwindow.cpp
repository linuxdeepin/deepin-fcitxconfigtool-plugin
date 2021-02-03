#include "imwindow.h"
#include "imaddwindow.h"
#include "imsettingwindow.h"
#include "immodel/immodel.h"
#include "fcitxInterface/config.h"
#include "fcitxInterface/global.h"
#include <QStackedWidget>
#include <QGridLayout>
#include <libintl.h>

using namespace Fcitx;
IMWindow::IMWindow(QWidget *parent)
    : QWidget(parent)
{
    initFcitxInterface();
    initUI();
    initConnect();
}

IMWindow::~IMWindow()
{
    IMModel::instance()->deleteIMModel();
}

void IMWindow::initFcitxInterface()
{
    bindtextdomain("fcitx", LOCALEDIR);
    bind_textdomain_codeset("fcitx", "UTF-8");
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
    //界面布局
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(m_stackedWidget);
    pLayout->setContentsMargins(0, 10, 0, 10);
    setLayout(pLayout);
}

void IMWindow::initConnect()
{
    connect(m_settingWindow, &IMSettingWindow::sig_popIMAddWindow, [=]() {
        m_stackedWidget->setCurrentIndex(1);
        m_addWindow->updateUI();
    });

    connect(m_addWindow, &IMAddWindow::sig_popSettingsWindow, [=]() {
        m_stackedWidget->setCurrentIndex(0);
        m_settingWindow->updateUI();
    });
}
