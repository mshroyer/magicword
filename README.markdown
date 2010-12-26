"Ah ah ah, you didn't say the magic word..."
============================================

Proof that I watched too much Jurassic Park as a child...

by Mark Shroyer

    Sat Dec 25 19:42:05 EST 2010

This is a plain WinAPI program written using GDI+.  Runs on Windows XP or
newer.

If you don't have a copy of Visual Studio already installed, the easiest
way to build this program yourself is to download and install Microsoft
Visual C++ 2010 Express Edition:

[[http://www.microsoft.com/express/Windows/]]

Building this project does not require any Visual Studio features or APIs
(such as MFC or ATL) not available in the free version of Visual C++.

Unfortunately, this program probably will not build with non-Microsoft
compilers without modification: it uses features such as Visual C++'s
support for the `__int64` data type and non-standard additions to the C
library, and it also requires binary compatibility with the Visual C++
runtime for use of the GDI+ class-based API.
