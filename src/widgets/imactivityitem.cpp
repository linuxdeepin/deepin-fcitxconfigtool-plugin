#include "imactivityitem.h"
#include "publisher/publisherdef.h"
#include "window/immodel/immodel.h"
#include <DToolButton>
#include <DFontSizeManager>
#include <QTimer>
using namespace Dtk::Widget;
namespace dcc_fcitx_configtool {
namespace widgets {

IMActivityItem::IMActivityItem(FcitxQtInputMethodItem item, bool isFirst, QFrame *parent)
    : SettingsItem(parent)
    , m_isFirst(isFirst)
    , m_item(item)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(20, 0, 10, 0);
    m_labelText = new ShortenLabel("", this);

    DFontSizeManager::instance()->bind(m_labelText, DFontSizeManager::T6);
    m_labelText->setShortenText(item.name());
    m_layout->addWidget(m_labelText);
    if (!m_isFirst) {
        m_upBtn = new ToolButton(this);
        m_downBtn = new ToolButton(this);
        m_configBtn = new DToolButton(this);
        m_deleteBtn = new DToolButton(this);
        m_upBtn->setIcon(QIcon(":/icons/arrow_up.svg"));
        m_downBtn->setIcon(QIcon(":/icons/arrow_down.svg"));
        m_configBtn->setIcon(QIcon(":/icons/setting.svg"));
        m_deleteBtn->setIcon(DStyle::standardIcon(QApplication::style(), DStyle::SP_DeleteButton));

        m_layout->addWidget(m_downBtn);
        m_layout->addWidget(m_upBtn);
        m_layout->addWidget(m_configBtn);
        m_layout->addWidget(m_deleteBtn);
        m_deleteBtn->hide();
        m_upBtn->hide();
        m_configBtn->hide();
        m_downBtn->hide();

        connect(m_upBtn, &ToolButton::clicked, this, &IMActivityItem::onUpItem);
        connect(m_downBtn, &ToolButton::clicked, this, &IMActivityItem::onDownItem);
        connect(m_configBtn, &DToolButton::clicked, this, &IMActivityItem::onConfigItem);
        connect(m_deleteBtn, &DToolButton::clicked, this, &IMActivityItem::onDeleteItem);
    }

    this->setFixedHeight(40);
    this->setLayout(m_layout);
}

IMActivityItem::~IMActivityItem()
{
}

void IMActivityItem::editSwitch(bool flag)
{
    if (m_isFirst)
        return;
    m_isEdit = flag;
    if (m_isEdit) {
        m_deleteBtn->show();
        m_configBtn->hide();
        m_upBtn->hide();
        m_downBtn->hide();
    } else {
        m_deleteBtn->hide();
    }
}

void IMActivityItem::setSelectStatus(bool flag)
{
    if (m_isFirst || !m_bgGroup)
        return;

    if (!flag)
        m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
    else {
        m_bgGroup->setBackgroundRole(DPalette::FrameShadowBorder);
    }
    if (!m_isEdit && flag) {
        int index = IMModel::instance()->getIMIndex(m_item);
        int count = IMModel::instance()->getCurIMList().count();

        if (count <= 2) {
            m_upBtn->setEnabled(false);
            m_downBtn->setEnabled(false);
        }
        if (index == 1) {
            m_upBtn->setEnabled(false);
            m_downBtn->setEnabled(true);
        } else if (index == count - 1) {
            m_upBtn->setEnabled(true);
            m_downBtn->setEnabled(false);
        } else {
            m_upBtn->setEnabled(true);
            m_downBtn->setEnabled(true);
        }
        m_configBtn->show();
        m_upBtn->show();
        m_downBtn->show();
        update();
    } else {
        m_configBtn->hide();
        m_upBtn->hide();
        m_downBtn->hide();
    }
}

void IMActivityItem::onUpItem()
{
    emit upBtnClicked(m_item);
}

void IMActivityItem::onDownItem()
{
    emit downBtnClicked(m_item);
}

void IMActivityItem::onConfigItem()
{
    emit configBtnClicked(m_item);
}

void IMActivityItem::onDeleteItem()
{
    emit deleteBtnClicked(m_item);
}

void IMActivityItem::enterEvent(QEvent *event)
{
    setSelectStatus(true);
    SettingsItem::enterEvent(event);
}

void IMActivityItem::leaveEvent(QEvent *event)
{
    setSelectStatus(false);
    SettingsItem::leaveEvent(event);
}

ToolButton::ToolButton(QWidget *parent)
    : QToolButton(parent)
{
}

void ToolButton::paintEvent(QPaintEvent *e)
{
    if (isEnabled()) {
        QToolButton::paintEvent(e);
    } else {
        QPainter p(this);
        p.drawPixmap({(width() - 16) / 2, (height() - 16) / 2, 16, 16}, icon().pixmap(16, 16, QIcon::Mode::Disabled));
    }
}

} // namespace widgets
} // namespace dcc_fcitx_configtool
