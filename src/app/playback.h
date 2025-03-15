#pragma once

#include <QString>

struct Playback {
    QString file;
    QString subtitle;
    QString altSubtitle;
    uint volume;
    qulonglong continueFrom;
};
