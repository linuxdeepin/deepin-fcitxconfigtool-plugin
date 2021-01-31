#include "immodel.h"
#include <QApplication>

IMModel::IMModel(QObject *parent)
    : QStandardItemModel (parent)
{

}

IMModel::~IMModel()
{

}

Qt::DropActions IMModel::supportedDropActions() const
{
    return Qt::CopyAction|Qt::MoveAction;
}

QStringList IMModel::mimeTypes() const
{
    QStringList types=QStringList()<<"InputMethod";
    return types;
}

QMimeData *IMModel::mimeData(const QModelIndexList &index) const
{
    QMimeData*mimeData =new QMimeData();
    QByteArray encodeData;

    QDataStream stream(&encodeData,QIODevice::WriteOnly);
    foreach (const QModelIndex&ind,index) {
        if (ind.isValid()) {
            stream<<ind.row();
        }
    }
    mimeData->setData("InputMethod",encodeData);
    return mimeData;
}

bool IMModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if(action == Qt::IgnoreAction)
        return true;

    if(!data->hasFormat("InputMethod")||column>0)
        return  false;

    QByteArray encodeData =data->data("InputMethod");
    QDataStream stream(&encodeData,QIODevice::ReadOnly);
    int rows=0;
    if (!stream.atEnd()) {
        int moveRow;
        stream >>moveRow;
        rows = moveRow;
    }

    if(row==0||parent.row()==0)
        return false;

    int insRow;
    if (row!=-1)
        insRow =row;
    else if(parent.isValid())
        insRow=parent.row();
    else
        insRow=rowCount()-1;

    if (rows == insRow)
        return false;
    else if (rows>insRow) {
        m_curIMList.insert(insRow,m_curIMList[rows]);
        m_curIMList.removeAt(rows+1);
    } else {
        FcitxQtInputMethodItem it = m_curIMList[rows];
        m_curIMList.removeAt(rows);
        m_curIMList.insert(insRow,it);
    }
    loadItem();
    return true;
}

Qt::ItemFlags IMModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()||index.row()==0)
        return Qt::ItemIsEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsSelectable;

    return QAbstractItemModel::flags(index)|Qt::ItemIsEditable|Qt::ItemIsDropEnabled|Qt::ItemIsDragEnabled;
}

void IMModel::setEdit(bool flag)
{
    this->m_isDeleteEdit = flag;
    loadItem();
}


void IMModel::slot_filterIMEntryList(const FcitxQtInputMethodItemList &imEntryList)
{
    QSet<QString> languageSet;
    m_curIMList.clear();
    Q_FOREACH(const FcitxQtInputMethodItem & im, imEntryList) {
        if (im.enabled()) {
            m_curIMList.append(im);
        }
    }
    loadItem();
}

void IMModel::loadItem()
{
    int i =0;
    foreach (FcitxQtInputMethodItem it,m_curIMList) {
       QStandardItem* iter = item(i,0);
       DStandardItem*item =dynamic_cast<DStandardItem*>(iter);
       if(!item) {
           item =new DStandardItem();
           this->appendRow(item);
       }

       if (item->text()!=it.name()){
           item->setText(it.name());
       }

       if(i++>0) {
           DViewItemActionList list;
           if (m_isDeleteEdit) {
               DViewItemAction *iconAction = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
               iconAction->setIcon(DStyle::standardIcon(QApplication::style(), DStyle::SP_DeleteButton));
               connect(iconAction,&DViewItemAction::triggered,[=](){deleteItem(item);});
               list.push_back(iconAction);
           } else {
               DViewItemAction *iconAction = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
               iconAction->setIcon(QIcon(":/icons/arrow_up.svg"));
               DViewItemAction *iconAction2 = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
               iconAction2->setIcon(QIcon(":/icons/arrow_down.svg"));
               DViewItemAction *iconAction3 = new DViewItemAction(Qt::AlignBottom, QSize(), QSize(), true);
               iconAction3->setIcon(QIcon(":/icons/setting.svg"));
               connect(iconAction,&DViewItemAction::triggered,[=](){itemUp(item);});
               connect(iconAction2,&DViewItemAction::triggered,[=](){itemDown(item);});
               connect(iconAction3,&DViewItemAction::triggered,[=](){configShow(item);});
               list.push_back(iconAction);
               list.push_back(iconAction2);
               list.push_back(iconAction3);
           }
           item->setActionList(Qt::RightEdge,list);
       }
    }

    while (rowCount()>m_curIMList.count()) {
        removeRow(rowCount()-1);
    }
}

void IMModel::deleteItem(DStandardItem *item)
{
    m_curIMList.removeAt(item->row());
    loadItem();
    emit sig_curIMchanged(m_curIMList);
}

void IMModel::itemUp(DStandardItem *item)
{
    if(item->row()<2)
        return ;
   itemSawp(item->row(),item->row()-1);
}

void IMModel::itemDown(DStandardItem *item)
{
    if(item->row()==m_curIMList.count()-1)
        return ;
    itemSawp(item->row(),item->row()+1);
}

void IMModel::itemSawp(int index, int index2)
{
    if (index <0 || index > m_curIMList.count()-1 || index2 < 0 || index2 > m_curIMList.count()-1 )
        return ;
    m_curIMList.swap(index,index2);
    loadItem();
    emit sig_curIMchanged(m_curIMList);
}

void IMModel::configShow(DStandardItem *item)
{

}
