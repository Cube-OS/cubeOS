Working with the Pumpkin MBM2
=============================

Overview
--------

This document covers the CubeOS Linux features which are specific to the
Pumpkin MBM2 target.

Please refer to :doc:`../../ecosystem/linux-docs/using-cubeos-linux` for a general guide to using CubeOS Linux.

Reference Documents
-------------------

Pumpkin Documentation
~~~~~~~~~~~~~~~~~~~~~

The :title:`CubeSat Kit Motherboard Module (MBM) 2` reference document
is available from Pumpkin and is a useful document for learning what
each of the hardware components are and how they are connected.

CubeOS Documentation
~~~~~~~~~~~~~~~~~~~

-  :doc:`../../tutorials/first-obc-project` - Basic tutorial for creating your first CubeOS project
-  :doc:`../../ecosystem/linux-docs/using-cubeos-linux` - General guide for interacting with CubeOS Linux
-  :doc:`../../deep-dive/klb/cubeos-linux-on-mbm2` - Steps to build CubeOS Linux for the Pumpkin MBM2
-  :doc:`installing-linux-mbm2` - Steps to install CubeOS Linux

Status LEDs
-----------

There are four LEDs present on the Pumpkin MBM2 which give some indication of what state
the board is in. When there is only one blinking LED, the board is running CubeOS Linux and
the system is currently idle. The LEDs will blink in correspondence with CPU and MMC activity.
If all LEDs are solid, then the system has reached some kind of locked error state.

USB Connection
--------------

The Pumpkin MBM2 should be shipped with a USB Debug Adapter board.

The white connection cable should be plugged into the labeled "UART0"
port on the edge of the board, with the exposed pins facing up.

The USB cable can then be plugged into your computer. Any required
drivers should be automatically installed.

This connection will be passed through to a CubeOS Vagrant image as
`/dev/FTDI` and will be used for the serial console.

.. _peripherals-mbm2:

Peripherals
-----------

The Pumpkin MBM2 has several different ports available for interacting
with peripheral devices. Currently, users should interact with these
devices using the standard Linux functions. A CubeOS HAL will be added
in the future to abstract this process.

ADC
~~~

The Pumpkin MBM2 has seven analog input pins available:

+------+------+
| Name | Pin  |
+======+======+
| AIN0 | H2.8 |
+------+------+
| AIN1 | H2.7 |
+------+------+
| AIN2 | H2.6 |
+------+------+
| AIN3 | H2.5 |
+------+------+
| AIN4 | H2.4 |
+------+------+
| AIN5 | H2.3 |
+------+------+
| AIN6 | H2.2 |
+------+------+

The pins are available through the Linux device ``/sys/bus/iio/devices/iio\:device0/``.

A single raw output value can be read from each of the pins via
``/sys/bus/iio/devices/iio\:device0/in_voltage{n}_raw``, where `{n}` corresponds to the
AIN number of the pin.

Information about setting up continuous data gathering can be found in
`this guide from TI <http://processors.wiki.ti.com/index.php/Linux_Core_ADC_Users_Guide>`__.

To convert the raw ADC value to a voltage, use this equation:

.. math::
    
    V_{in} = \frac{D * (2^n - 1)}{V_{ref}}

Where:

    - :math:`D` = Raw ADC value
    - :math:`n` = Number of ADC resolution bits
    - :math:`V_{ref}` =  Reference voltage

The Pumpkin MBM2 uses 12 resolution bits and a reference voltage of 1.8V, so the
resulting equation is

.. math::

    V_{in} = \frac{D * (4095)}{1.8}
     
Ethernet
~~~~~~~~

The Pumpkin MBM2, via the embedded Beaglebone Black, provides an ethernet
port which can be used for things like inter-system communication.

The ethernet port is configured to have support for static IPv4 addressing and
can be used with SSH via the included `Dropbear <https://en.wikipedia.org/wiki/Dropbear_(software)>`__
package.

CubeOS Linux currently guarantees support for TCP, UDP, and SCTP.
Other protocols might be supported by default, but have not been verified.

Resources
^^^^^^^^^

- :ref:`CubeOS Ethernet Communication Guide <ethernet>`
- `TCP tutorial <http://www.linuxhowtos.org/C_C++/socket.htm>`__
- `UDP tutorial <https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html>`__
- `SCTP tutorial <http://petanode.com/blog/posts/introduction-to-the-sctp-socket-api-in-linux.html>`__
- `Packet Sender <https://packetsender.com/>`__ - A tool to send test packets between an OBC and a host computer

.. note:: By default, Windows Firewall will block many incoming packet types. This may impact testing.

Configuration
^^^^^^^^^^^^^

The static IP address can be updated by editing the `/etc/network/interfaces` file.
By default the address is ``10.0.2.20``.

Examples
^^^^^^^^

A couple example programs using the ethernet port can be found in the `examples` folder of the `cubeos repo <https://github.com/cubeos/cubeos/tree/master/examples>`__:

- `cubeos-linux-tcprx <https://github.com/cubeos/cubeos/tree/master/examples/cubeos-linux-tcprx>`__ - Receive TCP packets and then reply to the sender
- `cubeos-linux-tcptx <https://github.com/cubeos/cubeos/tree/master/examples/cubeos-linux-tcptx>`__ - Send TCP packets to specified IP address and port

GPIO
~~~~

The CSK headers have 6 GPIO pins available for use.
These pins can be dynamically controlled via the `Linux GPIO Sysfs
Interface for Userspace <https://www.kernel.org/doc/Documentation/gpio/sysfs.txt>`__
as long as they have not already been assigned to another peripheral.

+---------+------------------+-----------+
| CSK Pin | Linux GPIO Value | Direction |
+=========+==================+===========+
| H1.6    | 65               | Input     |
+---------+------------------+-----------+
| H2.18   | 61               | Output    |
+---------+------------------+-----------+
| H2.21   | 89               | Output    |
+---------+------------------+-----------+
| H2.22   | 87               | Output    |
+---------+------------------+-----------+
| H2.23   | 86               | Output    |
+---------+------------------+-----------+
| H2.24   | 85               | Output    |
+---------+------------------+-----------+

CLI and Script Interface
^^^^^^^^^^^^^^^^^^^^^^^^

To interact with a pin from the command line or from a script, the user will first need to
generate the pin's device name:

::

    $ echo {pin} > /sys/class/gpio/export

For example, to interact with pin H2.18, which corresponds with GPIO_61, the user will use:

::

    $ echo 61 > /sys/class/gpio/export

Once this command has been issued, the pin will be defined to the system
as '/sys/class/gpio/gpio{pin}'. The user can then set and check the pins
direction and value.

::

    Set pin as output:
    $ echo out > /sys/class/gpio/gpio61/direction

    Set pin's value to 1:
    $ echo 1 > /sys/class/gpio/gpio61/value

    Get pins's value:
    $ cat /sys/class/gpio/gpio61/value

Once finished, the pin can be released:

::

    $ echo {pin} > /sys/class/gpio/unexport

Application Interface
^^^^^^^^^^^^^^^^^^^^^

This functionality can also be used from a user's application with Linux's sysfs
interface.

An example program might look like this:

.. code-block:: c
    
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    int fd;
    int pin = 61;
    int value = 1;
    
    /* Define the pin to the system */
    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, &pin, sizeof(pin)); 
    close(fd);
    
    /* Set the pin's direction */
    fd = open("/sys/class/gpio/gpio45/direction", O_WRONLY);
    write(fd, "out", 3);
    close(fd);
    
    /* Set the pin's value */
    fd = open("/sys/class/gpio/gpio45/value", O_WRONLY);
    write(fd, &value, 1);
    close(fd);
    
    /* Read the value back */
    fd = open("/sys/class/gpio/gpio45/value", O_RDONLY);
    char strValue[3];
    read(fd, strValue, 1);
    value = atoi(strValue);
    close(fd);
    
    /* Release the pin */
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, &pin, sizeof(pin)); 
    close(fd);

I2C
~~~

The Pumpkin MBM2 has one user-accessible I2C bus, ``/dev/i2c-1``
Users can connect a new device to it via pins **H1.43** (SCL) and **H1.41** (SDA)
of the CubeSat Kit Bus connectors.

`I2C Standards
Doc <http://www.nxp.com/documents/user_manual/UM10204.pdf>`__

CubeOS Linux is currently configured to support the I2C standard-mode
speed of 100kHz.

For examples and instructions, see the :doc:`I2C HAL documentation <../../deep-dive/apis/cubeos-hal/i2c-hal/index>`.

.. note:: The I2C bus is available through the CubeOS C HAL as ``K_I2C1``.

RTC
~~~

The Pumpkin MBM2 has a real-time clock (RTC) which is used to maintain system time.

This clock can be queried or set using the ``hwclock`` command.

UART
~~~~

The Pumpkin MBM2 has 5 UART ports available for use in varying capacities:

+-------------------+--------+--------+---------+---------+
| Linux Device      | TX Pin | RX Pin | RTS Pin | CTS Pin |
+===================+========+========+=========+=========+
| /dev/ttyS1        | H1.18  | H1.17  | H1.10   | H1.9    |
+-------------------+--------+--------+---------+---------+
| /dev/ttyS2        | H1.8   | H1.7   |         |         |
+-------------------+--------+--------+---------+---------+
| /dev/ttyS3        | H1.5   |        |         |         |
+-------------------+--------+--------+---------+---------+
| /dev/ttyS4        | H1.16  | H1.15  |         |         |
+-------------------+--------+--------+---------+---------+
| /dev/ttyS5 (SLIP) | H1.20  | H1.19  | H1.12   | H1.11   |
+-------------------+--------+--------+---------+---------+

Users can interact with these ports using Linux's `termios <http://man7.org/linux/man-pages/man3/termios.3.html>`__ interface.

`A tutorial on this interface can be found here <http://tldp.org/HOWTO/Serial-Programming-HOWTO/x115.html>`__

The ``/dev/ttyS5`` device has been preconfigured to be used for SLIP connections.
Please refer to the :ref:`SLIP instructions <slip>` for more information.

User Data Partitions
--------------------

The Pumpkin MBM2 has multiple user data partitions available, one on each storage
device.

eMMC
~~~~

The user partition on the eMMC device is used as the primary user data storage area.
All system-related `/home/` paths will reside here.

/home/system/usr/bin
^^^^^^^^^^^^^^^^^^^^

This directory is included in the system's PATH, so applications placed
here can be called directly from anywhere, without needing to know the
full file path.

/home/system/etc/init.d
^^^^^^^^^^^^^^^^^^^^^^^

All user-application initialization scripts live under this directory.
The naming format is 'S{run-level}{application}'.

microSD
~~~~~~~

/home/microsd
^^^^^^^^^^^^^

This directory points to a partition on the microSD device included with the
base Beaglebone Black board

.. todo::

    SD over SPI - /home/spisd
    (header characters here)
    
    This directory points to a partition on the SD over SPI device included as a
    peripheral device of the Pumpkin MBM2 board.
    
    EEPROM - /home/eeprom
    (header characters here)
    
    This directory points to the available space of the EEPROM storage included with 
    the base Beaglebone Black board. There are 4KB of space available for use.
    
    .. note:: 
    
        While EEPROM storage is more stable and safe than MMC/SD, it also has a much
        more limited number of writes available. This storage should be used carefully.
