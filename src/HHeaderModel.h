#ifndef HHEADERMODEL_H
#define HHEADERMODEL_H

#include <QAbstractItemModel>
#include <QDebug>
#include <QMap>


/**
 * @brief 单元格合并大小
 */
struct CellSpan
{
    CellSpan() : nCurRow(-1),nCurCol(-1)
             , nRowSpan(-1), nColSpan(-1)
             , nFirstRow(-1), nFirstCol(-1)
             , bValidFlag(false)
    {
    }

    CellSpan(int row, int col, int spanRow
             ,int spanCol, int firstRow, int firstCol)
    { 
        nCurRow = row;
        nCurCol = col;
        nRowSpan = spanRow;
        nColSpan = spanCol;
        nFirstRow = firstRow;
        nFirstCol = firstCol;
        bValidFlag = true;
    }

    bool isValid() 
    { 
        return bValidFlag;
    }

    void print()
    {
        qDebug()<<"nCurRow  :"<<nCurRow<<"nCurCol  :"<<nCurCol<<"nRowSpan :"<<nRowSpan<<"nColSpan :"<<nColSpan<<"nFirstRow:"<<nFirstRow<<"nFirstCol:"<<nFirstCol;

    }

    int nCurRow;
    int nCurCol;
    int nRowSpan;
    int nColSpan;
    int nFirstRow;
    int nFirstCol;
    bool bValidFlag;
};

/**
 * @brief 水平表头自定义数据模型
 */
class HHeaderModel : public QAbstractItemModel
{
    struct ModelData //模型数据结构
    {
        QString strText;
     
        ModelData() : strText("")
        {
        }
    };

    Q_OBJECT
protected:
    //key rowNo,  key colNo
    typedef QMap<int,QMap<int,HHeaderModel::ModelData*>> MapHeaderData;

public:

    HHeaderModel(QObject *parent = 0);
    ~HHeaderModel();

    void setItem(int row, int col, const QString& text);

    QString item(int row, int col);

    void setSpan(int firstRow, int firstColumn, int rowSpanCount, int columnSpanCount);
    const CellSpan& getSpan(int row, int column);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    //找到对应的模型数据
    ModelData* modelData(const QModelIndex & index) const;

private:

    MapHeaderData m_modelData;
    int m_nMaxCol;

    CellSpan m_stInvalidCellSpan;
    QList<CellSpan> m_cellSpanList;

};


#endif // HHEADERMODEL_H
