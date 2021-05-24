#!/usr/bin/env python3
"""
A setuptools based setup module.
See:
https://github.com/pypa/sampleproject
"""

from setuptools import setup

setup(name='app_api',
      version='0.1.0',
      description='Mission Application API for CubeOS',
      py_modules=["app_api"],
      install_requires=['toml']
      )
