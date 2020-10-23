#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QApplication>
#include <QFileDialog>
#include <QKeyEvent>
#include <QTableWidgetItem>

#include "MainTableModel.h"
#include "EditTableController.h"
#include "Logger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString path, QWidget *parent = nullptr);
    ~MainWindow();

    void changeCurrentDir(const QString &dir);

private slots:
    void on_fileBrowser_clicked(const QModelIndex &index);

    void on_mainTable_clicked(const QModelIndex &index);

    void on_saveButton_clicked();

    void keyPressEvent(QKeyEvent* ре);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *m_fileBrowserModel;
    MainTableModel *m_mainTableModel;
    EditTableController *m_editTableController;
    TagEditor *m_tagEditor;
    Logger *m_logger;
};
#endif // MAINWINDOW_H
