
/** Copyright (C) 2014 Diane Trout <diane@ghic.org>
 *
 */

#ifndef QFS_SESSION_H
#define QFS_SESSION_H
#include "qf.h"

#include <QGlib/Object>

namespace QFs {
/** Wrapper for FsSession */

class QFS_EXPORT Session : public QGlib::Object
{
    QFS_WRAPPER(Session)
public:
    static SessionPtr create(FsSession *);
};

};

QFS_REGISTER_TYPE(QFs::Session)  //codegen: GType=FS_TYPE_SESSION

#endif
