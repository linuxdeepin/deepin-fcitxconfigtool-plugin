#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//#include "interface/namespace.h"
//#include "comboxwidget.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

//    dcc::widgets::ComboxWidget *m_cmbMiniEffect;    //最小化效果


};

#endif // WIDGET_H
