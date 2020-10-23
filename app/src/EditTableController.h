#ifndef EDITTABLECONTROLLER_H
#define EDITTABLECONTROLLER_H

#include <QTableWidgetItem>

#define TAG_COUNT 5

class EditTableController
{
public:
    EditTableController(QTableWidget *parent);
    ~EditTableController();

    void setCurrentFile(const QVector<QString> &v);
    void unsetCurrentFile();
    QVector<QTableWidgetItem *> getCurrentFile();


private:
    QTableWidget *m_parent;
    QVector<QTableWidgetItem *> m_currentFileTags{TAG_COUNT};
    QString m_currentFilePath;
};

#endif // EDITTABLECONTROLLER_H
