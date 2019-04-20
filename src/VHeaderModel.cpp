#include <QSize>

#include <QFontMetrics>
//#include "NodeManager.h"
#include "VHeaderModel.h"
//#include "DataNode.h"
//#include "Const.h"
#include "VHeaderView.h"

VHeaderModel::VHeaderModel(QObject *parent) : QAbstractItemModel(parent)
{
}

VHeaderModel::~VHeaderModel()
{
}

QModelIndex VHeaderModel::index(int row, int column, const QModelIndex &parent) const
{
   Q_UNUSED(parent);
   if (row < 0 || column < 0 /*|| NodeManager::getInstance()->sortMap().isEmpty()*/)
        return QModelIndex();

    //QMap<int, DataNode* >::const_iterator iterRow = NodeManager::getInstance()->sortMap().find(row);
//    if (iterRow == NodeManager::getInstance()->sortMap().end())
//        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex VHeaderModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int VHeaderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    //return NodeManager::getInstance()->sortMap().size();
    return 2;
}

int VHeaderModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant VHeaderModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant VHeaderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::SizeHintRole)
    {
        QFontMetrics fonMetrics(VHeaderView::_Instance->font());
        //int size = NodeManager::getInstance()->sortMap().size();
        int size = 30;
        int width = fonMetrics.width(QString::number(size));
        return QSize(width + 13, 0); //可以设定头的宽度，高度是默认的30，如果需要设置，则要重载相关函数，和delegate中实现，还没实现。
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical) 
    {
        return QString::number(section);
//        DataNode* node = NodeManager::getInstance()->sortMap()[section];
//        if (NULL != node)
//        {
//            int serial = NodeManager::getInstance()->serialNoOfNode(node);
//            return QString::number(serial+1);
//        }
    }
    return QVariant();
}

/*Qt::ItemFlags VHeaderModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}*/
