#ifndef MAINTABLEVIEW_H
#define MAINTABLEVIEW_H

#include <QAbstractTableModel>
#include <QFileInfo>
#include <QTableWidgetItem>
#include <memory>
#include "TagEditor.h"
#include "Logger.h"

class MainTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MainTableModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void sort(int column, Qt::SortOrder order) override;

public:
    void setFileList(const QFileInfoList &lst, Logger *logger);

    QVector<QString> getTagsByIndex(const QModelIndex &index);

    void updateFile(const QModelIndex &index, const QVector<QString> &file);

private:
    QVector<QString> m_header;
    QVector<QVector<QString>> m_fileList;
    std::shared_ptr<TagEditor> m_tagEditor;
};

#endif // MAINTABLEVIEW_H
