#include "imaddwindow.h"
#include "availwidget.h"
#include "immodel/immodel.h"
#include "widgets/titlelabel.h"
#include <QGroupBox>
#include <QProcess>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QApplication>
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

    TitleLabel *title = new TitleLabel(tr("Add Input Method"), this);

    DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
    hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlayout->addWidget(title);
    hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(hlayout);

    m_searchLEdit = new DSearchEdit(this);
    m_searchLEdit->setText(tr("Search"));
    mainLayout->addWidget(m_searchLEdit);
    mainLayout->addSpacing(20);
    m_availWidget = new AvailWidget(this);
    mainLayout->addWidget(m_availWidget);

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addStretch();
    m_storeBtn = new DCommandLinkButton(tr("Find more in App Store"), this);

    hlayout2->addWidget(m_storeBtn);
    mainLayout->addLayout(hlayout2);

    m_buttonTuple = new ButtonTuple(ButtonTuple::Save);
    m_buttonTuple->rightButton()->setText(tr("Add"));
    m_buttonTuple->rightButton()->setEnabled(false);
    m_buttonTuple->leftButton()->setText(tr("Cancel"));

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
    connect(m_searchLEdit, &DSearchEdit::textChanged, m_availWidget, &AvailWidget::slot_searchIM);
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
