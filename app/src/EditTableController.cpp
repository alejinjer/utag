#include "EditTableController.h"

EditTableController::EditTableController(QTableWidget *parent)
    : m_parent(parent)
{
    for (int i = 0; i < TAG_COUNT; ++i) {
        m_currentFileTags[i] = new QTableWidgetItem("");
        m_parent->setItem(i, 0, m_currentFileTags[i]);
    }
}

EditTableController::~EditTableController()
{
}

void EditTableController::setCurrentFile(const QVector<QString> &v)
{
    for (auto i = 0; i < TAG_COUNT; i++) {
        m_currentFileTags[i]->setData(Qt::DisplayRole, v[i + 1]);
    }
}

void EditTableController::unsetCurrentFile()
{
    for (auto i = 0; i < TAG_COUNT; i++) {
        m_currentFileTags[i]->setData(Qt::DisplayRole, "");
    }
}

QVector<QTableWidgetItem *> EditTableController::getCurrentFile()
{
    return m_currentFileTags;
}
