#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QString path, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fileBrowserModel(new QFileSystemModel)
    , m_mainTableModel(new MainTableModel)
    , m_tagEditor(new TagEditor)
{
    ui->setupUi(this);
    m_logger = new Logger(ui);

    // fileBrowser
    m_fileBrowserModel->setRootPath(QDir::currentPath());
    if (!QDir(path).exists()) {
        m_logger->log_error("\"" + path + "\"" + " directory doesn`t exist");
    }
    ui->fileBrowser->scrollTo(m_fileBrowserModel->index(path));
    m_fileBrowserModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    ui->fileBrowser->setModel(m_fileBrowserModel);
    ui->fileBrowser->scrollTo(m_fileBrowserModel->index(path));
    ui->fileBrowser->selectionModel()->select(m_fileBrowserModel->index(path), QItemSelectionModel::SelectionFlag::Select);
    ui->fileBrowser->setHeaderHidden(true);
    on_fileBrowser_clicked(m_fileBrowserModel->index(path));


    for (int i = 1; i < m_fileBrowserModel->columnCount(); i++) {
        ui->fileBrowser->hideColumn(i);
    }

    // mainTable
    ui->mainTable->setModel(m_mainTableModel);

    ui->titleLabel->setFont(QFont( "Arial", 15, QFont::Bold));

    // editTable
    m_editTableController = new EditTableController(ui->editTable);
    ui->saveButton->hide();
    
    // log
    ui->log->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileBrowser_clicked(const QModelIndex &index)
{
    QString path = m_fileBrowserModel->fileInfo(index).filePath();
    QDir currentDir{path};

    if (!currentDir.isReadable()) {
        m_logger->log_error("\"" + path + "\"" + " directory is not readable");
    }

    if (m_mainTableModel) {
        delete m_mainTableModel;
    }
    m_mainTableModel = new MainTableModel();

    currentDir.setNameFilters(QStringList("*.mp3") << "*.ogg" << "*.wav");
    QFileInfoList fileList = currentDir.entryInfoList();
    m_mainTableModel->setFileList(fileList, m_logger);

    ui->mainTable->setModel(m_mainTableModel);
}

void MainWindow::changeCurrentDir(const QString &dir)
{
    ui->fileBrowser->setRootIndex(m_fileBrowserModel->index(dir));
}

void MainWindow::on_mainTable_clicked(const QModelIndex &index)
{
    auto tagList = m_mainTableModel->getTagsByIndex(index);

    QPixmap map(":/default_cover.png");
    ui->albumImgLabel->setPixmap(map.scaled(ui->albumImgLabel->width(), ui->albumImgLabel->height(), Qt::KeepAspectRatio));

    ui->titleLabel->setText(tagList[0]);

    ui->saveButton->show();

    m_editTableController->setCurrentFile(tagList);
}

void MainWindow::on_saveButton_clicked()
{
    if (ui->saveButton->isVisible()) {
        auto currentFile = m_editTableController->getCurrentFile();
        try {
            m_tagEditor->modifyFileTags(currentFile);
        } catch (std::exception &e) {
            m_logger->log_error("\"" + currentFile.back()->text() + "\" " + e.what());
        }
        on_fileBrowser_clicked(ui->fileBrowser->selectionModel()->selection().indexes().at(0));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *pe)
{
    switch (pe->key()) {
    case Qt::Key_Escape:
        ui->log->hide();
        ui->albumImgLabel->clear();
        ui->mainTable->clearSelection();
        m_editTableController->unsetCurrentFile();
        ui->titleLabel->setText("");
        ui->saveButton->hide();
        break;
    case Qt::Key_S:
        if (pe->modifiers() & Qt::CTRL) {
            on_saveButton_clicked();
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->log->isVisible()) {
        ui->log->hide();
    }
    else {
        ui->log->show();
    }
}
