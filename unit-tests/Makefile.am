
# Tests

AUTOMAKE_OPTIONS = foreign

# Arrange to build with the backward compatibility mode enabled.
AM_CPPFLAGS = -I$(top_srcdir) -I/opt/local/include $(BES_CPPFLAGS)

# These are not used by automake but are often useful for certain types of
# debugging. 
CXXFLAGS_DEBUG = -g3 -O0 -fno-defer-pop -Wall -W -Wcast-align -Werror
TEST_COV_FLAGS = -ftest-coverage -fprofile-arcs

check_PROGRAMS = $(TESTS)

noinst_HEADERS = test_config.h

# This determines what gets run by 'make check.'
TESTS = dbT authT kinstT parcodsT

noinst_DATA = bes.conf

EXTRA_DIST = bes.conf.in test_config.h.in

DISTCLEANFILES = test_config.h bes.conf

CLEANFILES = *.log *.sum real*

test_config.h: test_config.h.in Makefile
	sed -e "s%[@]srcdir[@]%${srcdir}%" $< > test_config.h

bes.conf: bes.conf.in ../config.status
	sed -e "s%[@]pkgdatadir[@]%${pkgdatadir}%" \
		-e "s%[@]sysconfdir[@]%${sysconfdir}%" \
		-e "s%[@]libdir[@]%${libdir}%" \
		-e "s%[@]datadir[@]%${datadir}%" \
		-e "s%[@]bindir[@]%${bindir}%" $< > bes.conf

############################################################################

dbT_SOURCES = dbT.cc
dbT_LDADD =  ../libcedar_handler.la -lcppunit

authT_SOURCES = authT.cc
authT_LDADD =  ../libcedar_handler.la -lcppunit

kinstT_SOURCES = kinstT.cc
kinstT_LDADD =  ../libcedar_handler.la -lcppunit

parcodsT_SOURCES = parcodsT.cc
parcodsT_LDADD =  ../libcedar_handler.la -lcppunit

