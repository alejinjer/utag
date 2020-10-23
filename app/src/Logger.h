#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Logger
{
public:
    Logger(Ui::MainWindow *ui);

    void log_error(const QString &str);

private:
    Ui::MainWindow *m_ui;
    QString m_logBuffer;
};

#endif // LOGGER_H
