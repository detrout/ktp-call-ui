#include "session.h"

#include <farstream/fs-session.h>

namespace QFs {

SessionPtr Session::create(FsSession *s)
{
    return SessionPtr::wrap(s, false);
}

}
