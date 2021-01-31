#include "imsettingwindow.h"
#include "widgets/utils.h"
#include <QComboBox>
#include <QGroupBox>
#include <QScrollArea>
#include <fcitxInterface/global.h>
#include <libintl.h>

using namespace Fcitx;

#define for_int(count) for(int i =0;i<count;++i)


IMSettingWindow::IMSettingWindow(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnect();
    updateUI();
}

IMSettingWindow::~IMSettingWindow()
{
    writeConfig();
}

void IMSettingWindow::updateUI()
{
    readConfig();
    if (Global::instance()->inputMethodProxy()) {
        emit sig_updateIMList(Global::instance()->inputMethodProxy()->iMList());
    }
}

void IMSettingWindow::initUI()
{
    auto createTitle=[this](QString str){
        TitleLabel*title = new TitleLabel(str,this);
        DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
        return title;
    };

    auto createGroup=[this](QWidget*widget){
        QGroupBox *groupBox =new QGroupBox(this);
        QVBoxLayout *layout =new QVBoxLayout(this);
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(widget);
        groupBox->setLayout(layout);
        return groupBox;
    };

    auto createKeyEditWidget=[=](DKeySequenceEdit* &keyEdit,QString str){
        QWidget *widget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(widget);
        keyEdit = new DKeySequenceEdit(this);
        QLabel *label = new QLabel(str,this);
        layout->addWidget(label);
        layout->addStretch();
        layout->addWidget(keyEdit);
        widget->setLayout(layout);
        keyEdit->setKeySequence(QKeySequence::FindNext);
        keyEdit->setFixedSize(200,30);
        keyEdit->setFrame(false);
        return createGroup(widget);
    };

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createTitle(tr("输入法")));

    m_defualtIMCbox = new ComboxWidget("默认");
    mainLayout->addWidget(createGroup(m_defualtIMCbox));
    m_switchSystem =new SwitchWidget("使用系统托盘",this);
    mainLayout->addWidget(createGroup(m_switchSystem));
    mainLayout->addSpacing(20);


    QHBoxLayout *headLayout = new QHBoxLayout(this);
    headLayout->setContentsMargins(0,0,0,0);
    headLayout->addWidget(createTitle(tr("输入法管理")));
    m_editBtn = new DCommandLinkButton(tr("编辑"));
    headLayout->addStretch();
    headLayout->addWidget(m_editBtn);
    mainLayout->addLayout(headLayout);
    m_IMCurrentView = new DListView(this);
    m_IMCurrentView->setDragEnabled(true);
    m_IMCurrentView->setAcceptDrops(true);
    m_IMCurrentView->setDropIndicatorShown(true);
    m_IMCurrentView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_IMCurrentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_IMCurrentView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_IMCurrentView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_IMCurrentView->setItemSpacing(2);
    m_IMCurrentView->setItemSize(QSize(100,48));
    mainLayout->addWidget(m_IMCurrentView);
    mainLayout->addSpacing(20);

    mainLayout->addWidget(createTitle(tr("快捷键")));
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget * scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 382, 209));
    QGridLayout * gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(6);
    gridLayout_2->addLayout(vLayout, 0, 0, 1, 1);
    scrollArea->setWidget(scrollAreaWidgetContents);
    mainLayout->addWidget(scrollArea);

    m_imSwitchCbox =new ComboxWidget(tr("切换输入法"));
    m_imSwitchCbox->comboBox()->addItems({"Ctrl+Shift","Alt+Shift","Ctrl+Super","Alt+Super"});
    vLayout->addWidget(createGroup(m_imSwitchCbox));
    vLayout->addWidget(createKeyEditWidget(m_defualtIMKey,tr("切换至默认输入法")));
    vLayout->addWidget(createKeyEditWidget(m_virtualKey,tr("切换虚拟键盘")));

    m_systemAppCbox = new ComboxWidget(tr("切换方式"));
    m_systemAppCbox->comboBox()->addItems({"系统","应用"});
    mainLayout->addWidget(m_systemAppCbox);

    QHBoxLayout *headLayout2 = new QHBoxLayout(this);
    headLayout2->setContentsMargins(0,0,0,0);
    headLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_addIMBtn =new DFloatingButton(DStyle::SP_IncreaseElement,this);
    headLayout2->addWidget(m_addIMBtn);
    headLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(headLayout2);
    this->setLayout(mainLayout);

    m_curIMModel = new IMModel(this);
    m_IMCurrentView->setModel(m_curIMModel);
    m_defualtIMCbox->comboBox()->setModel(m_curIMModel);
}

void IMSettingWindow::initConnect()
{
    connect(m_addIMBtn,&DFloatingButton::clicked,[=](){emit sig_popIMListWindow();});
    connect(m_defualtIMCbox,&ComboxWidget::onSelectChanged,this,&IMSettingWindow::slot_defualtIMChanged);
    connect(m_switchSystem,&SwitchWidget::checkedChanged,this,&IMSettingWindow::slot_switchSystem);
    connect(m_editBtn,&DCommandLinkButton::clicked,this,&IMSettingWindow::slot_editBtnClicked);
    connect(m_systemAppCbox,&ComboxWidget::onSelectChanged,this,&IMSettingWindow::slot_defualtIMChanged);
    connect(this,&IMSettingWindow::sig_updateIMList,m_curIMModel,&IMModel::slot_filterIMEntryList);
    connect(Global::instance(),&Global::connectStatusChanged,[=](){
        if (Global::instance()->inputMethodProxy()) {
            emit sig_updateIMList(Global::instance()->inputMethodProxy()->iMList());
        }
    });
}

void IMSettingWindow::readConfig()
{

}

void IMSettingWindow::writeConfig()
{

}

void IMSettingWindow::slot_defualtIMChanged(const QString &selected)
{

}

void IMSettingWindow::slot_switchSystem(const bool &checked)
{

}

void IMSettingWindow::slot_editBtnClicked()
{
    bool flag = m_curIMModel->isEdit();
    if(!flag){
        m_editBtn->setText(tr("完成"));
        m_IMCurrentView->setSelectionMode(QAbstractItemView::NoSelection);
    }else {
        m_editBtn->setText(tr("编辑"));
        m_IMCurrentView->setSelectionMode(QAbstractItemView::SingleSelection);
    }

    m_IMCurrentView->setDragEnabled(flag);
    m_IMCurrentView->setAcceptDrops(flag);
    m_IMCurrentView->setDropIndicatorShown(flag);
    m_curIMModel->setEdit(!flag);
}

void IMSettingWindow::slot_systemAppChanged(const QString &selected)
{

}


