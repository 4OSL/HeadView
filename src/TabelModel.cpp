#include "TabelModel.h"
#include <QDebug>

TabelModel::TabelModel(QObject *parent) : QAbstractTableModel(parent)
{

}

TabelModel::~TabelModel()
{
    m_headerList.clear();
    m_data.clear();
}

int TabelModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

int TabelModel::columnCount(const QModelIndex &) const
{
    return m_headerList.count();
}

///< 设置表格单元格数据内容
QVariant TabelModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        const int row = index.row();
        const int column = index.column();
        if (row >= m_data.size())
            return QVariant();
        const int colSize = m_data.at(row).size();
        if (column >= colSize)
               return QVariant();
        return m_data.at(row).at(column);
    }
    else
    {
        return QVariant();
    }
}

///< 因为表头已经有自定义的了,本函数不会被调用
QVariant TabelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
    {
        return QVariant(m_headerList.at(section));
    }
    else if(orientation == Qt::Vertical)
    {
        return QVariant(section+1);
    }
    else
    {
        return QVariant();
    }
}

void TabelModel::setHeaderList(const QStringList& list)
{
    m_headerList = list;
}

void TabelModel::updateData(const QList<QList<QVariant> >&listVariant)
{
    m_data = listVariant;
}

