#ifndef QFS_CONFERENCE_H
#define QFS_CONFERENCE_H
#include "qf.h"
#include "enums.h"
#include <QGst/Element>

namespace QFs {
/** Wrapper for FsConference */
class QFS_EXPORT Conference : public QGst::Element
{
    QFS_WRAPPER(Conference)
public:

    QFs::SessionPtr new_session(QFs::MediaType media_type /*, GError? */);
};
};

QFS_REGISTER_TYPE(QFs::Conference) //codegen: GType=FS_TYPE_CONFERENCE
#endif
