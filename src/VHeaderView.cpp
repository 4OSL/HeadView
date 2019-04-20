#include <QMouseEvent>
#include <QPainter>

#include "VHeaderView.h"
//#include "DataTreeView.h"

VHeaderView* VHeaderView::_Instance = NULL;

VHeaderView::VHeaderView(Qt::Orientation orientation, QWidget * parent) : QHeaderView(orientation, parent)
{
    _Instance = this;
    //this->setResizeMode(QHeaderView::Fixed);
    _selectRow = -1;
}

VHeaderView::~VHeaderView()
{
}

void VHeaderView::mousePressEvent ( QMouseEvent * event )
{
    //获取当前点击的行号
    int row = this->logicalIndexAt (event->pos());

    //保存行号
    _selectRow = row;

    //获取当前点中的树形节点的index
//    QModelIndex selIndex = DataTreeView::_Instance->rowIndex(row);
//    if (!selIndex.isValid())
//        return;

    //获取树形的选择模型
//    QItemSelectionModel* selModel = DataTreeView::_Instance->selectionModel();
//    if (NULL == selModel)
//        return;

    //清空之前选中的
//    selModel->clear();

    //选中当前行
//    selModel->setCurrentIndex(selIndex, QItemSelectionModel::Rows | QItemSelectionModel::Select);

    //需要设置为焦点，才能高亮显示
    //DataTreeView::_Instance->setFocus();
}

//轻量级的重载（相对paintevent） 重画每一列
void VHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    //先调用默认的处理
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    //判断是否选中，如果选中了当前行，则要画一个三角符号
    if (_selectRow == logicalIndex)
    {
        drawPreBtn(rect, painter);
        viewport()->update();
    }
}

void VHeaderView::drawPreBtn(const QRect& rect, QPainter* painter) const
{
    QRect brect = QRect(rect.right() - 13, rect.center().y() - 6, 13, 13);

    painter->save();
    painter->setPen(QColor(71, 71, 71));
    painter->drawLine(brect.right() - 4, brect.center().y() - 3, brect.right() - 4, brect.center().y() + 3);
    painter->drawLine(brect.right() - 3, brect.center().y() - 2, brect.right() - 3, brect.center().y() + 2);
    painter->drawLine(brect.right() - 2, brect.center().y() - 1, brect.right() - 2, brect.center().y() + 1);
    painter->drawPoint(brect.right() - 1, brect.center().y());
    painter->restore();
}

void VHeaderView::selectRow(int row)
{
    _selectRow = row;
    viewport()->update();
}
