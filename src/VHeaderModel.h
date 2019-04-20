#ifndef VHEADERMODEL_H
#define VHEADERMODEL_H

#include <QAbstractItemModel>

class DataNode;

class VHeaderModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    VHeaderModel(QObject *parent = 0);
    ~VHeaderModel();

    virtual QModelIndex index(int row, int column,
                      const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    //virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
};

#endif
