#!/usr/bin/env python3
"""
A setuptools based setup module for the cubeos test package.
See:
https://github.com/pypa/sampleproject
"""

from setuptools import setup

setup(name='cubeos_test',
      version='0.1.0',
      description='Manual integration testing library for CubeOS Services',
      py_modules=["cubeos_test"],
      install_requires=["app_api"]
      )
