#ifndef VHEADERVIEW_H
#define VHEADERVIEW_H

#include <QHeaderView>

class VHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    VHeaderView(Qt::Orientation orientation, QWidget * parent = 0);
    ~VHeaderView();
    static VHeaderView* _Instance;

    void selectRow(int row);
protected:
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

private:
    void drawPreBtn(const QRect& rect, QPainter* painter) const;

private:
    int _selectRow; //保存选中的行
};

#endif
