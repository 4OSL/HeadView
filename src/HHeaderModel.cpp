#include <QSize>

#include "HHeaderModel.h"

HHeaderModel::HHeaderModel(QObject *parent)
{
    m_nMaxCol = 0;
}
HHeaderModel::~HHeaderModel()
{
}
/**
 ** 为model中各个单元格cell(row,col)设置待显示的值(就是一个文本)
 ** 无论该cell是否属于一个合并单元格，都要设置其值
**/
void HHeaderModel::setItem(int row, int col, const QString& text)
{
    ModelData* data = new ModelData();
    data->strText = text;
   
    m_modelData[row][col] = data;

    if (m_nMaxCol < col)
    {
        m_nMaxCol = col;
    }
}
/**
 ** 获取cell(row,col)的文本内容
**/
QString HHeaderModel::item(int row, int col)
{
    QMap<int, QMap<int, ModelData*> >::Iterator iterRow = m_modelData.find(row);
    if (iterRow == m_modelData.end() || iterRow.value().isEmpty())
    {
        return QString();
    }

    QMap<int, ModelData*>::Iterator iterCol = iterRow.value().find(col);
    if (iterCol == iterRow.value().end())
    {
        return QString();
    }

    return iterCol.value()->strText;
}
/**
 ** param firstRow:本合并单元格的，起始行
 ** param firstColumn:本合并单元格的起始列
 ** param rowSpanCount:本合并单元格需要占用多少行
 ** param columnSpanCount:本合并单元格需要占用多少列
*/
void HHeaderModel::setSpan(int firstRow,int firstColumn
                          ,int rowSpanCount,int columnSpanCount)
{
    for(int row = firstRow; row < firstRow + rowSpanCount; ++row)
    {
        for(int col = firstColumn; col < firstColumn + columnSpanCount; ++col)
        {
            ///< 如果某一个合并单元格是从cell(0,0)开始，占用1行，4列
            ///< 那么cell(0,0),cell(0,1),cell(0,2),cell(0,3)
            ///< 就是属于这个合并单元的，都应当记录下来
            m_cellSpanList.append(CellSpan(row,col
                                 ,rowSpanCount,columnSpanCount
                                 ,firstRow,firstColumn));
        }
    }
}
/**
 ** 获取cell(row,column)所在的合并单元格(CellSpan)
**/
const CellSpan& HHeaderModel::getSpan(int row, int column)
{
    for(QList<CellSpan>::const_iterator iter = m_cellSpanList.begin(); iter != m_cellSpanList.end(); ++iter)
    {
        if((*iter).nCurRow == row && (*iter).nCurCol == column)
        {
            return *iter;
        }
    }

    return m_stInvalidCellSpan;
}

QModelIndex HHeaderModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (row < 0 || column < 0 || m_modelData.isEmpty())
        return QModelIndex();

    MapHeaderData::const_iterator iterRow = m_modelData.find(row);
    if (iterRow == m_modelData.end())
        return QModelIndex();

    if (iterRow.value().isEmpty())
        return QModelIndex();

    QMap<int, ModelData*>::const_iterator iterCol = iterRow.value().find(column);
    if (iterCol == iterRow.value().end())
        return QModelIndex();

    return createIndex(row, column, iterCol.value());
}

QModelIndex HHeaderModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int HHeaderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_modelData.size();
}

int HHeaderModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_nMaxCol + 1;
}
/**
 ** 设置值不考虑合并单元格，每一个index都要返回
 ** 从代码来看，似乎本函数并未被调用
*/
QVariant HHeaderModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (Qt::DisplayRole == role || Qt::EditRole == role)
    {
        MapHeaderData::const_iterator iterRow = m_modelData.find(row);
        if (iterRow == m_modelData.end() || iterRow.value().isEmpty())
            return QString();

        QMap<int, ModelData*>::const_iterator iterCol = iterRow.value().find(col);
        if (iterCol == iterRow.value().end())
        {
            return QString();
        }

        return iterCol.value()->strText;
    }
    return QVariant();
}

Qt::ItemFlags HHeaderModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled;  
}

bool HHeaderModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
    return false;
}


HHeaderModel::ModelData* HHeaderModel::modelData(const QModelIndex & index) const
{
    if (!index.isValid())
        return NULL;

    int row = index.row();
    int col = index.column();

    MapHeaderData::const_iterator iterRow = m_modelData.find(row);
    if (iterRow == m_modelData.end() || iterRow.value().isEmpty())
        return NULL;

    QMap<int, ModelData*>::const_iterator iterCol = iterRow.value().find(col);
    if (iterCol == iterRow.value().end())
    {
        return NULL;
    }

    return iterCol.value();
}

QVariant HHeaderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //重载了sectionSizeFromContents函数，但没有调用默认的处理，所以不会走到这里。
    if (role == Qt::SizeHintRole)
    {
        return QSize(200, 100);
    }

	return QVariant();

   // return QAbstractItemModel::headerData(section,orientation,role);
}
