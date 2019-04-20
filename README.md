# HeadView

Qt model/view 实现复杂的多行表头，可用于自定义我自己的表头，Table的多行表头在treeView的头中又重新设置了一遍，核心是多行表头实际上是通过ItemDelegate手动绘制。
本例的基本功能是:
 - 自定义了一个表格View(TableView),支持继承重载相关虚函数
 - TabelView支持设置多行横向表头(默认2行)
 - 可以添加多张表格，每个表格是独立的，它们都有属于自己的自定义表头
 - 表头的右键操作

![多行表头](./images/1.png)
![表头菜单事件](./images/2.png)