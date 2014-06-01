QtFarstream
===========

Motivation
----------

I noticed ktp-call-ui has a problem properly connecting to
Jitsi, and some of the error messages I've gotten suggest
that ktp-call-ui & jitsi are having trouble negotiating
a common codec.

I discovered no one had previously attempted to wrap farstream,
so I thought I'd attempt.

As a review the telepathy multimedia stack is roughly:

  +--------------------+
  | UI (KTp or Empathy)|
  +--------------------+
            |
            v
   +-------------------+
   |telepathy-farstream|
   +-------------------+
            |
            v
  +---------+  +---------+
  |farstream|->|Gstreamer|
  +---------+  +---------+

Part of farstream is GStreamer components. However the other
part, provides additional configuration things like -- FsCodec.

Hacking
-------

To build part of the farstream wraper I reused the codegen
component from libqtgstreamer.

The command I was using is as follows:

codegen -I/usr/include/farstream-0.2/farstream/fs-candidate.h \
        -I/usr/include/farstream-0.2/farstream/fs-codec.h \
        -I/usr/include/farstream-0.2/farstream/fs-conference.h \
	-I/usr/include/farstream-0.2/farstream/fs-participant.h \
	-I/usr/include/farstream-0.2/farstream/fs-session.h \
	-I/usr/include/farstream-0.2/farstream/fs-stream.h \
	candidate.h codec.h conference.h participant.h session.h stream.h enums.h > gen.cpp

Todo
----

* Clean up the includes.
* Write more wrapper code.
* Figure out how to access FsCodecGList


