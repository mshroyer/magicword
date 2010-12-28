"Ah ah ah, you didn't say the magic word..."
============================================

Proof that I watched too much Jurassic Park as a child...  (and a chance
for me to brush up on my WinAPI).

by [Mark Shroyer](http://markshroyer.com/)

This is a plain Win32 program written using GDI+.  Will run on Windows XP
or better.


## WTF? ##

[See here](http://www.youtube.com/watch?v=RfiQYRn7fBg) for context.


## Build instructions ##

If you don't already have a Windows C++ development environment set up, the
easiest way to build this program yourself is to download and install
Microsoft Visual C++ 2010 Express Edition:

[http://www.microsoft.com/express/Windows/](http://www.microsoft.com/express/Windows/)

This program does not require any Visual Studio features or APIs (e.g. MFC
or ATL) not available in the free version of Visual C++.

Unfortunately, it might not build with non-Microsoft compilers without
modification: it uses features such as Visual C++'s support for the
`__int64` data type and non-standard additions to the C library -- and
you'll also need headers for the GDI+ "non-flat" library, which I don't
think MinGW supports out of the box.
