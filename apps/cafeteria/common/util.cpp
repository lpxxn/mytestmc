#include "util.h"

#include <QTime>

namespace McCommon {

QString currentMinute()
{
    QTime currentTime = QTime::currentTime();
    int minute = currentTime.minute();
    return QString("%1").arg(minute, 2, 10, QChar('0'));
}


}
