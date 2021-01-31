#ifndef IMADDWINDOW_H
#define IMADDWINDOW_H

#include "availwidget.h"
#include "widgets/titlelabel.h"
#include "widgets/searchinput.h"
#include "widgets/buttontuple.h"
#include <QWidget>
#include <DCommandLinkButton>
#include <DFloatingButton>
#include <DListView>
#include <fcitxInterface/global.h>

using namespace Fcitx;

using namespace dcc::widgets;
using namespace Dtk::Widget;
class IMAddWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMAddWindow(QWidget *parent = nullptr);
    virtual ~IMAddWindow();
signals:
    void sig_cancel();
    void sig_addIM();
private:
    void initUI();
    void initConnect();

private slots:
    void slot_cancel();
    void slot_addIM();
    void slot_openStore();
    void slot_updateUI();
    void slot_seleteIM(bool);
private:
    SearchInput *m_searchLEdit{nullptr};
    AvailWidget *availWidget{nullptr};
    DCommandLinkButton *m_storeBtn{nullptr};
    ButtonTuple *m_buttonTuple{nullptr};
};

#endif // IMADDWINDOW_H
