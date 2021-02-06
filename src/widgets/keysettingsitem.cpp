#include "keysettingsitem.h"
#include <QComboBox>
#include <QMouseEvent>

KeyLabelWidget::KeyLabelWidget(QStringList list, QWidget *p)
    : QWidget(p)
{
    m_keyEdit = new DKeySequenceEdit(this);
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 10, 0);
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_keyEdit);
    setLayout(m_mainLayout);

    if (list.isEmpty())
        list << "";
    for (const QString &key : list) {
        KeyLabel *label = new KeyLabel(key);
        label->setAccessibleName("LABEL");
        m_list << label;
        m_mainLayout->addWidget(label);
    }
    adjustSize();
    connect(m_keyEdit, SIGNAL(editingFinished()), this, SLOT(editFinish()));
    m_keyEdit->hide();
    //m_keyEdit->setFixedWidth(130);
}

KeyLabelWidget::~KeyLabelWidget()
{
    for (KeyLabel *label : m_list) {
        m_mainLayout->removeWidget(label);
        label->deleteLater();
    }
}

void KeyLabelWidget::setList(const QStringList &list)
{
    for (KeyLabel *label : m_list) {
        m_mainLayout->removeWidget(label);
        label->deleteLater();
    }
    m_list.clear();
    for (const QString &key : list) {
        QString tmpKey = key.toLower();
        if (!tmpKey.isEmpty()) {
            tmpKey[0] = tmpKey[0].toUpper();
        }
        KeyLabel *label = new KeyLabel(tmpKey);
        label->setAccessibleName("LABEL");
        m_list << label;
        m_mainLayout->addWidget(label);
    }
}

QString KeyLabelWidget::getKeyToStr()
{
    QString key;
    for (int i = 0; i < m_list.count(); ++i) {
        if (i == m_list.count() - 1) {
            key += m_list[i]->text();
        } else {
            key += (m_list[i]->text() + "+");
        }
    }
    return QKeySequence(key).toString();
}

void KeyLabelWidget::editFinish()
{
    m_keyEdit->hide();
    QString str = m_keyEdit->keySequence().toString();
    if (str.isEmpty()) {
        for (KeyLabel *label : m_list) {
            label->show();
        }
        return;
    }
    for (KeyLabel *label : m_list) {
        m_mainLayout->removeWidget(label);
        label->deleteLater();
    }

    m_list.clear();

    for (const QString &key : str.split("+")) {
        KeyLabel *label = new KeyLabel(key);
        label->setAccessibleName("LABEL");
        m_list << label;
        m_mainLayout->addWidget(label);
    }
    emit editedFinish();
}

void KeyLabelWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
}

void KeyLabelWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
}

void KeyLabelWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->x() < this->x() / 3)
        return;
    if (m_keyEdit->isHidden()) {
        m_keyEdit->show();
        m_keyEdit->setFocus();
        m_keyEdit->clear();

        for (KeyLabel *label : m_list) {
            label->hide();
        }
    }
}

void KeyLabelWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

KeySettingsItem::KeySettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : SettingsItem(parent)
{
    m_lable.setText(text);
    m_keyWidget = new KeyLabelWidget(list, parent);

    m_hLayout.addWidget(&m_lable);
    m_hLayout.addStretch();
    m_hLayout.addWidget(m_keyWidget);
    setFixedHeight(48);
    setLayout(&m_hLayout);
    connect(m_keyWidget, &KeyLabelWidget::editedFinish, this, &KeySettingsItem::editedFinish);
}

void KeySettingsItem::setList(const QStringList &list)
{
    m_keyWidget->setList(list);
}

void KeySettingsItem::enterEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ObviousBackground);
}

void KeySettingsItem::leaveEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
}

ComBoboxSettingsItem::ComBoboxSettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : SettingsItem(parent)
{
    m_combox = new QComboBox(this);
    m_combox->addItems(list);
    m_label = new QLabel(text, this);
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_label);
    m_mainLayout->addWidget(m_combox);
    setLayout(m_mainLayout);
    setFixedHeight(48);
}

ComBoboxSettingsItem::~ComBoboxSettingsItem()
{
}

void ComBoboxSettingsItem::enterEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ObviousBackground);
}

void ComBoboxSettingsItem::leaveEvent(QEvent *event)
{
    if (m_bgGroup)
        m_bgGroup->setBackgroundRole(DPalette::ItemBackground);
}
