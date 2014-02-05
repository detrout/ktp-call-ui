#ifndef QFS_ENUMS_H
#define QFS_ENUMS_H

#include "qf.h"
#include <QtCore/QFlags>

namespace QFs {
    enum MediaType {
        //codegen: prefix=FS_
        MediaTypeAudio,
        MediaTypeVideo,
        /*padding*/
        MediaTypeLast = MediaTypeVideo
    };
}
QFS_REGISTER_TYPE(QFs::MediaType);

#endif
