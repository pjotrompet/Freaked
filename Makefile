#!/usr/bin/make -f
# Makefile for Freak Plugins #
# -------------------------- #
#

CC  ?= gcc
CXX ?= g++

DESTDIR =
PREFIX  = /usr/local

# ---------------------------------------------------------------------------------------------------------------------

FNAME_SUFFIX = _linux_lv2-32bits.cpp

# ---------------------------------------------------------------------------------------------------------------------
# Set build and link flags

BASE_FLAGS = -Wall -Wextra -Wno-unused-parameter -pipe -fPIC -DPIC
LINK_OPTS  = -fdata-sections -ffunction-sections -Wl,--gc-sections -Wl,-O1 -Wl,--as-needed -Wl,--strip-all

ifeq ($(NOOPT),true)
# No optimization flags
BASE_OPTS  = -O2 -ffast-math -fdata-sections -ffunction-sections
else
BASE_OPTS  = -O2 -ffast-math -mfpmath=sse -mtune=generic -msse -msse2 -fdata-sections -ffunction-sections
endif

ifeq ($(DEBUG),true)
BASE_FLAGS += -DDEBUG -O0 -g
LINK_OPTS   =
else
BASE_FLAGS += -DNDEBUG $(BASE_OPTS) -fvisibility=hidden
CXXFLAGS   += -fvisibility-inlines-hidden
endif

BUILD_C_FLAGS   = $(BASE_FLAGS) -std=c99 -std=gnu99 $(CFLAGS)
BUILD_CXX_FLAGS = $(BASE_FLAGS) -std=c++0x -std=gnu++0x $(CXXFLAGS) $(CPPFLAGS)
LINK_FLAGS      = $(LINK_OPTS) -Wl,--no-undefined $(LDFLAGS)

# ---------------------------------------------------------------------------------------------------------------------

plugins = \
LV2/Freakclip.lv2/Freakclip.so \
LV2/Freaktail.lv2/Freaktail.so \
LV2/Prefreak.lv2/Prefreak.so

# ---------------------------------------------------------------------------------------------------------------------

all: $(plugins)

clean:
	rm -f LV2/*.lv2/*.so

install:
	install -d $(DESTDIR)$(PREFIX)/lib/lv2/
	cp -r LV2/*.lv2/ $(DESTDIR)$(PREFIX)/lib/lv2/

export:
	$(CXX) CppSrc/FreakClip$(FNAME_SUFFIX) $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o export && ./export > Freakclip.ttl; rm -f export
	$(CXX) CppSrc/FreakTail$(FNAME_SUFFIX) $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o export && ./export > FreakTail.ttl; rm -f export
	$(CXX) CppSrc/PreFreak$(FNAME_SUFFIX)  $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o export && ./export > PreFreak.ttl ; rm -f export

# ---------------------------------------------------------------------------------------------------------------------

LV2/Freakclip.lv2/Freakclip.so: CppSrc/FreakClip$(FNAME_SUFFIX)
	$(CXX) $< $(BUILD_CXX_FLAGS) -DFAUST_META=0 $(LINK_FLAGS) -shared -o $@

LV2/Freaktail.lv2/Freaktail.so: CppSrc/FreakTail$(FNAME_SUFFIX)
	$(CXX) $< $(BUILD_CXX_FLAGS) -DFAUST_META=0 $(LINK_FLAGS) -shared -o $@

LV2/Prefreak.lv2/Prefreak.so: CppSrc/PreFreak$(FNAME_SUFFIX)
	$(CXX) $< $(BUILD_CXX_FLAGS) -DFAUST_META=0 $(LINK_FLAGS) -shared -o $@

# ---------------------------------------------------------------------------------------------------------------------
