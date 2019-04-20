#ifndef TABELMODEL_H
#define TABELMODEL_H

#include <QObject>
#include <QAbstractTableModel>

/**
 * @brief 自定义列表模型
 */
class TabelModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TabelModel(QObject *parent = 0);
    ~TabelModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void setHeaderList(const QStringList&);
    void updateData(const QList<QList<QVariant> >&);
private:
    QStringList m_headerList;           ////< 表头标题
    QList<QList<QVariant> > m_data;     ////< 表格内容（QVariant万能数据类型保证表格数据的多元性）
};

#endif
