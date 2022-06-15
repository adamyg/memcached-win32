# -*- mode: mak; indent-tabs-mode: t; tab-width: 8 -*-
#
# OPENSSL configuration
#

HAVE_OPENSSL=	no

ifeq (vs,$(findstring vs,$(TOOLCHAIN)))
ifeq ("$(OPENSSL)","")
OPENSSL=	../vcpkg_installed/x86-windows
ifeq ("$(wildcard $(OPENSSL)/*)","")
OPENSSL=	../../vcpkg/installed/x86-windows
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

else ifeq (mingw,$(findstring mingw,$(TOOLCHAIN)))
HAVE_OPENSSL=	yes
OPENSSL_LIBS=	-lssl -lcrypto

endif	#TOOLCHAIN

#
