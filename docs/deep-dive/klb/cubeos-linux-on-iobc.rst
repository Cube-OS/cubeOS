Building CubeOS Linux for the ISIS-OBC
=====================================

Overview
--------

This supplementary document covers specific features and components of CubeOS Linux for the ISIS-OBC.

The :doc:`../../ecosystem/linux-docs/cubeos-linux-overview` doc covers the major components of CubeOS Linux.

Additionally, this document covers the steps required in order to build CubeOS Linux.

Reference Documents
-------------------

iOBC Documentation
~~~~~~~~~~~~~~~~~~

The :title:`ISIS-OBC Quickstart Guide` should have been packaged with the iOBC
and is a useful document for learning what each of the hardware
components are, how to connect them, and what drivers need to be
installed to support them.

CubeOS Documentation
~~~~~~~~~~~~~~~~~~~

-  :doc:`../../obc-docs/iobc/installing-linux-iobc` - Steps to install CubeOS Linux on an iOBC
-  :doc:`../../ecosystem/linux-docs/using-cubeos-linux` - General guide for interacting with CubeOS Linux
-  :doc:`../../obc-docs/iobc/working-with-the-iobc` - Guide for interacting with iOBC-specific features

Software Components
-------------------

ISIS Bootloader
~~~~~~~~~~~~~~~

The ISIS bootloader lives in the very beginning of the NOR flash. It should come
pre-loaded on the board and should not need to be modified. It initializes the
memory hardware and then copies U-Boot into the SDRAM and starts its execution.

If for some reason this bootloader needs to be reloaded, the relevant
instructions can be found in section 8.1 of the *ISIS-OBC Quickstart Guide*.

SAM-BA
~~~~~~

`Product Page <https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/Atmel%20SAM-BA%20In-system%20Programmer>`__

The software tool used to program the iOBC's NOR flash storage area.

.. note:: 

    The ISIS-OBC SDK includes the SAM-BA application. You should install this version,
    rather than the default Atmel version, since it is packaged with several iOBC configuration
    files which are required to successfully connect to the board.

CubeOS Linux Build Process
-------------------------

If for some reason you want or need to modify and rebuild the CubeOS Linux components, follow
the steps in this section.

.. note::

    CubeOS Linux should be built from within an instance of the CubeOS SDK or some other native Linux
    environment.

.. _build-os:

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
the iOBC.

.. note::

    You will need to build with ``sudo`` if you are using the default iOBC
    configuration, since it points the output toolchain to "/usr/bin/iobc_toolchain",
    which is a protected directory.

::

    $ sudo make BR2_EXTERNAL=../cubeos-linux-build at91sam9g20isis_defconfig

Build everything

::

    $ sudo make

The full build process will take a while. Running on a Linux VM, it took about
an hour. Running in native Linux, it took about ten minutes. Once this build
process has completed once, you can run other BuildRoot commands to rebuild
only certain sections and it will go much more quickly (<5 min).

BuildRoot documentation can be found
`**here** <https://buildroot.org/docs.html>`__

The generated files will be located in buildroot-2019.02.2/output/images.
The relevant files are:

-  uboot.bin - The U-Boot binary
-  at91sam9g20isis.dtb - The Device Tree Binary that Linux uses to configure itself
   for the iOBC
-  cubeos-linux.tar.gz - A compressed file containing the complete CubeOS Linux SD card
   image

Changing the Output Toolchain Directory (optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you would like to build your toolchain in somewhere other than the
"/usr/bin/iobc_toolchain" directory, update the ``BR2_HOST_DIR`` variable in the
"configs/at91sam9g20isis_defconfig" file.

If you would like BuildRoot to just build the toolchain locally, you may remove
the ``BR2_HOST_DIR`` variable entirely. The toolchain will then be built under the
main "buildroot-2019.02.2" directory in a new "output/host" folder.

Using CubeOS Linux
-----------------

For information on how to create and run applications on your new CubeOS Linux system, see the
:doc:`../../obc-docs/iobc/working-with-the-iobc` guide.

Configuring CubeOS Linux
-----------------------

For information on how to customize your build of CubeOS Linux, see the
:doc:`configuring-cubeos` guide.

This guide covers things like including custom packages, enabling hardware services, and selecting
a non-default version of the CubeOS source.