#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QAction>

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = 0);
    ~TableView();

    /**< 初始化表格，自定义横向表头 */
    void initHeaderView();
     /**< 添加表头菜单 */
    void initAction();

public slots:
    ////< 事件可继承重载
    virtual void onMenuHorizontalHeaderRequested(QPoint pos);
    virtual void onMenuVerticalHeaderRequested(QPoint pos);

    virtual void onColumnClicked(int nIndex);
    virtual void onRowClicked(int nIndex);

    virtual void onCreateVariable();
    virtual void onDeleteVariable();
    virtual void onModifyVariable();

private:
    QMenu       *m_popMenu;        ////< 菜单
    QAction     *m_actionDel;      ////< 删除
    QAction     *m_actionMod;      ////< 修改
    QAction     *m_actionCreate;   ////< 新建

};

#endif
