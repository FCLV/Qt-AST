#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileDialog>
#include <QFile>
#include "AST.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InitTree(AST *T);
    void AddItem(QTreeWidgetItem *root, AST *T);

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButtonFile_clicked();
    //void on_showWarnings_blockCountChanged(int newBlockCount);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
