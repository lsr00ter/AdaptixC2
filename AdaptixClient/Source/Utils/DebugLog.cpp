#include <Utils/DebugLog.h>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

// Single global mutex - defined once with external linkage
static QMutex debugLogMutex;

void debugLog(const QString& function, const QString& message) {
    QMutexLocker locker(&debugLogMutex);
    QFile logFile("sync_debug.log");
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        out << "[" << timestamp << "] [" << function << "] " << message << "\n";
    }
}
