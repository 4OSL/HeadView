#ifndef HeaderItemDelegate_H
#define HeaderItemDelegate_H

#include <QStyledItemDelegate>

class HHeaderView;
class HHeaderItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    HHeaderItemDelegate(QObject *parent = 0);
    void setHeaderView(HHeaderView* pHeader);
    virtual void paint (QPainter *painter
                       ,const QStyleOptionViewItem &option
                       ,const QModelIndex &index )const;

    virtual bool editorEvent(QEvent *event
                            ,QAbstractItemModel *model
                            ,const QStyleOptionViewItem &option
                            ,const QModelIndex &index);

private:
    void drawMenuBtn(int row, int col, const QRect& rect, QPainter* painter) const;
    void drawPreBtn(const QRect& rect, QPainter* painter) const;
    void drawNextBtn(const QRect& rect, QPainter* painter) const;
private:
    HHeaderView *m_pHeaderView;
};

#endif // HeaderItemDelegate_H
