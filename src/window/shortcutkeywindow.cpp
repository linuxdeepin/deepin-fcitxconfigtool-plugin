#include "shortcutkeywindow.h"
#include "widgets/settingsgroup.h"
#include "widgets/keysettingsitem.h"
#include "publisher/publisherdef.h"
#include <QVBoxLayout>

using namespace dcc_fcitx_configtool::widgets;

ShortcutKeyWindow::ShortcutKeyWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnect();
}

ShortcutKeyWindow::~ShortcutKeyWindow()
{

}

void ShortcutKeyWindow::initUI()
{
    //界面布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 10);
    mainLayout->addSpacing(10);
    //冲突快捷键
    m_shortcutGroup = new Fcitx_SettingsGroup();
    m_keySettingsItem = new Fcitx_KeySettingsItem();
    m_shortcutGroup->appendItem(m_keySettingsItem);
    //取消按鈕
    m_buttonTuple = new Fcitx_ButtonTuple();
    cancel = m_buttonTuple->rightButton();
    m_buttonTuple->leftButton()->setVisible(false);
    cancel->setText(tr("Cancel"));
    //BottomTip提示
    m_bottomTip = new QLabel(this);
    //垂直伸缩条
    m_verticalSpacer = new QSpacerItem(20, 240, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //添加至主界面内
    mainLayout->addWidget(m_shortcutGroup);
    mainLayout->addWidget(m_buttonTuple);
    mainLayout->addWidget(m_bottomTip);
    mainLayout->addSpacerItem(m_verticalSpacer);
}

void ShortcutKeyWindow::initConnect()
{
    connect(cancel, SIGNAL(clicked()), this, SIGNAL(popSettingsWindow()));
}

void ShortcutKeyWindow::setBottomTip()
{
    QString str = tr("This shortcut conflicts with %1, click on Add to make this shortcut effective immediately")
                      .arg(QString("<span style=\"color: rgba(255, 90, 90, 1);\">%1 %2</span>").arg(m_conflictName).arg(QString("[%1]").arg(m_shortCut)));
    m_bottomTip->setText(str);
}

void ShortcutKeyWindow::setKeySettings()
{
    m_keySettingsItem->setEnableEdit(true);
    m_keySettingsItem->setList(m_shortCut.split("+"));
    m_keySettingsItem->setEnableEdit(false);
}

void ShortcutKeyWindow::setLabelText()
{
    m_keySettingsItem->setText(m_curName);
}
void ShortcutKeyWindow::setValue(QString curName, QString conflictName, QString shortCut)
{
    m_curName = curName;
    m_conflictName = conflictName;
    m_shortCut = shortCut;
    setLabelText();
    setKeySettings();
    setBottomTip();
}
