# -*- mode: mak; indent-tabs-mode: t; tab-width: 8 -*-
#
# OPENSSL configuration
#

HAVE_OPENSSL=	no

# MSVC
ifeq (vs,$(findstring vs,$(TOOLCHAIN)))

##VSCMD_ARG_HOST_ARCH
##VSCMD_ARG_TGT_ARCH
TOOLTARGET?=$(VSCMD_ARG_TGT_ARCH)
TOOLTARGET?=x86

ifeq ("$(OPENSSL)","")
OPENSSL=	../vcpkg_installed/$(TOOLTARGET)-windows
ifeq ("$(wildcard $(OPENSSL)/*)","")
OPENSSL=	../../vcpkg/installed/$(TOOLTARGET)-windows
ifeq ("$(wildcard $(OPENSSL)/*)","")
OPENSSL=
endif
endif
endif

ifneq ("$(OPENSSL)","")
HAVE_OPENSSL=	yes
CINCLUDE+=	-I$(OPENSSL)/include
ifeq ("$(BUILD_TYPE)","debug")
OPENSSL_LIB=	$(OPENSSL)/debug/lib
OPENSSL_BIN=	$(OPENSSL)/debug/bin
else
OPENSSL_LIB=	$(OPENSSL)/lib
OPENSSL_BIN=	$(OPENSSL)/bin
endif

OPENSSL_DLLS=	$(notdir $(wildcard $(OPENSSL_BIN)/libssl*.dll)) $(notdir $(wildcard $(OPENSSL_BIN)/libcrypto*.dll))
OPENSSL_LIBS=	/LIBPATH:$(OPENSSL_LIB) libssl.lib libcrypto.lib
endif

# Mingw32/Mingw64
else ifeq (mingw,$(findstring mingw,$(TOOLCHAIN)))
HAVE_OPENSSL=	yes
OPENSSL_LIBS=	-lssl -lcrypto

endif	#TOOLCHAIN

#
