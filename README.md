CubeOS

=========

CubeOS is an open-source software stack for satellites forked from the orignal found at https://github.com/kubos/kubos.

The CubeOS system is designed to take care of every aspect of a satellite’s flight
software.

Rather than operating as a single, monolithic entity, CubeOS is comprised of a series
of independent, yet interoperating components.

<p align="center"> 
<img src="docs/images/architecture_stack.png">
</p>

- Mission applications control and execute the logic necessary to accomplish mission goals
- Services expose hardware and system functionality with a controlled and uniform interface
- CubeOS Linux provides the base operating system and the drivers needed to communicate with connected hardware devices

[Company website](https://www.cubeos-doc-websitem)

[Main Documentation Page](https://docs.cubeos-doc-website)

# Getting Started

Here are some docs which we recommend you look at first when getting started with CubeOS:

- [CubeOS Design](https://docs.cubeos-doc-websitem/latest/cubeos-design.html) - A high-level
  overview of what CubeOS is and how it works
- [Getting Started with Local Dev Environment](https://docs.cubeos-doc-websitem/latest/getting-started/index.html) - 
  Docs for getting started with CubeOS using a local dev environment of your choice
- [Getting Started with the CubeOS SDK](https://docs.cubeos-doc-websitem/latest/sdk-docs/index.html) - 
  Docs for setting up an instance of the CubeOS SDK as your development environemnt.
  Highly recommended for Windows users
- [New User Tutorials](https://docs.cubeos-doc-websitem/latest/tutorials/index.html) - Tutorials
  which will walk you through using all of the major components of CubeOS

# Contributing to CubeOS

Want to get your code to space? Become a contributor!

Check out our doc on [contributing to CubeOS](https://docs.cubeos-doc-websitem/latest/contributing/contribution-process.html) 
and come talk to us on [Slack](https://slack.cubeos-doc-website/) to join our community. 

Or, if you're just looking to give some feedback, 
submit an [issue](https://github.com/cubeos/cubeos/issues) with your feature requests or bug reports! 

# Repo Components

These are the important folders in this repo:

- apis - Contains all of our [hardware APIs](https://docs.cubeos-doc-websitem/latest/deep-dive/apis/device-api/index.html)
  as well as our [application APIs](https://docs.cubeos-doc-websitem/latest/os-docs/apps/app-guide.html)
- clients - Contains client programs which can be used locally to communicate with the
  corresponding service on a remote target
- docs - Contains all of the raw doc files used to generate our [documentation](http://docs.cubeos-doc-website)
- examples - Various example CubeOS projects
- hal - A collection of [hardware interface abstractions](https://docs.cubeos-doc-websitem/latest/apis/cubeos-hal/index.html)
- libs - Helper libraries used when building [CubeOS services](https://docs.cubeos-doc-websitem/latest/os-docs/index.html#services)
- services - Contains all of the CubeOS [core services](https://docs.cubeos-doc-websitem/latest/os-docs/services/core-services.html)
  and [hardware services](https://docs.cubeos-doc-websitem/latest/os-docs/services/hardware-services.html)

# Related Repos

- [cubeos-linux-build](https://github.com/cubeos/cubeos-linux-build) - Repo used for
  configuring and building CubeOS images
- [cargo-cubeos](https://github.com/cubeos/cargo-cubeos) - Repo for a Cargo subcommand
  which will assist with cross-compiling Rust projects for CubeOS
- [cubeos-vagrant](https://github.com/cubeos/cubeos-vagrant) - Repo used to build the
  CubeOS SDK
