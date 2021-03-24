/*
 * Copyright (C) 2011 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     andywang <andywang_cm@deepin.com>
 *
 * Maintainer: andywang <andywang_cm@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "comboxwidget.h"
#include "utils.h"

#include <QHBoxLayout>
#include <QComboBox>
#include <QDebug>
#include <QStringList>
#include <QMouseEvent>
#include <QLabel>

namespace dcc_fcitx_configtool {
namespace widgets {

Fcitx_ComboxWidget::Fcitx_ComboxWidget(QFrame *parent)
    : Fcitx_ComboxWidget(new QLabel, parent)
{
}

Fcitx_ComboxWidget::Fcitx_ComboxWidget(const QString &title, QFrame *parent)
    : Fcitx_ComboxWidget(new QLabel(title), parent)
{
}

Fcitx_ComboxWidget::Fcitx_ComboxWidget(QWidget *widget, QFrame *parent)
    : Fcitx_SettingsItem(parent)
    , m_leftWidget(widget)
    , m_switchComboBox(new QComboBox)
    , m_str("")
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    m_titleLabel = qobject_cast<QLabel *>(m_leftWidget);
    if (m_titleLabel) {
        m_str = m_titleLabel->text();
    }

    mainLayout->addWidget(m_leftWidget, 0, Qt::AlignVCenter);
    mainLayout->setStretchFactor(m_leftWidget, 3);
    mainLayout->addWidget(m_switchComboBox, 0, Qt::AlignVCenter);
    mainLayout->setStretchFactor(m_switchComboBox, 7);

    m_leftWidget->setFixedWidth(ComboxTitleWidth);
    m_leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setLayout(mainLayout);

    connect(m_switchComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Fcitx_ComboxWidget::onIndexChanged);
    connect(m_switchComboBox, &QComboBox::currentTextChanged, this, &Fcitx_ComboxWidget::onSelectChanged);
    connect(m_switchComboBox, &QComboBox::currentTextChanged, this, [this] {
        Q_EMIT dataChanged(m_switchComboBox->currentData());
    });
}

void Fcitx_ComboxWidget::setComboxOption(const QStringList &options)
{
    m_switchComboBox->blockSignals(true);
    for (QString item : options) {
        m_switchComboBox->addItem(item);
    }
    m_switchComboBox->blockSignals(false);
}

void Fcitx_ComboxWidget::setCurrentText(const QString &curText)
{
    m_switchComboBox->blockSignals(true);
    m_switchComboBox->setCurrentText(curText);
    m_switchComboBox->blockSignals(false);
}

void Fcitx_ComboxWidget::setTitle(const QString &title)
{
    QLabel *label = qobject_cast<QLabel *>(m_leftWidget);
    if (label) {
        label->setWordWrap(true);
        label->setText(title);
        m_str = title;
    }

    setAccessibleName(m_str);
}

QComboBox *Fcitx_ComboxWidget::comboBox()
{
    return m_switchComboBox;
}

void Fcitx_ComboxWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_switchComboBox->geometry().contains(event->pos())) {
        Q_EMIT clicked();
    }

    return Fcitx_SettingsItem::mouseReleaseEvent(event);
}

void Fcitx_ComboxWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if (event->type() == QEvent::Resize) {
        if (m_titleLabel) {
            QFontMetrics fontMetrics(m_titleLabel->font());
            int fontSize = fontMetrics.width(m_str);
            if (fontSize > m_titleLabel->width()) {
                m_titleLabel->setText(fontMetrics.elidedText(m_str, Qt::ElideRight, m_titleLabel->width()));

                m_titleLabel->setToolTip(m_str);
            } else {
                m_titleLabel->setText(m_str);
                m_titleLabel->setToolTip("");
            }
        }
    }
    Fcitx_SettingsItem::resizeEvent(event);
}

} // namespace widgets
} // namespace dcc
