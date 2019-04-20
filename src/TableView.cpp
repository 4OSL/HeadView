#include "TableView.h"

#include <QDebug>
#include <QMessageBox>

#include "HHeaderView.h"
#include "HHeaderModel.h"


TableView::TableView(QWidget *parent) : QTableView(parent)
{
}

TableView::~TableView()
{
    QAbstractItemModel *pModel = model();
    delete pModel;
    pModel = NULL;
}

void TableView::initHeaderView()
{
   HHeaderView *pHeadView = new HHeaderView(Qt::Horizontal,this);
   HHeaderModel *pHeadModel = new HHeaderModel();

   pHeadView->initHeaderView(pHeadModel);
   pHeadView->setModel(pHeadModel);
   setHorizontalHeader(pHeadView);
}

void TableView::initAction()
{
    horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

    m_popMenu = new QMenu(this);
    m_popMenu->setStyleSheet("QMenu{background-color:rgb(255,255,255);color:rgb(0, 0, 0);font:10pt ""宋体"";}"
                             "QMenu::item:selected{background-color:#CCDAE7;}");

    m_actionDel = new QAction(QStringLiteral("删除"),this);
    m_actionMod = new QAction(QStringLiteral("修改"),this);
    m_actionCreate = new QAction(QStringLiteral("新建"),this);


    connect(m_actionDel,SIGNAL(triggered()),this,SLOT(onDeleteVariable()));
    connect(m_actionMod,SIGNAL(triggered()),this,SLOT(onModifyVariable()));
    connect(m_actionCreate,SIGNAL(triggered()),this,SLOT(onCreateVariable()));

    // 选中一列
    connect(horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(onColumnClicked(int)));

    // 选中一行
    connect(verticalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(onRowClicked(int)));
    connect(horizontalHeader(),SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(onMenuHorizontalHeaderRequested(QPoint)));
    connect(verticalHeader(),SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(onMenuVerticalHeaderRequested(QPoint)));

}

void TableView::onMenuHorizontalHeaderRequested(QPoint pos)
{
    Q_UNUSED(pos)
    qWarning() << "void TableView::onMenuHorizontalHeaderRequested(QPoint pos)";
    m_popMenu->clear();
    m_popMenu->addAction(m_actionCreate);
    m_popMenu->addAction(m_actionMod);
    m_popMenu->addAction(m_actionDel);
    m_popMenu->exec(QCursor::pos());
}

void TableView::onMenuVerticalHeaderRequested(QPoint pos)
{
    Q_UNUSED(pos)
    qWarning() << "void TableView::onMenuVerticalHeaderRequested(QPoint pos)";
    m_popMenu->clear();
    m_popMenu->addAction(m_actionCreate);
    m_popMenu->addAction(m_actionMod);
    m_popMenu->addAction(m_actionDel);
    m_popMenu->exec(QCursor::pos());
}

void TableView::onColumnClicked(int nIndex)
{
    setSelectionBehavior(QAbstractItemView::SelectColumns);
    QMessageBox msgBox;
    msgBox.setText(QStringLiteral("列单击"));
    msgBox.setInformativeText(QString::number(nIndex));
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void TableView::onRowClicked(int nIndex)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    QMessageBox msgBox;
    msgBox.setText(QStringLiteral("行单击"));
    msgBox.setInformativeText(QString::number(nIndex));
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void TableView::onCreateVariable()
{
    QMessageBox msgBox;
    msgBox.setText(QStringLiteral("创建"));
    msgBox.setInformativeText(QStringLiteral("确定创建吗？"));
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void TableView::onDeleteVariable()
{
    QMessageBox msgBox;
    msgBox.setText(QStringLiteral("删除"));
    msgBox.setInformativeText(QStringLiteral("确定删除吗？"));
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void TableView::onModifyVariable()
{
    QMessageBox msgBox;
    msgBox.setText(QStringLiteral("修改"));
    msgBox.setInformativeText(QStringLiteral("确定修改吗？"));
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}








