#ifndef IMSETTINGSITEM_H
#define IMSETTINGSITEM_H

#include "settingsitem.h"
#include <fcitxqtinputmethoditem.h>
using namespace dcc::widgets;

namespace dcc {
namespace widgets {

class IMSettingsItem : public SettingsItem
{
    Q_OBJECT

public:
    explicit IMSettingsItem(QString str =QString(),QFrame *parent = nullptr);
    void setFcitxItem(FcitxQtInputMethodItem item);
    void addBackground();
    void clearItemSelected();
signals:
    void sig_itemClicked(IMSettingsItem*item);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event)override;
    void enterEvent(QEvent *event)override;
    void leaveEvent(QEvent *event)override;

public:
    QLabel *m_labelText{nullptr};
    QLabel *m_labelIcon{nullptr};
    QHBoxLayout*m_layout{nullptr};
    FcitxQtInputMethodItem m_item;

};

}
}
#endif // IMSETTINGSITEM_H

