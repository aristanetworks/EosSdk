#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.
from __future__ import print_function
import string
import sys

# Converts a string_like_this from stdin to a stringLikeThis. If the
# --classname flag is provided, we capitalize the first letter:
# StringLikeThis

i = sys.stdin.readline().strip()
if i.endswith('_t'):
   i = i[:-2]
i = string.capwords(i, '_').replace('_', '')
if '--classname' not in sys.argv:
   i = i[0].lower() + i[1:]
print(i, end="")
