#include "MainWidget.h"

#include <QTableView>
#include <QHBoxLayout>
#include <QApplication>

#include "TableView.h"
#include "TabelModel.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // 表格数据
    QList<QList<QVariant> > data;
    for(int i = 0; i < 10000; ++i)
    {
        QList<QVariant> list;
        for(int j = 0; j < 6; ++j)
        {
            list.append(i*j);
        }
        data.append(list);
    }
    // 表头数据
    QStringList headList;
    headList << QStringLiteral(" ") <<QStringLiteral(" ") << QStringLiteral(" ")
             << QStringLiteral(" ") <<QStringLiteral(" ") << QStringLiteral(" ");

    TableView *pTableView = new TableView(this);
    TabelModel *pTabelModel = new TabelModel();

    pTabelModel->setHeaderList(headList);
    pTabelModel->updateData(data);

    // 为表格内部(不是表头)设置数据的model
    pTableView->setModel(pTabelModel);
    pTableView->initHeaderView();
    pTableView->initAction();

    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->setSpacing(0);
    pLayout->addWidget(pTableView);
    this->setLayout(pLayout);


}

MainWidget::~MainWidget()
{

}
