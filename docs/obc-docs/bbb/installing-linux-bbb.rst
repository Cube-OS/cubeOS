Installing CubeOS Linux on a Beaglebone Black
============================================

Overview
--------

This document covers the steps required to install CubeOS Linux onto a Beaglebone Black.

Reference Documents
-------------------

Beaglebone Documentation
~~~~~~~~~~~~~~~~~~~~~~~~

- `Beaglebone Black Web Page <https://beagleboard.org/black>`__
- `Beaglebone Black Wiki <http://elinux.org/Beagleboard:BeagleBoneBlack>`__
- `Beaglebone Black Hardware Diagrams <http://beagleboard.org/Support/bone101/#hardware>`__
- `Beaglebone Black System Reference Manual Rev C <http://static6.arrow.com/aropdfconversion/8fff89aa85f5c451318cbdee2facd9c9fac36872/bbb_srm.pdf>`__

CubeOS Documentation
~~~~~~~~~~~~~~~~~~~

-  :doc:`../../tutorials/first-obc-project` - Basic tutorial for creating your first CubeOS project
-  :doc:`../../ecosystem/linux-docs/using-cubeos-linux` - General guide for interacting with CubeOS Linux
-  :doc:`working-with-the-bbb` - Guide for interacting with BBB-specific features
-  :doc:`../../deep-dive/klb/cubeos-linux-on-bbb` - Steps to build CubeOS Linux

Components
----------

The CubeOS Linux installation process is composed of two high-level steps:

  - Flashing the eMMC
  - Flashing the microSD card

To perform a full default installation, two files are needed:

  - A CubeOS Linux SD card image (cubeos-linux.img)
  - An Auxilliary SD card image (aux-sd.img)

All of these files can be obtained from `our CubeOS Linux Releases page on GitHub <https://github.com/cubeos/cubeos-linux-build/releases>`__

Download the latest `CubeOS-v{version}.tar.gz` file and then unzip the files for the Beaglebone Black. They're located in the `CubeOS-v{version}/Beaglebone-Black` folder.

.. note::

    The Beaglebone Black can also be used as a development board for the Pumpkin MBM2.
    If you would like to use it for this purpose, please follow the
    :doc:`../mbm2/installing-linux-mbm2` instructions instead.

Pre-Requisites
--------------

1. Obtain a microSD card that is at least 4GB.

.. note:: 

    The CubeOS Linux SD images are created for a 4GB SD card. The image can be applied to a larger SD card, but the
    resulting system will still only have 4GB of space available to it.

 
2. Install `Etcher <https://www.balena.io/etcher/>`__. Other software to flash SD cards does exist,
   but Etcher is the CubeOS software of choice.

3. Obtain the SD card images

Install the eMMC Image
----------------------

Flash the SD Card
~~~~~~~~~~~~~~~~~

Using `Etcher <https://www.balena.io/etcher/>`__:

  - Select the CubeOS Linux image to flash
  - Make sure the SD card device is correct (may be auto-detected if there is only one SD card present
    in your system.)
  - Click the "Flash!" button to start the flashing process

.. figure:: ../../images/iOBC/etcher.png
   :alt: Etcher Setup

   Etcher Setup
  
It should take roughly 10 minutes for a 4GB image to be loaded onto an SD card.

Once the program has finished successfully, the SD card is ready to be inserted
into the Beaglebone Black's microSD slot.

Boot into U-Boot
~~~~~~~~~~~~~~~~

.. note:: These instructions should work whether you're currently running CubeOS Linux
    or some other Linux distribution.

We now want to overwrite the eMMC, so we'll need to use U-Boot in order to boot
CubeOS Linux from the microSD card.

You'll need to establish a serial connection with the board in order to connect
to the console.

Hold down any key while the board is booting. This will exit out of the auto-boot and
bring up the CLI.

::

    U-Boot 2016.09 (May 23 2019 - 21:19:32 +0000)

    I2C:   ready
    DRAM:  512 MiB
    MMC:   OMAP SD/MMC: 0, OMAP SD/MMC: 1
    Net:   cpsw, usb_ether
    Hit any key to stop autoboot:  0
    U-Boot>
   
Copy/paste these commands:

::
    
    setenv bootargs console=ttyS0,115200 root=/dev/mmcblk0p2 ext4 rootwait; fatload mmc 0:1 ${fdtaddr} /beaglebone-black.dtb; fatload mmc 0:1 ${loadaddr} /kernel; bootm ${loadaddr} - ${fdtaddr}
    
This will cause the board to load CubeOS Linux off of the microSD card, allowing us to flash
the eMMC.

Alternative Boot
~~~~~~~~~~~~~~~~

When loading CubeOS Linux for the first time, the prior instructions may fail for boards which come
from certain hardware providers.
This failure will be indicated by the following error message::

    Wrong Image Format for bootm command
    
In this case, you will need to boot off of the microSD card by using the Beaglebone's
`boot button <https://cdn-learn.adafruit.com/assets/assets/000/008/680/medium800/beaglebone_BeagleBoneBlack.jpeg>`__.
Power off the board. Hold down the boot button and then apply power to the board.
You may let go of the boot button once you start seeing boot messages from the debug port.

The system will now boot off of the microSD card and into CubeOS Linux.

Flash the eMMC
~~~~~~~~~~~~~~

To flash the eMMC, log into the board using the default `root` user with password `CubeOS123` and then run the
installation script, ``install-os``. It has been placed within the system PATH, so may be called from any location.

A confirmation dialog will be issued. Enter ``y`` to proceed with the installation.

You will see a variety of messages which will vary depending on the current state of the system
(for example, whether you are currently running a version of CubeOS Linux or some other distribution).

It should be safe to ignore any messages which are issued prior to the actual copying of data.

The installation script will produce a few informational messages prefixed with ``OS Install``.

The resulting installation messages should look like this::

    ~ # install-os
    ** Warning ** This script will wipe out the current contents of the eMMC
    Are you sure you want to proceed? (y/N)
    y
    OS Install: Pausing monitoring
    OS Install: Stopping running services
    OS Install: Prepping the file system
    OS Install: Copying SD card contents over to eMMC. This process should take 10-15 minutes to complete

The four status LEDs on the board should start flashing in a random pattern.
This indicates that the eMMC is currently being flashed.

The process should take roughly ten minutes, after which the LEDs should return to normal,
with one LED blinking to indicate a successfully running CubeOS Linux system.

The console should show a summary of the transfer::

    7471104+0 records in
    7471104+0 records out
    3825205248 bytes (3.6GB) copied, 659.546105 seconds, 5.5MB/s

After this process has completed, shutdown and de-power the system.

Install the Auxiliary Image
---------------------------

Re-Flash the SD Card
~~~~~~~~~~~~~~~~~~~~

Now flash the microSD card with the auxiliary SD card image (``aux-sd.img``). This image contains the
CubeOS Linux upgrade partition and the second user data partition.

Once the flash process has completed, put the card back into the microSD slot
and boot up the system.


.. figure:: ../../images/cubeos_bbb_linux_mount_errors.png
   :alt: mount complaints during boot.

You will see messages as the data partitions are mounted. For example::

    EXT4-fs (mmcblk0p2): couldn't mount as ext3 due to feature incompatibilities.

While they may seem like errors, they are a normal part of the boot process as
the system detects the partition file type. If there are *actual* issues
mounting a partition, the resulting error message will look like this::

    mount: can't find PARTUUID=41555820-02

This example message is given when the system is unable to find the axilliary
SD card's second partition. This might be due to no microSD card being present,
or the microSD card not being properly flashed with the auxilliary SD image.

If you see no such errors, the installation process is now complete.

Using CubeOS Linux
-----------------

For information on how to create and run applications on your new CubeOS Linux system, see the
:doc:`../../ecosystem/linux-docs/using-cubeos-linux` and :doc:`working-with-the-bbb` guides.
