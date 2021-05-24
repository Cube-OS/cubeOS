CubeOS Ecosystem
===============

The CubeOS system is designed to take care of every aspect of a satellite’s flight software.

Rather than operating as a single, monolithic entity, CubeOS is comprised of a series of independent,
yet interoperating components.

.. figure:: ../images/architecture_stack.png
    :align: center
    
- Mission applications control and execute the logic necessary to accomplish mission goals
- Services expose hardware and system functionality with a controlled and uniform interface
- CubeOS Linux provides the base operating system and the drivers needed to communicate with connected
  hardware devices

Information about how to develop and tie all of these components together for a particular mission
can be found in the :doc:`mission development <../mission-dev/index>` section.

.. _app-docs:

Mission Applications
--------------------

Applications are user-level programs which can either be run as one-off executions or continuous
processes.

*Mission* applications are anything that governs the behavior of the satellite.
They govern state management, accomplish scripted tasks, monitor on-board behavior, and are
generally the brains of the system.

Each application is typically dedicated to a certain mode or isolated task the satellite is supposed
to accomplish to keep them lightweight and portable.
They can be simple, such as a telemetry beacon app, or complex, such as a payload operations app.

Details about how to get started developing applications can be found in the
:doc:`mission app dev guide <apps/app-guide>`.

If you prefer to learn by doing, check out our :doc:`tutorials <../tutorials/index>` section.

For more information about what applications will need to be developed in order to accomplish all
the required mission logic, check out our :doc:`../mission-dev/mission-needs` doc.

.. toctree::
    :maxdepth: 1

    apps/app-guide
    apps/python-app-api
    apps/rust-app-api

.. _service-docs:

Services
--------

CubeOS services are defined as any persistent process that is used to interact with the satellite.
Services rarely make decisions, but will allow the user to accomplish typical flight software tasks
such as task scheduling, telemetry storage, file management, shell access, and hardware interaction.

All services expose their functionality via HTTP endpoints which accept :doc:`GraphQL <services/graphql>`
requests and return JSON responses.
This behavior allows client programs which wish to communicate with a service to be written in any
language.

There are three distinct kinds of services:

- Core services, as the name implies, provide the core functionality of the system. They are
  OBC-independent and are automatically included in CubeOS. These services include things like
  OBC monitoring, telemetry management, delay-tolerant file transfer and shell access,
  application management, and task scheduling.
- Hardware services expose the functionality of a connected hardware device (ADCS, GPS, radio, etc)
  to the rest of the bus. They should be re-usable between missions. CubeOS comes with support for a
  certain selection of :ref:`pre-built hardware services <supported-hardware>`.
- Payload services are hardware services which have been custom designed for a specific mission's
  payload hardware. They are not intended to be re-used between missions.

.. toctree::
    :maxdepth: 1

    Core Services <services/core-services>
    Hardware Services <services/hardware-services>
    Payload Services <services/payload-services>
    Service Configuration <services/service-config>
    Service Development <services/service-dev>
    services/service-outline-guide
    GraphQL <services/graphql>

.. _linux-docs:

CubeOS Linux
-----------

CubeOS Linux is a custom Linux distribution designed with embedded devices in mind.

It focuses on including only drivers that are useful for space applications (eg.
I2C and SPI, rather than display drivers) and multi-layer system validation and
recovery logic.

Official CubeOS Linux installation files can be found in the
`cubeos-linux-build releases <https://github.com/cubeos/cubeos-linux-build/releases>`__ page.

Guides for installing and interacting with CubeOS Linux on a target OBC can be found in the
:doc:`../obc-docs/index` section.

Information about creating a custom CubeOS Linux build can be found in our :ref:`Under the Hood <custom-klb>`
section.

Tightly coupled with CubeOS Linux is U-Boot, our bootloader of choice.
U-Boot is responsible for loading CubeOS Linux from permanent storage into RAM at boot
time.
It is also responsible for processing operating system :doc:`upgrades <linux-docs/cubeos-linux-upgrade>`
and :doc:`recovery <linux-docs/cubeos-linux-recovery>`, when necessary.

.. toctree::
    :maxdepth: 1

    CubeOS Linux Overview <linux-docs/cubeos-linux-overview>
    Using CubeOS Linux <linux-docs/using-cubeos-linux>
    Logging <linux-docs/logging>
    Process Monitoring <linux-docs/monitoring>
    CubeOS Linux Upgrades <linux-docs/cubeos-linux-upgrade>
    CubeOS Linux Recovery <linux-docs/cubeos-linux-recovery>
