
# Automake file for fits-handler
#
# 5/17/2005 jhrg
#
# $Id: Makefile.am 12972 2006-01-05 15:41:07Z pwest $

AUTOMAKE_OPTIONS = foreign check-news

ACLOCAL_AMFLAGS = -I conf

bin_PROGRAMS = cedar_handler encode
lib_LTLIBRARIES = libcedar_handler.la

CEDAR_SRCS:=cedar_read_attributes.cc cedar_read_descriptors.cc \
	cedar_read_tab.cc cedar_read_tab_support.cc cedar_read_info.cc \
	cedar_read_flat.cc cedar_read_stream.cc CedarRequestHandler.cc \
	CedarFilter.cc CedarTab.cc CedarFlat.cc CedarInfo.cc \
	FlatResponseHandler.cc TabResponseHandler.cc \
	StreamResponseHandler.cc ContainerStorageCedar.cc \
	CedarReporter.cc InfoResponseHandler.cc \
	CedarAuthenticate.cc CedarAuthenticateException.cc \
	DODSMySQLChannel.cc DODSMySQLConnect.cc DODSMySQLQuery.cc \
	DODSMySQLResult.cc DODSEncode.cc CedarModule.cc

CEDAR_HDRS:=CedarFilter.h CedarFlat.h CedarRequestHandler.h \
	CedarResponseNames.h CedarTab.h CedarInfo.h FlatResponseHandler.h \
	StreamResponseHandler.h TabResponseHandler.h cedar_read_attributes.h \
	cedar_read_descriptors.h cedar_read_flat.h cedar_read_info.h \
	cedar_read_stream.h cedar_read_tab.h cedar_read_tab_support.h \
	ContainerStorageCedar.h CedarReporter.h InfoResponseHandler.h \
	CedarAuthenticate.h CedarAuthenticateException.h \
	DODSMySQLChannel.h DODSMySQLConnect.h DODSMySQLQuery.h \
	DODSMySQLResult.h DODSEncode.h \
	DODSMySQLQueryException.h DODSMySQLConnectException.h \
	cedar_version.h config_cedar.h CedarModule.h

BES_HANDLER_SRC = cedar_handler.cc CedarHandlerApp.cc cedar_module.cc cedar_commands.cc

libcedar_handler_la_SOURCES = $(CEDAR_SRCS) $(CEDAR_HDRS)

cedar_handler_SOURCES = $(BES_HANDLER_SRC)
cedar_handler_CPPFLAGS = $(BES_CPPFLAGS)
cedar_handler_LDFLAGS = $(BES_LDFLAGS) -ldap_module -ldap_cmdmodule
cedar_handler_LDADD = libcedar_handler.la

encode_SOURCES = encode.cc
encode_LDADD = libcedar_handler.la

MODOBJS = cedar_module.o cedar_commands.o

all-local: $(MODOBJS)

CEDAR_INSTALL_FILES=cedar_help.html cedar_help.txt
install-data-local: $(MODOBJS)
	test -z "$(pkglibdir)" || $(mkdir_p) "$(DESTDIR)$(pkglibdir)"
	list='$(MODOBJS)'; for p in $$list; do \
	  if test -f $$p; then \
	    f=$(am__strip_dir) \
	    $(INSTALL) $$p $(DESTDIR)$(pkglibdir)/$$f; \
	  fi; \
	done
	test -z "$(sysconfdir)/bes" || $(mkdir_p) "$(DESTDIR)$(sysconfdir)/bes"
	list='$(CEDAR_INSTALL_FILES)'; for p in $$list; do \
	  if test -f $$p; then \
	    f=$(am__strip_dir) \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(sysconfdir)/bes/$$f; \
	  fi; \
	done

uninstall-local:
	@set -x; list='$(MODOBJS)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  rm -f "$(DESTDIR)$(pkglibdir)/$$f"; \
	done
	@set -x; list='$(CEDAR_INSTALL_FILES)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  rm -f "$(DESTDIR)$(sysconfdir)/bes/$$f"; \
	done

EXTRA_DIST = COPYRIGHT COPYING

CLEANFILES = *~ $(MODOBJS)

###########################################################################

# Build linux RPMs

srpm:
	rpmbuild -ts fits_handler-@PACKAGE_VERSION@.tar.gz

rpm:
	rpmbuild -tb fits_handler-@PACKAGE_VERSION@.tar.gz

info:
	@echo ""
	@echo ""
	@echo "Makefile Information"
	@echo "    CEDAR_CPPFLAGS = $(CEDAR_CPPFLAGS)"
	@echo "    CEDAR_LDFLAGS = $(CEDAR_LDFLAGS)"
	@echo "    CEDAR_LIBS = $(CEDAR_LIBS)"
