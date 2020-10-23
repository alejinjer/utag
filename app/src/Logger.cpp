#include "Logger.h"
#include <QDateTime>
#include "ui_mainwindow.h"

Logger::Logger(Ui::MainWindow *ui) : m_ui(ui)
{
}

void Logger::log_error(const QString &str)
{
    m_logBuffer += QDateTime::currentDateTime().toString("hh:mm:ss dd-MM-yyyy:")
                    + " " + str + "\n";
    m_ui->log->setText(m_logBuffer);
}
