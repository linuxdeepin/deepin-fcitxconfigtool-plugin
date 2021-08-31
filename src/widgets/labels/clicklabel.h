#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QIcon>

class ClickLabel :public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QWidget *parent);
    ~ClickLabel();
    void setIcon(const QIcon &icon);

signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // CLICKLABEL_H
