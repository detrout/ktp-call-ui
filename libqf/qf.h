/*
    Copyright (C) 2014 Diane Trout. <diane@ghic.org>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef QF_H
#define QF_H

/* This module is a wrapper for farstream that
 * uses the QtGLib/QtGStreamer bindings as a base. It could
 * be built standalone and used in other projects in the future.
 */
#include <QGlib/Object>

//for the moment, this is a static lib
#define QFS_EXPORT

#define QFS_WRAPPER_FSCLASS_DECLARATION(Class) \
    typedef struct _Fs##Class Fs##Class;

#define QFS_WRAPPER_REFPOINTER_DECLARATION(Class) \
    namespace QFs { \
        class Class; \
        typedef QGlib::RefPointer<Class> Class##Ptr; \
    }

#define QFS_WRAPPER_DECLARATION(Class) \
    QFS_WRAPPER_FSCLASS_DECLARATION(Class) \
    QFS_WRAPPER_REFPOINTER_DECLARATION(Class)

QFS_WRAPPER_DECLARATION(Candidate)
QFS_WRAPPER_DECLARATION(Codec)
QFS_WRAPPER_DECLARATION(Conference)
QFS_WRAPPER_DECLARATION(Participant)
QFS_WRAPPER_DECLARATION(Session)
QFS_WRAPPER_DECLARATION(Stream)

#define QFS_WRAPPER(Class) \
    QGLIB_WRAPPER_DECLARATION_MACRO(Class, Class, Fs, Class)

#define QFS_REGISTER_TYPE(Class) \
    QGLIB_REGISTER_TYPE_WITH_EXPORT_MACRO(Class, QFS_EXPORT)

namespace QFs {

/** Initializes telepathy-farstream and registers the
 * QTf wrapper types with the QGlib type system */
QFS_EXPORT void init();

} //namespace QTf


#endif // QTF_H
