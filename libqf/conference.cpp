#include "conference.h"
#include "session.h"
#include <glib-object.h>

#include <farstream/fs-conference.h>
#include <QDebug>
namespace QFs {
SessionPtr Conference::new_session(MediaType media_type /*, GError? */)
{
    GError *gerr = 0;
    FsConference *conference = object<FsConference>();
    SessionPtr session = SessionPtr::wrap(fs_conference_new_session(conference,
                                                                    static_cast<FsMediaType>(static_cast<int>(media_type)),
                                                                    &gerr));
    if (gerr) {
        qCritical() << "GError with new session" << gerr;
        throw QGlib::Error(gerr);
    }
    return session;
}

}
