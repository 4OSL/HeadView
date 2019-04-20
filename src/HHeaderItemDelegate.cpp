#include <QApplication>
#include <QPainter>

#include "HHeaderItemDelegate.h"
#include "HHeaderView.h"
#include <QDebug>

HHeaderItemDelegate::HHeaderItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void HHeaderItemDelegate::setHeaderView(HHeaderView *pHeader)
{
    m_pHeaderView = pHeader;
}

///< headerView中绘制的item，根据不同的操作显示不同的效果
void HHeaderItemDelegate::paint (QPainter * painter
                                ,const QStyleOptionViewItem& option
                                ,const QModelIndex &index) const
{

    int row = index.row();
    int col = index.column();

    //const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
    
    QRect smallRect;
    //判断是否有checkbox
    ///< 目前我是不会设置checkbox的
    if (m_pHeaderView->isCheckedEnable(row, col))
    {
        smallRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                        QSize(option.fontMetrics.width(index.data(Qt::DisplayRole).toString()) + 25, option.fontMetrics.height() + 3),
                                        option.rect);
    }
    else
    {
        smallRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                        QSize(option.fontMetrics.width(index.data(Qt::DisplayRole).toString()) + 8, option.fontMetrics.height() + 3),
                                        option.rect);
    }
    
    QStyleOptionHeader header_opt;
    header_opt.rect = option.rect;
    header_opt.position = QStyleOptionHeader::Middle;
    header_opt.textAlignment = Qt::AlignCenter;

    header_opt.state = option.state;
    //header_opt.state |= QStyle::State_HasFocus;//QStyle::State_Enabled | QStyle::State_Horizontal | QStyle::State_None | QStyle::State_Raised;

    //判断是否能够排序
    ///< 支持排序
    if (m_pHeaderView->isSortedEnable(row, col))
    {
        //可以排序
        //获取它当前的排序顺序
        int ret = m_pHeaderView->sortedDirection(row, col);
        if (0 == ret)
        {
            header_opt.sortIndicator = QStyleOptionHeader::SortUp;
        }
        else if (1 == ret)
        {
            header_opt.sortIndicator = QStyleOptionHeader::SortDown;
        }
        else
        {
            header_opt.sortIndicator = QStyleOptionHeader::None;
        }    
    }
    if (m_pHeaderView->isItemPress(row, col))
    {
        header_opt.state |= QStyle::State_Sunken; //按钮按下效果
    }

    painter->save();
    QApplication::style()->drawControl(QStyle::CE_Header, &header_opt, painter);
    painter->restore();
    painter->setPen(QColor(255,0,0));
    QStyleOptionViewItemV4 xopt(option);
    xopt.state &= ~QStyle::State_MouseOver;
    if (m_pHeaderView->isCheckedEnable(row, col))
    {
        //判断是该单元格是否有checkbox
        xopt.features |= QStyleOptionViewItemV4::HasCheckIndicator;

        //判断checkbox的状态
        Qt::CheckState state = m_pHeaderView->checkedState(row, col);
        if (Qt::Unchecked == state)
        {
            xopt.state |= QStyle::State_Off;
        }
        else if (Qt::PartiallyChecked == state)
        {
            xopt.state |= QStyle::State_NoChange;
        }
        else if (Qt::Checked == state)
        {
            xopt.state |= QStyle::State_On;
        }
    }  

    xopt.rect = smallRect;
    if (!m_pHeaderView->isColHide(col))
    {
        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &xopt, painter);

         //首先要判断是否处于hover状态
        if (header_opt.state & QStyle::State_MouseOver)
        {
            //判断是否能够排序，如果能排序，则显示图标
            if (m_pHeaderView->isCustomMenuEnable(row, col))
            {
                drawMenuBtn(row, col, option.rect, painter);      
            }    
        }

         //判断前面1列是否隐藏，如果隐藏了，需要在左边画上三角符号
        if (m_pHeaderView->isSectionHidden(col - 1))
        {
            drawPreBtn(option.rect, painter);
        }

        //判断后面1列是否隐藏，如果隐藏了，需要在右边画上三角符号
        if (m_pHeaderView->isSectionHidden(col + 1))
        {
            drawNextBtn(option.rect, painter);
        }
    }

}


bool HHeaderItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return false;
}

void HHeaderItemDelegate::drawMenuBtn(int row, int col, const QRect& rect, QPainter* painter) const
{
    QRect brect = QRect(rect.right() - 5 - 13, rect.center().y() - 6, 13, 13);

    //判断鼠标是否在menu的上面，如果是，则要用黑色显示，否则灰色
    int state = m_pHeaderView->customMenuState(row, col);
    bool enabled = (state == 1 ? true : false);

    painter->save();
    painter->setPen(enabled ? QColor(186, 186, 186) : QColor(223, 223, 223));
    painter->setBrush(QColor(246, 246, 246));
    painter->drawRect(brect.adjusted(0, 0 ,-1, -1));

    painter->setPen(enabled ? QColor(71, 71, 71) : QColor(193, 193, 193));
    painter->drawLine(brect.left() + 3, brect.top() + 5, brect.right() - 3, brect.top() + 5);
    painter->drawLine(brect.left() + 4, brect.top() + 6, brect.right() - 4, brect.top() + 6);
    painter->drawLine(brect.left() + 5, brect.top() + 7, brect.right() - 5, brect.top() + 7);
    painter->drawPoint(brect.left() + 6, brect.top() + 8);
    painter->restore();
}

void HHeaderItemDelegate::drawPreBtn(const QRect& rect, QPainter* painter) const 
{
    QRect brect = QRect(rect.left() + 1, rect.center().y() - 6, 13, 13);

    painter->save();
    painter->setPen(QColor(71, 71, 71));
    painter->drawLine(brect.left() + 1, brect.center().y() - 3, brect.left() + 1, brect.center().y() + 3);
    painter->drawLine(brect.left() + 2, brect.center().y() - 2, brect.left() + 2, brect.center().y() + 2);
    painter->drawLine(brect.left() + 3, brect.center().y() - 1, brect.left() + 3, brect.center().y() + 1);
    painter->drawPoint(brect.left() + 4, brect.center().y());
    painter->restore();
}

void HHeaderItemDelegate::drawNextBtn(const QRect& rect, QPainter* painter) const
{
    QRect brect = QRect(rect.right() - 13, rect.center().y() - 6, 13, 13);;

    painter->save();
    painter->setPen(QColor(71, 71, 71));
    painter->drawLine(brect.right() - 2, brect.center().y() - 3, brect.right() - 2, brect.center().y() + 3);
    painter->drawLine(brect.right() - 3, brect.center().y() - 2, brect.right() - 3, brect.center().y() + 2);
    painter->drawLine(brect.right() - 4, brect.center().y() - 1, brect.right() - 4, brect.center().y() + 1);
    painter->drawPoint(brect.right() - 5, brect.center().y());
    painter->restore();
}
