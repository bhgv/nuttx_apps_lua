############################################################################
# examples/null/Makefile
#
#   Copyright (C) 2007-2008, 2010-2012 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

-include $(TOPDIR)/Make.defs

# The NULL example built-in application info


APPNAME = lua

CONFIG_INTERPRETER_LUA_PRIORITY ?= 100
CONFIG_INTERPRETER_LUA_STACKSIZE = 10240

PRIORITY  = $(CONFIG_INTERPRETER_LUA_PRIORITY)
STACKSIZE = $(CONFIG_INTERPRETER_LUA_STACKSIZE)

#PRIORITY = SCHED_PRIORITY_DEFAULT
#STACKSIZE = 2048

# The smallest thing you can build -- the NULL example.

ASRCS =
CSRCS =  lapi.c      lcode.c     ldebug.c  lgc.c     lmathlib.c  lopcodes.c  lstring.c  ltm.c      lutf8lib.c
CSRCS += lauxlib.c   lcorolib.c  ldo.c     linit.c   lmem.c      lstrlib.c   lvm.c
CSRCS += lbaselib.c  lctype.c    ldump.c   loadlib.c lparser.c   ltable.c    lzio.c
CSRCS += lbitlib.c   ldblib.c    lfunc.c   llex.c    lobject.c   lstate.c    ltablib.c  lundump.c
#CSRCS += loslib.c liolib.c

#CFLAGS += -I../../system -DLUA_USE_POSIX -DLUA_USE_READLINE
CFLAGS += -I../../include -DLUA_USE_READLINE #-DLUA_USE_LINUX
CFLAGS += -std=gnu99
CFLAGS += -O2 -Wall -Wextra -DLUA_COMPAT_5_2
CFLAGS += -DKERNEL -DLUA_USE_CTYPE -DLUA_32BITS -DDEBUG_FREE_MEM=1


MAINSRC = lua_main.c

CONFIG_XYZ_PROGNAME ?= lua$(EXEEXT)
PROGNAME = $(CONFIG_XYZ_PROGNAME)

MODULE = CONFIG_EXAMPLES_LUA

include $(APPDIR)/Application.mk
