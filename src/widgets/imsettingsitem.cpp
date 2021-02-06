#include "imsettingsitem.h"
#include "settingsitem.h"
#include <DPalette>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QLabel>
#include <QApplication>
#include <QFrame>
#include <DKeySequenceEdit>

DWIDGET_USE_NAMESPACE

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

void IMSettingsItem::setItemSelected(bool status)
{
    if (status) {
        QIcon icon = DStyle::standardIcon(QApplication::style(), DStyle::SP_IndicatorChecked);
        m_labelIcon->setPixmap(icon.pixmap(QSize(20, 20)));
    } else {
        m_labelIcon->clear();
    }
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
