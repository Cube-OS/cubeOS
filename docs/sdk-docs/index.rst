CubeOS SDK Docs
==============

While the majority of CubeOS development can be done locally on a host machine, we also provide a
standalone SDK which can be used to assist with the development process.

The "CubeOS SDK" is a term used to describe all of the components used
to build CubeOS projects:

-  `Vagrant <https://www.vagrantup.com/>`__ box - The VM that contains the "ready to run" CubeOS development
   environment
-  CubeOS source modules - The underlying libraries on which CubeOS projects
   are built

Internally, we use this SDK in order to build CubeOS releases and to host our CI tests.

Externally, the SDK is most useful for:

- Windows users
- Users who do not want to muddle their host systems with all of the dependencies required to build
  and execute CubeOS projects
- Users who want to build a :ref:`custom CubeOS image <custom-klb>`

.. uml::

    @startuml
    left to right direction

    actor User

    node "CubeOS SDK" as sdk{
        () "init" as init
        folder "cubeos-proj" as proj {
            folder source {
            }
            () "build" as build
            [binary]
        }
        folder "CubeOS Source" as k_source {
        }
    }

    () "transfer" as flash

    node "OBC - CubeOS Linux" {
        cloud "cubeos-proj" as application
        cloud "App1"
        cloud "App2"
    }

    User -> sdk : vagrant ssh
    init -> proj
    k_source -> build
    build <- source
    [binary] <- build
    [binary] -> flash
    flash -> application

    @enduml

This documentation section contains the various guides related to using the CubeOS SDK:

    - :doc:`sdk-installing` - How to install the SDK onto your host machine
    - :doc:`sdk-c` - A guide to using C with the CubeOS SDK
    - :doc:`sdk-rust` - How to develop and run CubeOS projects using Rust
    - :doc:`sdk-python` - How to develop and run CubeOS projects using Python
    - :doc:`sdk-upgrading` - How to upgrade to the latest version of the CubeOS SDK
    - :doc:`sdk-advanced-cross-compiling` - How to cross compile unsupported targets with Rust

.. toctree::
    :hidden:

    sdk-installing
    sdk-rust
    sdk-python
    sdk-c
    Upgrading the CubeOS SDK <sdk-upgrading>
    sdk-advanced-cross-compiling
