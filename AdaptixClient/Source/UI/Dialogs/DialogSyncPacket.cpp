#include <UI/Dialogs/DialogSyncPacket.h>
#include <Utils/DebugLog.h>

DialogSyncPacket::DialogSyncPacket()
{
    splashScreen = new CustomSplashScreen();
    splashScreen->setPixmap(QPixmap(":/SyncLogo"));

    logNameLabel = new QLabel("Log synchronization");

    logProgressLabel = new QLabel();
    logProgressLabel->setAlignment(Qt::AlignCenter);

    progressBar = new QProgressBar();

    layout = new QVBoxLayout(splashScreen);
    layout->addWidget(logNameLabel);
    layout->addStretch();
    layout->addWidget(progressBar);
    layout->addWidget(logProgressLabel);
}

DialogSyncPacket::~DialogSyncPacket() = default;

void DialogSyncPacket::init(int count)
{
    receivedLogs = 0;
    totalLogs = count;
    startTime = QDateTime::currentMSecsSinceEpoch();
    
    debugLog("DialogSyncPacket::init", 
        QString("INITIALIZED: totalLogs=%1, startTime=%2")
            .arg(totalLogs).arg(startTime));
    
    QString progress = QString("Received: %1 / %2").arg(receivedLogs).arg(totalLogs);
    logProgressLabel->setText(progress);
    logProgressLabel->setAlignment(Qt::AlignCenter);

    progressBar->setRange(receivedLogs, totalLogs);
    progressBar->setValue(receivedLogs);
}

void DialogSyncPacket::upgrade() const
{
    debugLog("DialogSyncPacket::upgrade", 
        QString("PROGRESS UPDATE: receivedLogs=%1, totalLogs=%2, percentage=%3%")
            .arg(receivedLogs).arg(totalLogs)
            .arg(totalLogs > 0 ? (receivedLogs * 100 / totalLogs) : 0));
    
    QString progress = QString("Received: %1 / %2").arg(receivedLogs).arg(totalLogs);
    logProgressLabel->setText(progress);

    if (totalLogs > 0) {
        progressBar->setValue(receivedLogs);
    }

    if (receivedLogs >= totalLogs) {
        debugLog("DialogSyncPacket::upgrade", "SYNC COMPLETE: Calling finish()");
        finish();
    }
}

void DialogSyncPacket::finish() const
{
    qint64 elapsed = QDateTime::currentMSecsSinceEpoch() - startTime;
    double seconds = elapsed / 1000.0;

    debugLog("DialogSyncPacket::finish", 
        QString("SYNC FINISHED: totalLogs=%1, elapsed=%2ms, seconds=%3s, receivedLogs=%4")
            .arg(totalLogs).arg(elapsed).arg(seconds, 0, 'f', 2).arg(receivedLogs));

    QString completeMsg = QString("Synchronization complete! %1 items in %2s")
        .arg(totalLogs)
        .arg(seconds, 0, 'f', 2);

    logProgressLabel->setText(completeMsg);
    splashScreen->close();
}
