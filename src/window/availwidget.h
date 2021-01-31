#ifndef AVAILWIDGET_H
#define AVAILWIDGET_H

#include "widgets/titlelabel.h"
#include "widgets/settingsgroup.h"
#include "widgets/settingshead.h"
#include "widgets/imsettingsitem.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <fcitxInterface/global.h>


using namespace Dtk::Widget;
using namespace dcc::widgets;

class AvailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AvailWidget(QWidget* parent = nullptr);
    ~AvailWidget();
    void updateUI(const FcitxQtInputMethodItemList&IMlist);
    FcitxQtInputMethodItem getSeleteIm();
signals:
    void sig_seleteIM(bool);
public slots:
    void slot_searchIM(const QString& str);
private:
    QList<QPair<QString, FcitxQtInputMethodItemList>> m_filteredIMEntryList;
    SettingsGroup *m_group;
    QString m_search;
    FcitxQtInputMethodItemList m_imlist;
};

#endif // AVAILWIDGET_H
