#ifndef KETSETTINGSITEM_H
#define KETSETTINGSITEM_H

#include "keylabel.h"
#include "settingsitem.h"
#include "comboxwidget.h"
#include <QLabel>
#include <QApplication>
#include <DStyle>
#include <QFrame>
#include <QVBoxLayout>
#include <DKeySequenceEdit>

using namespace Dtk::Widget;
using namespace dcc::widgets;

class KeyLabelWidget : public QWidget
{
    Q_OBJECT
public:
    KeyLabelWidget(QStringList list = {}, QWidget *p = nullptr);
    virtual ~KeyLabelWidget();
    void setList(const QStringList &list);
    QString getKeyToStr();
public slots:
    void editFinish();
signals:
    void editedFinish();

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QHBoxLayout *m_mainLayout {nullptr};
    DKeySequenceEdit *m_keyEdit {nullptr};
    QList<KeyLabel *> m_list;
};

class KeySettingsItem : public SettingsItem
{
    Q_OBJECT
public:
    KeySettingsItem(const QString &text, const QStringList &list = {}, QFrame *parent = nullptr);
    void setList(const QStringList &list);
    QString getKeyToStr() { return m_keyWidget->getKeyToStr(); }
signals:
    void editedFinish();

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QLabel m_lable;
    QHBoxLayout m_hLayout;
    KeyLabelWidget *m_keyWidget;
};

class ComBoboxSettingsItem : public SettingsItem
{
    Q_OBJECT
public:
    ComBoboxSettingsItem(const QString &text, const QStringList &list = {}, QFrame *parent = nullptr);
    virtual ~ComBoboxSettingsItem();
    QComboBox *comboBox() { return m_combox; }

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QHBoxLayout *m_mainLayout {nullptr};
    QComboBox *m_combox {nullptr};
    QLabel *m_label {nullptr};
};

#endif // KETSETTINGSITEM_H
