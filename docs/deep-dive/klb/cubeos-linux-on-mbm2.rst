Building CubeOS Linux for the Pumpkin MBM2
=========================================

Overview
--------

This supplementary document covers specific features and components of CubeOS Linux for the
Pumpkin Motherboard Module 2.

The :doc:`../../ecosystem/linux-docs/cubeos-linux-overview` doc covers the major components of CubeOS Linux.

Additionally, this document covers the steps required in order to build CubeOS Linux.

Reference Documents
-------------------

Pumpkin Documentation
~~~~~~~~~~~~~~~~~~~~~

The :title:`CubeSat Kit Motherboard Module (MBM) 2` reference document
is available from Pumpkin and is a useful document for learning what
each of the hardware components are and how they are connected.

CubeOS Documentation
~~~~~~~~~~~~~~~~~~~

-  :doc:`../../obc-docs/mbm2/installing-linux-mbm2` - Steps to install CubeOS Linux
-  :doc:`../../ecosystem/linux-docs/using-cubeos-linux` - General guide for interacting with CubeOS Linux
-  :doc:`../../obc-docs/mbm2/working-with-the-mbm2` - Guide for interacting with MBM2-specific features

Software Components
-------------------

ROM Bootloader
~~~~~~~~~~~~~~

The ROM bootloader lives in a small section of ROM space. It should come
pre-loaded on the board and should not need to be modified. It selects the
next bootloader depending on whether the boot mode button is being held.
If not held, it attempts to run the next boot step from eMMC storage;
otherwise, it attempts to boot from the microSD card.

U-Boot
~~~~~~
This board utilizes U-Boot's SPL feature. A small boot file called "MLO" is
run and that file then loads the main U-Boot image into SDRAM.

The main U-Boot image iterates through the `boot_targets` variable to attempt
to boot from an available MMC device. The partuuid of the first successful
device is passed off to Linux to be used to mount the root filesystem.

By default, the microSD card slot will be checked first, followed by the
eMMC. This behavior can be changed by setting the ``boot_dev`` value to
``1`` to indicate that the eMMC should be tried first.

CubeOS Linux Build Process
-------------------------

If for some reason you want or need to modify and rebuild the CubeOS Linux components, follow
the steps in this section.

.. note::

    CubeOS Linux should be built from within an instance of the CubeOS SDK or some other native Linux
    environment.

.. _build-os-mbm2:

Build the OS Files
~~~~~~~~~~~~~~~~~~

.. warning::

    The OS files cannot be built using a `synced folder <https://www.vagrantup.com/docs/synced-folders/>`__ in a Vagrant box (or regular VM).
    VirtualBox does not support hard links in shared folders, which are crucial in order to complete
    the build.

:doc:`SSH into a CubeOS SDK box <../../sdk-docs/sdk-installing>`

In order to build CubeOS Linux, two components are needed:

- The `cubeos-linux-build repo <https://github.com/cubeos/cubeos-linux-build>`__ - Contains the configurations, patches, and extra tools needed to build CubeOS Linux
- `BuildRoot <https://buildroot.org/>`__ - The actual build system

These components should be setup as children of the same parent directory.
There are several commands and variables in the build process which use relative file paths to navigate between the components.

After the environment has been set up, all build commands will be run from the BuildRoot directory unless otherwise stated.

To set up a build environment and build CubeOS Linux:

Create a new parent folder to contain the build environment

::

    $ mkdir cubeos-linux

Enter the new folder

::

    $ cd cubeos-linux

Download BuildRoot-2019.02.2 (more current versions of BuildRoot may work as well,
but all testing has been done against 2019.02.2)

.. note:: All CubeOS documentation will refer to v2019.02.2, which is the latest version of the LTS release at the time of this writing.

::

    $ wget https://buildroot.uclibc.org/downloads/buildroot-2019.02.2.tar.gz && tar xvzf buildroot-2019.02.2.tar.gz && rm buildroot-2019.02.2.tar.gz

Pull the cubeos-linux-build repo

::

    $ git clone http://github.com/cubeos/cubeos-linux-build

Move into the buildroot directory

::

    $ cd buildroot-2019.02.2

Point BuildRoot to the external cubeos-linux-build folder and tell it to build
for the Pumpkin MBM2.

.. note::

    You will need to build with ``sudo`` if you are using the default 
    configuration, since it points the output toolchain to "/usr/bin/bbb_toolchain",
    which is a protected directory.

::

    $ sudo make BR2_EXTERNAL=../cubeos-linux-build pumpkin-mbm2_defconfig

Build everything

::

    $ sudo make

The full build process will take a while. Running on a Linux VM, it takes about
an hour. Running in native Linux, it took about ten minutes. Once this build
process has completed once, you can run other BuildRoot commands to rebuild
only certain sections and it will go much more quickly (<5 min).

BuildRoot documentation can be found
`**here** <https://buildroot.org/docs.html>`__

The generated files will be located in buildroot-2019.02.2/output/images.
The relevant files are:

-  uboot.bin - The U-Boot binary
-  kernel - The compressed Linux kernel file
-  pumpkin-mbm2.dtb - The Device Tree Binary that Linux uses to configure itself
   for the Pumpkin MBM2 board
-  rootfs.tar - The root file system. Contains BusyBox and other libraries
-  cubeos-linux.tar.gz - A compressed file containing the complete CubeOS Linux SD card
   image, ``cubeos-linux.img``. It has a disk signature of 0x4B4C4E58 ("KLNX").
-  aux-sd.tar.gz - A compressed file containing the auxilliary SD card image which
   contains the upgrade partition and the ``kpack-base.itb`` file which is used for
   OS recovery. It has a disk signature of 0x41555820 ("AUX ").

The `cubeos-linux.tar.gz` and `aux-sd.tar.gz` files are the two final files which will be used to
install CubeOS Linux onto your target board.

Changing the Output Toolchain Directory (optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you would like to build your toolchain in somewhere other than the
"/usr/bin/bbb_toolchain" directory, update the ``BR2_HOST_DIR`` variable in the
"configs/pumpkin-mbm2_defconfig" file.

If you would like BuildRoot to just build the toolchain locally, you may remove
the ``BR2_HOST_DIR`` variable entirely. The toolchain will then be built under the
main "buildroot-2019.02.2" directory in a new "output/host" folder.

Using CubeOS Linux
-----------------

For information on how to create and run applications on your new CubeOS Linux system, see the
:doc:`../../obc-docs/mbm2/working-with-the-mbm2` guide.

Configuring CubeOS Linux
-----------------------

For information on how to customize your build of CubeOS Linux, see the
:doc:`configuring-cubeos` guide.

This guide covers things like including custom packages, enabling hardware services, and selecting
a non-default version of the CubeOS source.