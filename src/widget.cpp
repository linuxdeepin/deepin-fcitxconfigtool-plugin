#include "widget.h"

#include "titlelabel.h"
#include "comboxwidget.h"
#include "settingsitem.h"
#include "utils.h"

#include <DFontSizeManager>
#include <DSwitchButton>
#include <DKeySequenceEdit>
#include <DFloatingButton>

#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE


Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* vboxLayout = new QVBoxLayout();
    QHBoxLayout *hboxLayout = new QHBoxLayout();

    TitleLabel *headTitle = new TitleLabel(tr("输入法"));
    DFontSizeManager::instance()->bind(headTitle, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体

    vboxLayout->addWidget(headTitle);

    dcc::widgets::ComboxWidget* m_cmbMiniEffect = new  dcc::widgets::ComboxWidget();
    m_cmbMiniEffect->setTitle(tr("默认"));
    m_cmbMiniEffect->addBackground();
    QStringList options;
    options << tr("讯飞输入法") << tr("华宇输入法");
    m_cmbMiniEffect->setComboxOption(options);
    vboxLayout->addWidget(m_cmbMiniEffect);

    DTK_WIDGET_NAMESPACE::DSwitchButton *m_wmSwitch = new DTK_WIDGET_NAMESPACE::DSwitchButton();
    m_wmSwitch->setAccessibleName("switchbutton");

    QHBoxLayout *swswitchLayout = new QHBoxLayout();
    swswitchLayout->addWidget(new QLabel(tr("使用系统托盘")));
    swswitchLayout->addStretch();
    swswitchLayout->addWidget(m_wmSwitch);
    swswitchLayout->setContentsMargins(10, 0, 10, 0);
    vboxLayout->addLayout(swswitchLayout);

    TitleLabel *headTitle1 = new TitleLabel(tr("快捷键"));
    DFontSizeManager::instance()->bind(headTitle1, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体

    vboxLayout->addWidget(headTitle1);

    QHBoxLayout *oneLayout = new QHBoxLayout();
    oneLayout->addWidget(new QLabel(tr("切换默认输入法")));
    oneLayout->addStretch();
    DKeySequenceEdit *keySequenceEdit1 = new DKeySequenceEdit();

    oneLayout->addWidget(keySequenceEdit1);
    oneLayout->setContentsMargins(10, 0, 10, 0);
    vboxLayout->addLayout(oneLayout);

    QHBoxLayout *twoLayout = new QHBoxLayout();
    twoLayout->addWidget(new QLabel(tr("切换输入法")));
    twoLayout->addStretch();
    DKeySequenceEdit *keySequenceEdit2 = new DKeySequenceEdit();

    twoLayout->addWidget(keySequenceEdit2);
    twoLayout->setContentsMargins(10, 0, 10, 0);
    vboxLayout->addLayout(twoLayout);


    QHBoxLayout *threeLayout = new QHBoxLayout();
    threeLayout->addWidget(new QLabel(tr("唤起虚拟键盘")));
    threeLayout->addStretch();
    DKeySequenceEdit *keySequenceEdit3 = new DKeySequenceEdit();

    threeLayout->addWidget(keySequenceEdit3);
    threeLayout->setContentsMargins(10, 0, 10, 0);
    vboxLayout->addLayout(threeLayout);


    DFloatingButton* floatingButton = new DFloatingButton(this);

    vboxLayout->addWidget(floatingButton);


    hboxLayout->addLayout(vboxLayout);





    setLayout(hboxLayout);

}

Widget::~Widget()
{
}
