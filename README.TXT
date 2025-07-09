This repository contains the current state of my work on reverse engineering the libqgsepaper library provided in the rMPP toolchain.

Right now the rM2 is not supported.
The library exposes the `epframebuffer.so` file which you can include in your project.

You can then use the following functions

- EPFramebuffer::createControlledInstance() - returns an instance of EPFramebuffer.
- EPFramebuffer.getAuxFramebuffer() - returns the QImage* to the auxilary buffer (the one you can write your images to)
- EPFramebuffer.swapBuffers(QRect changedRegion, EPContentType epct, EPScreenMode type, QFlags<EPFramebuffer::UpdateFlag> flags) - swaps the buffers (and updates the screen)

Please link against libepfb.so *first* (see `make.sh`), otherwise this program won't work.

The framebuffer should automatically clean up all its resources, when the app terminates (it uses atexit() hooks).
