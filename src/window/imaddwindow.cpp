#include "imaddwindow.h"
#include "availwidget.h"
#include "immodel/immodel.h"
#include "widgets/titlelabel.h"
#include <QGroupBox>
#include <QProcess>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QApplication>
<<<<<<< HEAD
=======
#include <DStyle>
>>>>>>> cdc386b... feat: 添加输入法界面完成
#include <fcitxInterface/global.h>

using namespace Fcitx;

IMAddWindow::IMAddWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnect();
}

IMAddWindow::~IMAddWindow()
{
}

void IMAddWindow::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QHBoxLayout *hlayout = new QHBoxLayout();
<<<<<<< HEAD
    TitleLabel *title = new TitleLabel(tr("添加输入法"), this);
=======
    TitleLabel *title = new TitleLabel(tr("Add Input Method"), this);
>>>>>>> cdc386b... feat: 添加输入法界面完成
    DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
    hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlayout->addWidget(title);
    hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(hlayout);

<<<<<<< HEAD
    m_searchLEdit = new SearchInput(this);
    m_searchLEdit->setIcon("");
    m_searchLEdit->setSearchText(tr("搜索"));
=======
    m_searchLEdit = new DSearchEdit(this);
    m_searchLEdit->setText(tr("Search"));
>>>>>>> cdc386b... feat: 添加输入法界面完成
    mainLayout->addWidget(m_searchLEdit);
    mainLayout->addSpacing(20);
    m_availWidget = new AvailWidget(this);
    mainLayout->addWidget(m_availWidget);

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addStretch();
<<<<<<< HEAD
    m_storeBtn = new DCommandLinkButton(tr("前往商店下载"), this);
=======
    m_storeBtn = new DCommandLinkButton(tr("Find more in App Store"), this);
>>>>>>> cdc386b... feat: 添加输入法界面完成
    hlayout2->addWidget(m_storeBtn);
    mainLayout->addLayout(hlayout2);

    m_buttonTuple = new ButtonTuple(ButtonTuple::Save);
    auto ok = m_buttonTuple->rightButton();
<<<<<<< HEAD
    ok->setText(tr("添加"));
    ok->setEnabled(false);
    auto cancel = m_buttonTuple->leftButton();
    cancel->setText(tr("取消"));
=======
    ok->setText(tr("Add"));
    ok->setEnabled(false);
    auto cancel = m_buttonTuple->leftButton();
    cancel->setText(tr("Cancel"));
>>>>>>> cdc386b... feat: 添加输入法界面完成

    mainLayout->addWidget(m_buttonTuple, 0, Qt::AlignBottom);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

void IMAddWindow::initConnect()
{
    connect(m_storeBtn, &DCommandLinkButton::clicked, this, &IMAddWindow::slot_openStore);
    connect(m_buttonTuple->rightButton(), &QPushButton::clicked, this, &IMAddWindow::slot_addIM);
    connect(m_buttonTuple->leftButton(), &QPushButton::clicked, this, &IMAddWindow::sig_popSettingsWindow);
    connect(m_availWidget, &AvailWidget::sig_seleteIM, m_buttonTuple->rightButton(), &QPushButton::setEnabled);
<<<<<<< HEAD
    connect(m_searchLEdit, &SearchInput::textChanged, m_availWidget, &AvailWidget::slot_searchIM);
=======
    connect(m_searchLEdit, &DSearchEdit::textChanged, m_availWidget, &AvailWidget::slot_searchIM);
>>>>>>> cdc386b... feat: 添加输入法界面完成
}

void IMAddWindow::updateUI()
{
    m_buttonTuple->rightButton()->setEnabled(false);
    m_buttonTuple->leftButton()->setDefault(true);
    if (!m_searchLEdit->text().isEmpty())
        m_searchLEdit->clear();
    m_availWidget->clearItemStatus();
}

void IMAddWindow::slot_addIM()
{
    IMModel::instance()->addIMItem(m_availWidget->getSeleteIm());
    emit sig_popSettingsWindow();
}

void IMAddWindow::slot_openStore()
{
    QProcess::startDetached("deepin-app-store");
}
