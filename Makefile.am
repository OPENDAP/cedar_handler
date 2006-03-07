
# Automake file for fits-handler
#
# 5/17/2005 jhrg
#
# $Id: Makefile.am 12972 2006-01-05 15:41:07Z pwest $

AUTOMAKE_OPTIONS = foreign check-news

ACLOCAL_AMFLAGS = -I conf

bin_PROGRAMS = cedar_handler

CEDAR_SRCS:=cedar_read_attributes.cc cedar_read_descriptors.cc \
	cedar_read_tab.cc cedar_read_tab_support.cc cedar_read_info.cc \
	CedarFilter.cc CedarTab.cc CedarFlat.cc cedar_read_flat.cc \
	cedar_read_stream.cc CedarRequestHandler.cc \
	FlatResponseHandler.cc TabResponseHandler.cc \
	StreamResponseHandler.cc ContainerStorageCedar.cc \
	CedarReporter.cc InfoResponseHandler.cc \
	CedarAuthenticate.cc CedarAuthenticateException.cc \
	DODSMySQLChannel.cc DODSMySQLConnect.cc DODSMySQLQuery.cc \
	DODSMySQLResult.cc DODSEncode.cc

CEDAR_HDRS:=CedarFilter.h CedarFlat.h CedarRequestHandler.h \
	CedarResponseNames.h CedarTab.h FlatResponseHandler.h \
	StreamResponseHandler.h TabResponseHandler.h cedar_read_attributes.h \
	cedar_read_descriptors.h cedar_read_flat.h cedar_read_info.h \
	cedar_read_stream.h cedar_read_tab.h cedar_read_tab_support.h \
	ContainerStorageCedar.h CedarReporter.h InfoResponseHandler.h \
	CedarAuthenticate.h CedarAuthenticateException.h \
	DODSMySQLChannel.h DODSMySQLConnect.h DODSMySQLQuery.h \
	DODSMySQLResult.h DODSEncode.h \
	DODSMySQLQueryException.h DODSMySQLConnectException.h \
	cedar_version.h config_cedar.h 

BES_HANDLER_SRC = cedar_handler.cc CedarHandlerApp.cc cedar_module.cc cedar_commands.cc

cedar_handler_SOURCES = $(CEDAR_SRCS) $(BES_HANDLER_SRC) $(CEDAR_HDRS)
cedar_handler_CPPFLAGS = $(BES_CPPFLAGS)
cedar_handler_LDFLAGS = $(BES_LDFLAGS)
cedar_handler_LDADD = $(BES_LDADD)

EXTRA_DIST = COPYRIGHT COPYING

CLEANFILES = *~

###########################################################################

# Build linux RPMs

srpm:
	rpmbuild -ts fits_handler-@PACKAGE_VERSION@.tar.gz

rpm:
	rpmbuild -tb fits_handler-@PACKAGE_VERSION@.tar.gz
