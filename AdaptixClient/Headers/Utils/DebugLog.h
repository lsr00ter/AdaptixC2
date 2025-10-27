#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <QString>

// Debug logging utility for sync operations
// Thread-safe, writes to sync_debug.log with timestamps
void debugLog(const QString& function, const QString& message);

#endif // DEBUGLOG_H
