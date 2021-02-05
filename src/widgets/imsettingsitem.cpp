#include "imsettingsitem.h"

#include "settingsitem.h"

#include <DPalette>
#include <DStyle>

#include <QStyle>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QLabel>
#include <QApplication>
#include <DStyle>
#include <QFrame>
#include <DKeySequenceEdit>
DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

namespace dcc {
namespace widgets {

IMSettingsItem::IMSettingsItem(QString str, QFrame *parent)
    : SettingsItem(parent)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(20, 0, 10, 0);
    this->setLayout(m_layout);
    m_labelText = new QLabel(this);
    m_labelText->setText(str);
    m_labelIcon = new QLabel(this);
    m_layout->addWidget(m_labelText);
    m_layout->addStretch();
    m_layout->addWidget(m_labelIcon);

    m_layout->addWidget(new DKeySequenceEdit);
    this->setFixedHeight(40);
}

IMSettingsItem::~IMSettingsItem()
{
}

void IMSettingsItem::setFcitxItem(FcitxQtInputMethodItem item)
{
    m_item = item;
    m_labelText->setText(item.name());
    m_labelText->adjustSize();
}

void IMSettingsItem::setFilterStr(QString str)
{
    if (!(m_item.name().indexOf(str, Qt::CaseInsensitive) != -1
          || m_item.uniqueName().indexOf(str, Qt::CaseInsensitive) != -1
          || m_item.langCode().indexOf(str, Qt::CaseInsensitive) != -1)) {
        this->hide();
    } else {
        this->show();
    }
}

void IMSettingsItem::addBackground()
{
    //加入一个 DFrame 作为圆角背景
    if (m_bgGroup)
        m_bgGroup->deleteLater();
    m_bgGroup = new DFrame(this);
    m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
    m_bgGroup->setLineWidth(0);
    DStyle::setFrameRadius(m_bgGroup, 8);

    //将 m_bgGroup 沉底
    m_bgGroup->lower();
    //设置m_bgGroup 的大小
    m_bgGroup->setFixedSize(size());
}

void IMSettingsItem::setItemSelected(bool status)
{
    if (status) {
        QIcon icon = DStyle::standardIcon(QApplication::style(), DStyle::SP_IndicatorChecked);
        m_labelIcon->setPixmap(icon.pixmap(QSize(20, 20)));
    } else {
        m_labelIcon->clear();
    }
}

void IMSettingsItem::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);

    //设置m_bgGroup 的大小
    if (m_bgGroup)
        m_bgGroup->setFixedSize(size());
}

void IMSettingsItem::mousePressEvent(QMouseEvent *event)
{
    setItemSelected(true);
    emit sig_itemClicked(this);
}

void IMSettingsItem::enterEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ObviousBackground);
}

void IMSettingsItem::leaveEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
}
} // namespace widgets
} // namespace dcc
