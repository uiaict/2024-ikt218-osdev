#!/usr/bin/env python

from distutils.core import setup

setup(
    name='IKT218 OSDev',
    version='1.0',
    description='The local dev server for IKT218 OSDev',
    author='Per-Arne Andersen',
    author_email='per.andersen@uia.no',
    url='https://ikt218.per-arne.no',
    packages=[],
    install_requires=[
        'requests',
        'flask',
        'jinja2'
    ],
)