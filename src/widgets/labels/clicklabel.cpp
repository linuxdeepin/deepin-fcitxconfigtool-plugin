#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent):
    QLabel(parent)
{
<<<<<<< HEAD
    setMaximumSize(QSize(16,16));
    setMaximumWidth(25);
=======
  //  setMaximumSize(QSize(16,16));
 //   setMaximumWidth(25);
>>>>>>> 1144aa4... fix: 修复输入法管理列表按钮样式问题
}

ClickLabel::~ClickLabel()
{

}

void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
            emit clicked();
    }

}

void ClickLabel::setIcon(const QIcon &icon)
{
    QPixmap img = icon.pixmap(icon.actualSize(QSize(16, 16)));
    this->setPixmap(img);
}
