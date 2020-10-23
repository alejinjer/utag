#include "MainTableModel.h"

MainTableModel::MainTableModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_header{"Name", "Title", "Artist", "Album", "Genre", "Path"}
    , m_tagEditor(std::make_shared<TagEditor>())
{
}

QVariant MainTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

    if (orientation == Qt::Horizontal) {
        try {
            return m_header.at(section);
        }
        catch (std::out_of_range &) {
        }
    }
    return QVariant();
}

int MainTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_fileList.size();
}

int MainTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_header.size();
}

void MainTableModel::setFileList(const QFileInfoList &lst, Logger *logger)
{
    for (auto i = 0; i < lst.size(); i++) {
        QVector<QString> file;
        try {
            file = m_tagEditor->getTagsVector(lst[i].filePath());
        } catch (std::exception &e) {
            file.fill("", TAG_COUNT);
            logger->log_error("\"" + lst[i].fileName() + "\" " + e.what());
        }
        file.push_front(lst[i].fileName());
        file.push_back(lst[i].filePath());
        m_fileList.push_back(file);
    }
}

QVector<QString> MainTableModel::getTagsByIndex(const QModelIndex &index)
{
    return m_fileList[index.row()];
}

void MainTableModel::updateFile(const QModelIndex &index, const QVector<QString> &file)
{
    m_fileList[index.row()] = file;
}

QVariant MainTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (!m_fileList.empty()) {
            if (!m_fileList[index.row()][index.column()].isEmpty()) {
                return m_fileList[index.row()][index.column()];
            }
        }
    }
    return QString();
}

void MainTableModel::sort(int column, Qt::SortOrder order)
{
    beginResetModel();
    std::sort(m_fileList.begin(), m_fileList.end(), [=](const auto& a, const auto& b) {
        return order == Qt::AscendingOrder ? a[column] < b[column] : a[column] > b[column];
    });
    endResetModel();
}
