arm
===

Currently toying with writing code to run on a "bare metal" ARM processor.
Hoping to work up to a small operating system. Right now, hello world works.

You'll probably need to install the arm-non-eabi toolchain, and qemu for ARM.
Then you can do:

    # run the code
    make run

    # do debug mode
    make debug
    # (in another terminal)
    make gdb


Resources
---------

The following links do similar things, but with different machines (i.e. not the
"virt" board from qemu), which means different memory layouts, etc:

https://balau82.wordpress.com/2010/02/28/hello-world-for-bare-metal-arm-using-qemu/

https://community.arm.com/processors/b/blog/posts/hello-world-with-bare-metal-and-qemu

This one does similar things, but with ARM 64 bit.

https://github.com/freedomtan/aarch64-bare-metal-qemu

ARM assembly reference card:

http://ozark.hendrix.edu/~burch/cs/230/arm-ref.pdf

Baking Pi

https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/ok05.html

This is an interesting alternative which uses qemu without a "system", just to
run some ARM code. Interesting stuff:

https://doppioandante.github.io/2015/07/10/Simple-ARM-programming-on-linux.html

This course website is a useful reference as well:

http://cs107e.github.io/