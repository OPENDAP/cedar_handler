
# Automake file for fits-handler
#
# 5/17/2005 jhrg
#
# $Id: Makefile.am 12972 2006-01-05 15:41:07Z pwest $

AUTOMAKE_OPTIONS = foreign check-news

ACLOCAL_AMFLAGS = -I conf

AM_CPPFLAGS = $(BES_CPPFLAGS)

SUBDIRS = unit-tests bes-testsuite

bin_PROGRAMS = dap_cedar_handler encode checkKinst checkParcod
lib_LTLIBRARIES = libcedar_handler.la

lib_besdir=$(libdir)/bes
lib_bes_LTLIBRARIES = libcedar_module.la

dist_bin_SCRIPTS = bes-cedar-data.sh

CEDAR_SRCS:=cedar_read_attributes.cc cedar_read_descriptors.cc \
	cedar_read_tab.cc cedar_read_tab_support.cc cedar_read_info.cc \
	cedar_read_flat.cc cedar_read_stream.cc CedarRequestHandler.cc \
	CedarFilter.cc CedarTab.cc CedarFlat.cc CedarInfo.cc \
	FlatResponseHandler.cc TabResponseHandler.cc \
	StreamResponseHandler.cc ContainerStorageCedar.cc \
	CedarReporter.cc InfoResponseHandler.cc \
	CedarAuthenticate.cc CedarAuthenticateException.cc \
	CedarDB.cc CedarMySQLDB.cc CedarMySQLConnect.cc \
	CedarReadKinst.cc CedarReadParcods.cc \
	CedarMySQLResult.cc CedarEncode.cc CedarFSDir.cc CedarFSFile.cc


CEDAR_HDRS:=CedarFilter.h CedarFlat.h CedarRequestHandler.h \
	CedarResponseNames.h CedarTab.h CedarInfo.h FlatResponseHandler.h \
	StreamResponseHandler.h TabResponseHandler.h cedar_read_attributes.h \
	cedar_read_descriptors.h cedar_read_flat.h cedar_read_info.h \
	cedar_read_stream.h cedar_read_tab.h cedar_read_tab_support.h \
	ContainerStorageCedar.h CedarReporter.h InfoResponseHandler.h \
	CedarAuthenticate.h CedarAuthenticateException.h \
	CedarDB.h CedarMySQLDB.h CedarMySQLConnect.h CedarDBResult.h \
	CedarMySQLResult.h CedarDBFields.h CedarEncode.h \
	CedarReadKinst.h CedarReadParcods.h \
	config_cedar.h CedarFSDir.h CedarFSFile.h


BES_HANDLER_SRC = cedar_handler.cc CedarHandlerApp.cc cedar_module.cc cedar_commands.cc CedarHandlerApp.h

libcedar_handler_la_SOURCES = $(CEDAR_SRCS) $(CEDAR_HDRS)
libcedar_handler_la_LIBADD = $(BES_DAP_LIBS)

dap_cedar_handler_SOURCES = $(BES_HANDLER_SRC)
dap_cedar_handler_LDADD = libcedar_handler.la -L$(BES_MODULE_DIR) -ldap_module -ldap_cmd_module

libcedar_module_la_SOURCES = $(CEDAR_SRCS) CedarModule.cc $(CEDAR_HDRS) CedarModule.h
libcedar_module_la_LDFLAGS = -avoid-version -module 
libcedar_module_la_LIBADD = $(BES_DAP_LIBS)

encode_SOURCES = encode.cc
encode_LDADD = libcedar_handler.la -lbes_dap

checkKinst_SOURCES = checkKinst.cc
checkKinst_LDADD = libcedar_handler.la

checkParcod_SOURCES = checkParcod.cc
checkParcod_LDADD = libcedar_handler.la

pkgdata_DATA = cedar/cedar_help.html cedar/cedar_help.txt cedar/cedar_login.html

MODOBJS = cedar_module.o cedar_commands.o

all-local: $(MODOBJS)

install-data-local: $(MODOBJS)
	test -z "$(pkglibdir)" || $(mkdir_p) "$(DESTDIR)$(pkglibdir)"
	list='$(MODOBJS)'; for p in $$list; do \
	  if test -f $$p; then \
	    f=$(am__strip_dir) \
	    $(INSTALL) $$p $(DESTDIR)$(pkglibdir)/$$f; \
	  fi; \
	done

uninstall-local:
	@set -x; list='$(MODOBJS)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  rm -f "$(DESTDIR)$(pkglibdir)/$$f"; \
	done

EXTRA_DIST = COPYRIGHT COPYING bes-cedar-data.sh.in cedar/cedar_help.html cedar/cedar_help.txt cedar/cedar_login.html data

CLEANFILES = *~ $(MODOBJS) bes-cedar-data.sh

sample_datadir = $(datadir)/hyrax/data/cedar
sample_data_DATA = data/mfp920504a.cbf

do_subst = sed -e 's,[@]sysconfdir[@],$(sysconfdir),g' \
		   	   -e 's,[@]libdir[@],$(libdir),g' \
		   	   -e 's,[@]pkgdatadir[@],$(pkgdatadir),g' \
		   	   -e 's,[@]datadir[@],$(datadir),g'

bes-cedar-data.sh: bes-cedar-data.sh.in config.status
	$(do_subst) < $(srcdir)/bes-cedar-data.sh.in > bes-cedar-data.sh
	chmod +x bes-cedar-data.sh

# This makes sure that the handler modifies the bes which configure found
# even when distcheck is run.
bes-conf: bes-cedar-data.sh
	(bes_prefix=`bes-config --prefix` ; \
	if test "$$bes_prefix" = "/usr" ; \
	 then \
	    ./bes-cedar-data.sh /etc/bes/bes.conf /usr/lib/bes ;\
	else \
	    ./bes-cedar-data.sh $$bes_prefix/etc/bes/bes.conf $$bes_prefix/lib/bes ; \
	fi)

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
