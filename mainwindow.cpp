#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AST.h"
#include "gettoken.cpp"

extern int mistake;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->treeWidget = new QTreeWidget;
    QStringList qsl;
    qsl << "类型" << "值";
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels(qsl);
    QHeaderView *head = ui->treeWidget->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitTree(AST *T)
{
    QStringList qsl;
    qsl << "类型" << "值";
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels(qsl);
    QHeaderView *head = ui->treeWidget->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    QTreeWidgetItem *Qroot = new QTreeWidgetItem(ui->treeWidget, QStringList(QString("程序")));
    ui->treeWidget->addTopLevelItem(Qroot);
    AddItem(Qroot, T);
}

void MainWindow::AddItem(QTreeWidgetItem *Qroot, AST *T)
{
    QStringList qsl;
    QString qs;
    QTreeWidgetItem *n;
    switch (T->type)
    {
    case EXTDEFLIST:
        qs = "外部定义序列";
        break;
    case EXTVARDEF:
        qs = "外部变量定义";
        break;
    case EXTVARTYPE:
        qs = "外部变量类型";
        break;
    case EXTVARLIST:
        qs = "外部变量名序列";
        break;
    case EXTVAR:
        qs = "外部变量名";
        break;
    case FUNCDEF:
        qs = "函数定义";
        break;
    case FUNCRETURNTYPE:
        qs = "函数返回值类型";
        break;
    case 8:
        qs = "函数名";
        break;
    case 9:
        qs = "函数形参序列";
        break;
    case 10:
        qs = "函数形参定义";
        break;
    case 11:
        qs = "函数形参类型";
        break;
    case 12:
        qs = "函数形参名";
        break;
    case 13:
        qs = "函数体";
        break;
    case 14:
        qs = "局部变量定义序列";
        break;
    case 15:
        qs = "局部变量定义";
        break;
    case 16:
        qs = "局部变量类型";
        break;
    case 17:
        qs = "局部变量名序列";
        break;
    case 18:
        qs = "局部变量名";
        break;
    case 19:
        qs = "语句序列";
        break;
    case 20:
        qs = "操作数";
        break;
    case 21:
        qs = "运算符";
        break;
    case 22:
        qs = "表达式";
        break;
    case 23:
        qs = "if条件语句";
        break;
    case 24:
        qs = "else语句体";
        break;
    case 25:
        qs = "if语句";
        break;
    case 26:
        qs = "if-else语句";
        break;
    case 27:
        qs = "while语句";
        break;
    case 28:
        qs = "while条件语句";
        break;
    case 29:
        qs = "while语句体";
        break;
    case 30:
        qs = "for语句";
        break;
    case 31:
        qs = "for条件语句";
        break;
    case 32:
        qs = "for语句条件一";
        break;
    case 33:
        qs = "for语句条件二";
        break;
    case 34:
        qs = "for语句条件三";
        break;
    case 35:
        qs = "for语句体";
        break;
    case 36:
        qs = "return语句";
        break;
    case 37:
        qs = "break语句";
        break;
    case 38:
        qs = "do-while语句";
        break;
    case 39:
        qs = "do-while语句体";
        break;
    case 40:
        qs = "do-while循环条件";
        break;
    case 41:
        qs = "continue语句";
        break;
    case 42:
        qs = "函数声明";
        break;
    case 43:
        qs = "数组定义";
        break;
    case 44:
        qs = "数组类型";
        break;
    case 45:
        qs = "数组名";
        break;
    case 46:
        qs = "数组大小";
        break;
    }
    n = new QTreeWidgetItem(Qroot, QStringList(qs));
    Qroot->addChild(n);
    if (T->l != NULL)
    {
        AddItem(n, T->l);
    }
    while (T->r != NULL)
    {
        AddItem(n, T->r);
        T = T->r;
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->treeWidget->clear();
    QString s = ui->lineEdit->text();
    QByteArray ba = s.toLatin1();
    fp = fopen(ba.data(), "r");
    AST *root = program();
    if (root == NULL || mistake == 1)
    {
        printf("代码有误\n");        //非常规语法错误，主要的报错在后续函数中给出
    }
    else
    {
        printf("AST已经写入treeText.txt中，可以查看\n\n");
    }
    InitTree(root);
    fseek(fp, 0, SEEK_SET);
    QFile qf;
    qf.open(fp, QIODevice::ReadWrite, QFileDevice::AutoCloseHandle);
    ui->textEdit->setPlainText(qf.readAll());
    qf.close();
}

void MainWindow::on_lineEdit_returnPressed()
{
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_pushButtonFile_clicked()
{
    //cnt_lines = 1;
    ui->treeWidget->clear();
    QString s = "test.txt";
    QByteArray ba = s.toLatin1();
    fp = fopen(ba.data(), "r");
    //startAST();
    fseek(fp, 0, SEEK_SET);
    QFile qf;
    qf.open(fp, QIODevice::ReadWrite, QFileDevice::AutoCloseHandle);
    ui->textEdit->setPlainText(qf.readAll());
    qf.close();
}
