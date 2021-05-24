#!/usr/bin/env python3
"""
A setuptools based setup module for the Pumpkin MCU API.
See:
https://github.com/pypa/sampleproject
"""

from setuptools import setup

setup(name='pumpkin_mcu',
      version='0.1.5',
      description='CubeOS API for communicating with Pumpkin module MCUs',
      py_modules=["mcu_api"],
      install_requires=[
          'i2c'
      ]
      )
