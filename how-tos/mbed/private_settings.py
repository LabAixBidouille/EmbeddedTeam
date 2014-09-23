"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
from os.path import join, abspath, dirname
import logging

ROOT = abspath(join(dirname(__file__), ".."))

# These default settings have two purposes:
#    1) Give a template for writing local "private_settings.py"
#    2) Give default initialization fields for the "toolchains.py" constructors

##############################################################################
# Build System Settings
##############################################################################
BUILD_DIR = abspath(join(ROOT, "build"))

BUILD_OPTIONS = []

# mbed.org username
MBED_ORG_USER = ""


