# Makefile.in generated automatically by automake 1.5 from Makefile.am.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



#AUTOMAKE_OPTIONS = ../util/ansi2knr no-dependencies

SHELL = /bin/sh

srcdir = .
top_srcdir = ..

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include
pkgdatadir = $(datadir)/ntp
pkglibdir = $(libdir)/ntp
pkgincludedir = $(includedir)/ntp
top_builddir = ..

ACLOCAL = ${SHELL} /home/gerg/new-wave.dist/user/ntp/missing --run aclocal
AUTOCONF = ${SHELL} /home/gerg/new-wave.dist/user/ntp/missing --run autoconf
AUTOMAKE = ${SHELL} /home/gerg/new-wave.dist/user/ntp/missing --run automake
AUTOHEADER = ${SHELL} /home/gerg/new-wave.dist/user/ntp/missing --run autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_alias = 
build_triplet = i686-pc-linux-gnu
host_alias = 
host_triplet = i686-pc-linux-gnu
target_alias = 
target_triplet = i686-pc-linux-gnu
AMTAR = ${SHELL} /home/gerg/new-wave.dist/user/ntp/missing --run tar
AUTOKEY = 
AWK = mawk
#CC = gcc
CFLAGS +=  -Wall -Wcast-qual -Wmissing-prototypes -Wpointer-arith -Wshadow -Wstrict-prototypes -pipe
CHUTEST = 
CLKTEST = 
CPP = $(CC) -E
DCFD = 
DEPDIR = .deps
EF_LIBS = 
EF_PROGS = 
EXEEXT = 
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
#LDFLAGS = 
LIBPARSE = 
LIBRSAREF = 
LN_S = ln -s
MAKE_ADJTIMED = 
MAKE_CHECK_Y2K = 
MAKE_LIBPARSE = 
MAKE_LIBPARSE_KERNEL = 
MAKE_LIBRSAREF = 
MAKE_NTPTIME = ntptime
MAKE_NTP_GENKEYS = 
MAKE_PARSEKMODULE = 
MAKE_TICKADJ = tickadj
MAKE_TIMETRIM = 
OBJEXT = o
OPENSSL = 
OPENSSL_INC = 
OPENSSL_LIB = 
PACKAGE = ntp
PATH_PERL = /usr/bin/perl
PATH_SH = /bin/sh
PROPDELAY = 
RANLIB = ranlib
RSADIR = 
RSAOBJS = 
RSAREF = 
RSASRCS = 
TESTDCF = 
U = 
VERSION = 4.1.1
am__include = include
am__quote = 
install_sh = /home/gerg/new-wave.dist/user/ntp/install-sh

AUTOMAKE_OPTIONS = ../util/ansi2knr
bin_PROGRAMS = ntpd
INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/librsaref
# LDADD might need RESLIB and ADJLIB
LDADD = version.o  ../libntp/libntp.a 
# ntpd may need:
# log10                               refclock_wwv.o
# sqrt                                ntp_control.o
# floor                               refclock_wwv.o
# which are (usually) provided by -lm.
ntpd_LDADD = $(LDADD) -lm
DISTCLEANFILES = .version version.c
#EXTRA_DIST = ntpd.mak
ETAGS_ARGS = Makefile.am
###							Y2Kfixes
check_PROGRAMS = 
EXTRA_PROGRAMS = check_y2k

# ntp_resolver.c is presently unused...
ntpd_SOURCES = cmd_args.c jupiter.h map_vme.c ntp_config.c ntp_control.c \
	ntp_crypto.c ntp_filegen.c \
	ntp_intres.c ntp_io.c ntp_loopfilter.c ntp_monitor.c ntp_peer.c \
	ntp_proto.c ntp_refclock.c ntp_request.c \
	ntp_restrict.c ntp_timer.c \
	ntp_util.c ntpd.c refclock_acts.c refclock_arbiter.c refclock_arc.c \
	refclock_as2201.c refclock_atom.c refclock_bancomm.c \
	refclock_chronolog.c refclock_chu.c refclock_conf.c refclock_datum.c \
	refclock_dumbclock.c refclock_fg.c refclock_gpsvme.c refclock_heath.c \
	refclock_hopfser.c refclock_hopfpci.c \
	refclock_hpgps.c refclock_irig.c refclock_jjy.c refclock_jupiter.c refclock_leitch.c \
	refclock_local.c refclock_msfees.c refclock_mx4200.c refclock_nmea.c \
	refclock_oncore.c refclock_palisade.c refclock_palisade.h \
	refclock_parse.c refclock_pcf.c refclock_pst.c refclock_ptbacts.c \
	refclock_shm.c refclock_tpro.c refclock_trak.c refclock_true.c \
	refclock_ulink.c refclock_usno.c refclock_wwv.c refclock_wwvb.c

subdir = ntpd
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
EXTRA_PROGRAMS = check_y2k$(EXEEXT)
bin_PROGRAMS = ntpd$(EXEEXT)
check_PROGRAMS = 
PROGRAMS = $(bin_PROGRAMS)

check_y2k_SOURCES = check_y2k.c
check_y2k_OBJECTS = check_y2k$U.$(OBJEXT)
check_y2k_LDADD = $(LDADD)
check_y2k_DEPENDENCIES = version.o ../libntp/libntp.a
check_y2k_LDFLAGS =
am_ntpd_OBJECTS = cmd_args$U.$(OBJEXT) map_vme$U.$(OBJEXT) \
	ntp_config$U.$(OBJEXT) ntp_control$U.$(OBJEXT) \
	ntp_crypto$U.$(OBJEXT) ntp_filegen$U.$(OBJEXT) \
	ntp_intres$U.$(OBJEXT) ntp_io$U.$(OBJEXT) \
	ntp_loopfilter$U.$(OBJEXT) ntp_monitor$U.$(OBJEXT) \
	ntp_peer$U.$(OBJEXT) ntp_proto$U.$(OBJEXT) \
	ntp_refclock$U.$(OBJEXT) ntp_request$U.$(OBJEXT) \
	ntp_restrict$U.$(OBJEXT) ntp_timer$U.$(OBJEXT) \
	ntp_util$U.$(OBJEXT) ntpd$U.$(OBJEXT) refclock_acts$U.$(OBJEXT) \
	refclock_arbiter$U.$(OBJEXT) refclock_arc$U.$(OBJEXT) \
	refclock_as2201$U.$(OBJEXT) refclock_atom$U.$(OBJEXT) \
	refclock_bancomm$U.$(OBJEXT) refclock_chronolog$U.$(OBJEXT) \
	refclock_chu$U.$(OBJEXT) refclock_conf$U.$(OBJEXT) \
	refclock_datum$U.$(OBJEXT) refclock_dumbclock$U.$(OBJEXT) \
	refclock_fg$U.$(OBJEXT) refclock_gpsvme$U.$(OBJEXT) \
	refclock_heath$U.$(OBJEXT) refclock_hopfser$U.$(OBJEXT) \
	refclock_hopfpci$U.$(OBJEXT) refclock_hpgps$U.$(OBJEXT) \
	refclock_irig$U.$(OBJEXT) refclock_jjy$U.$(OBJEXT) \
	refclock_jupiter$U.$(OBJEXT) refclock_leitch$U.$(OBJEXT) \
	refclock_local$U.$(OBJEXT) refclock_msfees$U.$(OBJEXT) \
	refclock_mx4200$U.$(OBJEXT) refclock_nmea$U.$(OBJEXT) \
	refclock_oncore$U.$(OBJEXT) refclock_palisade$U.$(OBJEXT) \
	refclock_parse$U.$(OBJEXT) refclock_pcf$U.$(OBJEXT) \
	refclock_pst$U.$(OBJEXT) refclock_ptbacts$U.$(OBJEXT) \
	refclock_shm$U.$(OBJEXT) refclock_tpro$U.$(OBJEXT) \
	refclock_trak$U.$(OBJEXT) refclock_true$U.$(OBJEXT) \
	refclock_ulink$U.$(OBJEXT) refclock_usno$U.$(OBJEXT) \
	refclock_wwv$U.$(OBJEXT) refclock_wwvb$U.$(OBJEXT)
ntpd_OBJECTS = $(am_ntpd_OBJECTS)
ntpd_DEPENDENCIES = version.o ../libntp/libntp.a
ntpd_LDFLAGS =

DEFS = -DHAVE_CONFIG_H
DEFAULT_INCLUDES =  -I. -I$(srcdir) -I$(top_builddir)
CPPFLAGS = 
#LDFLAGS = 
LIBS = 
depcomp = $(SHELL) $(top_srcdir)/depcomp
DEP_FILES = $(DEPDIR)/check_y2k$U.Po $(DEPDIR)/cmd_args$U.Po \
	$(DEPDIR)/map_vme$U.Po $(DEPDIR)/ntp_config$U.Po \
	$(DEPDIR)/ntp_control$U.Po \
	$(DEPDIR)/ntp_crypto$U.Po \
	$(DEPDIR)/ntp_filegen$U.Po \
	$(DEPDIR)/ntp_intres$U.Po $(DEPDIR)/ntp_io$U.Po \
	$(DEPDIR)/ntp_loopfilter$U.Po \
	$(DEPDIR)/ntp_monitor$U.Po $(DEPDIR)/ntp_peer$U.Po \
	$(DEPDIR)/ntp_proto$U.Po \
	$(DEPDIR)/ntp_refclock$U.Po \
	$(DEPDIR)/ntp_request$U.Po \
	$(DEPDIR)/ntp_restrict$U.Po \
	$(DEPDIR)/ntp_timer$U.Po $(DEPDIR)/ntp_util$U.Po \
	$(DEPDIR)/ntpd$U.Po $(DEPDIR)/refclock_acts$U.Po \
	$(DEPDIR)/refclock_arbiter$U.Po \
	$(DEPDIR)/refclock_arc$U.Po \
	$(DEPDIR)/refclock_as2201$U.Po \
	$(DEPDIR)/refclock_atom$U.Po \
	$(DEPDIR)/refclock_bancomm$U.Po \
	$(DEPDIR)/refclock_chronolog$U.Po \
	$(DEPDIR)/refclock_chu$U.Po \
	$(DEPDIR)/refclock_conf$U.Po \
	$(DEPDIR)/refclock_datum$U.Po \
	$(DEPDIR)/refclock_dumbclock$U.Po \
	$(DEPDIR)/refclock_fg$U.Po \
	$(DEPDIR)/refclock_gpsvme$U.Po \
	$(DEPDIR)/refclock_heath$U.Po \
	$(DEPDIR)/refclock_hopfpci$U.Po \
	$(DEPDIR)/refclock_hopfser$U.Po \
	$(DEPDIR)/refclock_hpgps$U.Po \
	$(DEPDIR)/refclock_irig$U.Po \
	$(DEPDIR)/refclock_jjy$U.Po \
	$(DEPDIR)/refclock_jupiter$U.Po \
	$(DEPDIR)/refclock_leitch$U.Po \
	$(DEPDIR)/refclock_local$U.Po \
	$(DEPDIR)/refclock_msfees$U.Po \
	$(DEPDIR)/refclock_mx4200$U.Po \
	$(DEPDIR)/refclock_nmea$U.Po \
	$(DEPDIR)/refclock_oncore$U.Po \
	$(DEPDIR)/refclock_palisade$U.Po \
	$(DEPDIR)/refclock_parse$U.Po \
	$(DEPDIR)/refclock_pcf$U.Po \
	$(DEPDIR)/refclock_pst$U.Po \
	$(DEPDIR)/refclock_ptbacts$U.Po \
	$(DEPDIR)/refclock_shm$U.Po \
	$(DEPDIR)/refclock_tpro$U.Po \
	$(DEPDIR)/refclock_trak$U.Po \
	$(DEPDIR)/refclock_true$U.Po \
	$(DEPDIR)/refclock_ulink$U.Po \
	$(DEPDIR)/refclock_usno$U.Po \
	$(DEPDIR)/refclock_wwv$U.Po \
	$(DEPDIR)/refclock_wwvb$U.Po
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
LIBS += $(LDLIBS$(LDLIBS_$@))
DIST_SOURCES = check_y2k.c $(ntpd_SOURCES)
DIST_COMMON = Makefile.am Makefile.in
SOURCES = check_y2k.c $(ntpd_SOURCES)

all: all-am

.SUFFIXES:
.SUFFIXES: .c .o .obj
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.in $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  ntpd/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  p1=`echo $$p|sed 's/$(EXEEXT)$$//'`; \
	  if test -f $$p \
	  ; then \
	    f=`echo $$p1|sed '$(transform);s/$$/$(EXEEXT)/'`; \
	   echo " $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/$$f"; \
	   $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/$$f; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  f=`echo $$p|sed 's/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/'`; \
	  echo " rm -f $(DESTDIR)$(bindir)/$$f"; \
	  rm -f $(DESTDIR)$(bindir)/$$f; \
	done

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

clean-checkPROGRAMS:
	-test -z "$(check_PROGRAMS)" || rm -f $(check_PROGRAMS)
check_y2k$(EXEEXT): $(check_y2k_OBJECTS) $(check_y2k_DEPENDENCIES) 
	@rm -f check_y2k$(EXEEXT)
	$(LINK) $(check_y2k_LDFLAGS) $(check_y2k_OBJECTS) $(check_y2k_LDADD) $(LIBS)
ntpd$(EXEEXT): $(ntpd_OBJECTS) $(ntpd_DEPENDENCIES) 
	@rm -f ntpd$(EXEEXT)
	$(LINK) $(ntpd_LDFLAGS) $(ntpd_OBJECTS) $(ntpd_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

ANSI2KNR = ../util/ansi2knr
../util/ansi2knr:
	cd ../util && $(MAKE) $(AM_MAKEFLAGS) ansi2knr

mostlyclean-kr:
	-rm -f *_.c

include $(DEPDIR)/check_y2k$U.Po
include $(DEPDIR)/cmd_args$U.Po
include $(DEPDIR)/map_vme$U.Po
include $(DEPDIR)/ntp_config$U.Po
include $(DEPDIR)/ntp_control$U.Po
include $(DEPDIR)/ntp_crypto$U.Po
include $(DEPDIR)/ntp_filegen$U.Po
include $(DEPDIR)/ntp_intres$U.Po
include $(DEPDIR)/ntp_io$U.Po
include $(DEPDIR)/ntp_loopfilter$U.Po
include $(DEPDIR)/ntp_monitor$U.Po
include $(DEPDIR)/ntp_peer$U.Po
include $(DEPDIR)/ntp_proto$U.Po
include $(DEPDIR)/ntp_refclock$U.Po
include $(DEPDIR)/ntp_request$U.Po
include $(DEPDIR)/ntp_restrict$U.Po
include $(DEPDIR)/ntp_timer$U.Po
include $(DEPDIR)/ntp_util$U.Po
include $(DEPDIR)/ntpd$U.Po
include $(DEPDIR)/refclock_acts$U.Po
include $(DEPDIR)/refclock_arbiter$U.Po
include $(DEPDIR)/refclock_arc$U.Po
include $(DEPDIR)/refclock_as2201$U.Po
include $(DEPDIR)/refclock_atom$U.Po
include $(DEPDIR)/refclock_bancomm$U.Po
include $(DEPDIR)/refclock_chronolog$U.Po
include $(DEPDIR)/refclock_chu$U.Po
include $(DEPDIR)/refclock_conf$U.Po
include $(DEPDIR)/refclock_datum$U.Po
include $(DEPDIR)/refclock_dumbclock$U.Po
include $(DEPDIR)/refclock_fg$U.Po
include $(DEPDIR)/refclock_gpsvme$U.Po
include $(DEPDIR)/refclock_heath$U.Po
include $(DEPDIR)/refclock_hopfpci$U.Po
include $(DEPDIR)/refclock_hopfser$U.Po
include $(DEPDIR)/refclock_hpgps$U.Po
include $(DEPDIR)/refclock_irig$U.Po
include $(DEPDIR)/refclock_jjy$U.Po
include $(DEPDIR)/refclock_jupiter$U.Po
include $(DEPDIR)/refclock_leitch$U.Po
include $(DEPDIR)/refclock_local$U.Po
include $(DEPDIR)/refclock_msfees$U.Po
include $(DEPDIR)/refclock_mx4200$U.Po
include $(DEPDIR)/refclock_nmea$U.Po
include $(DEPDIR)/refclock_oncore$U.Po
include $(DEPDIR)/refclock_palisade$U.Po
include $(DEPDIR)/refclock_parse$U.Po
include $(DEPDIR)/refclock_pcf$U.Po
include $(DEPDIR)/refclock_pst$U.Po
include $(DEPDIR)/refclock_ptbacts$U.Po
include $(DEPDIR)/refclock_shm$U.Po
include $(DEPDIR)/refclock_tpro$U.Po
include $(DEPDIR)/refclock_trak$U.Po
include $(DEPDIR)/refclock_true$U.Po
include $(DEPDIR)/refclock_ulink$U.Po
include $(DEPDIR)/refclock_usno$U.Po
include $(DEPDIR)/refclock_wwv$U.Po
include $(DEPDIR)/refclock_wwvb$U.Po

distclean-depend:
	-rm -rf $(DEPDIR)

.c.o:
	source='$<' object='$@' libtool=no \
	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
	$(CCDEPMODE) $(depcomp) \
	$(COMPILE) -c `test -f $< || echo '$(srcdir)/'`$<

.c.obj:
	source='$<' object='$@' libtool=no \
	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
	$(CCDEPMODE) $(depcomp) \
	$(COMPILE) -c `cygpath -w $<`
CCDEPMODE = depmode=gcc
check_y2k_.c: check_y2k.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/check_y2k.c; then echo $(srcdir)/check_y2k.c; else echo check_y2k.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > check_y2k_.c || rm -f check_y2k_.c
cmd_args_.c: cmd_args.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/cmd_args.c; then echo $(srcdir)/cmd_args.c; else echo cmd_args.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > cmd_args_.c || rm -f cmd_args_.c
map_vme_.c: map_vme.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/map_vme.c; then echo $(srcdir)/map_vme.c; else echo map_vme.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > map_vme_.c || rm -f map_vme_.c
ntp_config_.c: ntp_config.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_config.c; then echo $(srcdir)/ntp_config.c; else echo ntp_config.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_config_.c || rm -f ntp_config_.c
ntp_control_.c: ntp_control.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_control.c; then echo $(srcdir)/ntp_control.c; else echo ntp_control.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_control_.c || rm -f ntp_control_.c
ntp_crypto_.c: ntp_crypto.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_crypto.c; then echo $(srcdir)/ntp_crypto.c; else echo ntp_crypto.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_crypto_.c || rm -f ntp_crypto_.c
ntp_filegen_.c: ntp_filegen.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_filegen.c; then echo $(srcdir)/ntp_filegen.c; else echo ntp_filegen.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_filegen_.c || rm -f ntp_filegen_.c
ntp_intres_.c: ntp_intres.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_intres.c; then echo $(srcdir)/ntp_intres.c; else echo ntp_intres.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_intres_.c || rm -f ntp_intres_.c
ntp_io_.c: ntp_io.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_io.c; then echo $(srcdir)/ntp_io.c; else echo ntp_io.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_io_.c || rm -f ntp_io_.c
ntp_loopfilter_.c: ntp_loopfilter.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_loopfilter.c; then echo $(srcdir)/ntp_loopfilter.c; else echo ntp_loopfilter.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_loopfilter_.c || rm -f ntp_loopfilter_.c
ntp_monitor_.c: ntp_monitor.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_monitor.c; then echo $(srcdir)/ntp_monitor.c; else echo ntp_monitor.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_monitor_.c || rm -f ntp_monitor_.c
ntp_peer_.c: ntp_peer.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_peer.c; then echo $(srcdir)/ntp_peer.c; else echo ntp_peer.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_peer_.c || rm -f ntp_peer_.c
ntp_proto_.c: ntp_proto.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_proto.c; then echo $(srcdir)/ntp_proto.c; else echo ntp_proto.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_proto_.c || rm -f ntp_proto_.c
ntp_refclock_.c: ntp_refclock.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_refclock.c; then echo $(srcdir)/ntp_refclock.c; else echo ntp_refclock.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_refclock_.c || rm -f ntp_refclock_.c
ntp_request_.c: ntp_request.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_request.c; then echo $(srcdir)/ntp_request.c; else echo ntp_request.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_request_.c || rm -f ntp_request_.c
ntp_restrict_.c: ntp_restrict.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_restrict.c; then echo $(srcdir)/ntp_restrict.c; else echo ntp_restrict.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_restrict_.c || rm -f ntp_restrict_.c
ntp_timer_.c: ntp_timer.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_timer.c; then echo $(srcdir)/ntp_timer.c; else echo ntp_timer.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_timer_.c || rm -f ntp_timer_.c
ntp_util_.c: ntp_util.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntp_util.c; then echo $(srcdir)/ntp_util.c; else echo ntp_util.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntp_util_.c || rm -f ntp_util_.c
ntpd_.c: ntpd.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/ntpd.c; then echo $(srcdir)/ntpd.c; else echo ntpd.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > ntpd_.c || rm -f ntpd_.c
refclock_acts_.c: refclock_acts.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_acts.c; then echo $(srcdir)/refclock_acts.c; else echo refclock_acts.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_acts_.c || rm -f refclock_acts_.c
refclock_arbiter_.c: refclock_arbiter.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_arbiter.c; then echo $(srcdir)/refclock_arbiter.c; else echo refclock_arbiter.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_arbiter_.c || rm -f refclock_arbiter_.c
refclock_arc_.c: refclock_arc.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_arc.c; then echo $(srcdir)/refclock_arc.c; else echo refclock_arc.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_arc_.c || rm -f refclock_arc_.c
refclock_as2201_.c: refclock_as2201.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_as2201.c; then echo $(srcdir)/refclock_as2201.c; else echo refclock_as2201.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_as2201_.c || rm -f refclock_as2201_.c
refclock_atom_.c: refclock_atom.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_atom.c; then echo $(srcdir)/refclock_atom.c; else echo refclock_atom.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_atom_.c || rm -f refclock_atom_.c
refclock_bancomm_.c: refclock_bancomm.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_bancomm.c; then echo $(srcdir)/refclock_bancomm.c; else echo refclock_bancomm.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_bancomm_.c || rm -f refclock_bancomm_.c
refclock_chronolog_.c: refclock_chronolog.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_chronolog.c; then echo $(srcdir)/refclock_chronolog.c; else echo refclock_chronolog.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_chronolog_.c || rm -f refclock_chronolog_.c
refclock_chu_.c: refclock_chu.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_chu.c; then echo $(srcdir)/refclock_chu.c; else echo refclock_chu.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_chu_.c || rm -f refclock_chu_.c
refclock_conf_.c: refclock_conf.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_conf.c; then echo $(srcdir)/refclock_conf.c; else echo refclock_conf.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_conf_.c || rm -f refclock_conf_.c
refclock_datum_.c: refclock_datum.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_datum.c; then echo $(srcdir)/refclock_datum.c; else echo refclock_datum.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_datum_.c || rm -f refclock_datum_.c
refclock_dumbclock_.c: refclock_dumbclock.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_dumbclock.c; then echo $(srcdir)/refclock_dumbclock.c; else echo refclock_dumbclock.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_dumbclock_.c || rm -f refclock_dumbclock_.c
refclock_fg_.c: refclock_fg.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_fg.c; then echo $(srcdir)/refclock_fg.c; else echo refclock_fg.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_fg_.c || rm -f refclock_fg_.c
refclock_gpsvme_.c: refclock_gpsvme.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_gpsvme.c; then echo $(srcdir)/refclock_gpsvme.c; else echo refclock_gpsvme.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_gpsvme_.c || rm -f refclock_gpsvme_.c
refclock_heath_.c: refclock_heath.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_heath.c; then echo $(srcdir)/refclock_heath.c; else echo refclock_heath.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_heath_.c || rm -f refclock_heath_.c
refclock_hopfpci_.c: refclock_hopfpci.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_hopfpci.c; then echo $(srcdir)/refclock_hopfpci.c; else echo refclock_hopfpci.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_hopfpci_.c || rm -f refclock_hopfpci_.c
refclock_hopfser_.c: refclock_hopfser.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_hopfser.c; then echo $(srcdir)/refclock_hopfser.c; else echo refclock_hopfser.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_hopfser_.c || rm -f refclock_hopfser_.c
refclock_hpgps_.c: refclock_hpgps.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_hpgps.c; then echo $(srcdir)/refclock_hpgps.c; else echo refclock_hpgps.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_hpgps_.c || rm -f refclock_hpgps_.c
refclock_irig_.c: refclock_irig.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_irig.c; then echo $(srcdir)/refclock_irig.c; else echo refclock_irig.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_irig_.c || rm -f refclock_irig_.c
refclock_jjy_.c: refclock_jjy.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_jjy.c; then echo $(srcdir)/refclock_jjy.c; else echo refclock_jjy.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_jjy_.c || rm -f refclock_jjy_.c
refclock_jupiter_.c: refclock_jupiter.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_jupiter.c; then echo $(srcdir)/refclock_jupiter.c; else echo refclock_jupiter.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_jupiter_.c || rm -f refclock_jupiter_.c
refclock_leitch_.c: refclock_leitch.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_leitch.c; then echo $(srcdir)/refclock_leitch.c; else echo refclock_leitch.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_leitch_.c || rm -f refclock_leitch_.c
refclock_local_.c: refclock_local.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_local.c; then echo $(srcdir)/refclock_local.c; else echo refclock_local.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_local_.c || rm -f refclock_local_.c
refclock_msfees_.c: refclock_msfees.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_msfees.c; then echo $(srcdir)/refclock_msfees.c; else echo refclock_msfees.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_msfees_.c || rm -f refclock_msfees_.c
refclock_mx4200_.c: refclock_mx4200.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_mx4200.c; then echo $(srcdir)/refclock_mx4200.c; else echo refclock_mx4200.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_mx4200_.c || rm -f refclock_mx4200_.c
refclock_nmea_.c: refclock_nmea.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_nmea.c; then echo $(srcdir)/refclock_nmea.c; else echo refclock_nmea.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_nmea_.c || rm -f refclock_nmea_.c
refclock_oncore_.c: refclock_oncore.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_oncore.c; then echo $(srcdir)/refclock_oncore.c; else echo refclock_oncore.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_oncore_.c || rm -f refclock_oncore_.c
refclock_palisade_.c: refclock_palisade.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_palisade.c; then echo $(srcdir)/refclock_palisade.c; else echo refclock_palisade.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_palisade_.c || rm -f refclock_palisade_.c
refclock_parse_.c: refclock_parse.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_parse.c; then echo $(srcdir)/refclock_parse.c; else echo refclock_parse.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_parse_.c || rm -f refclock_parse_.c
refclock_pcf_.c: refclock_pcf.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_pcf.c; then echo $(srcdir)/refclock_pcf.c; else echo refclock_pcf.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_pcf_.c || rm -f refclock_pcf_.c
refclock_pst_.c: refclock_pst.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_pst.c; then echo $(srcdir)/refclock_pst.c; else echo refclock_pst.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_pst_.c || rm -f refclock_pst_.c
refclock_ptbacts_.c: refclock_ptbacts.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_ptbacts.c; then echo $(srcdir)/refclock_ptbacts.c; else echo refclock_ptbacts.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_ptbacts_.c || rm -f refclock_ptbacts_.c
refclock_shm_.c: refclock_shm.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_shm.c; then echo $(srcdir)/refclock_shm.c; else echo refclock_shm.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_shm_.c || rm -f refclock_shm_.c
refclock_tpro_.c: refclock_tpro.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_tpro.c; then echo $(srcdir)/refclock_tpro.c; else echo refclock_tpro.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_tpro_.c || rm -f refclock_tpro_.c
refclock_trak_.c: refclock_trak.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_trak.c; then echo $(srcdir)/refclock_trak.c; else echo refclock_trak.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_trak_.c || rm -f refclock_trak_.c
refclock_true_.c: refclock_true.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_true.c; then echo $(srcdir)/refclock_true.c; else echo refclock_true.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_true_.c || rm -f refclock_true_.c
refclock_ulink_.c: refclock_ulink.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_ulink.c; then echo $(srcdir)/refclock_ulink.c; else echo refclock_ulink.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_ulink_.c || rm -f refclock_ulink_.c
refclock_usno_.c: refclock_usno.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_usno.c; then echo $(srcdir)/refclock_usno.c; else echo refclock_usno.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_usno_.c || rm -f refclock_usno_.c
refclock_wwv_.c: refclock_wwv.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_wwv.c; then echo $(srcdir)/refclock_wwv.c; else echo refclock_wwv.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_wwv_.c || rm -f refclock_wwv_.c
refclock_wwvb_.c: refclock_wwvb.c $(ANSI2KNR)
	$(CPP) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) `if test -f $(srcdir)/refclock_wwvb.c; then echo $(srcdir)/refclock_wwvb.c; else echo refclock_wwvb.c; fi` | sed 's/^# \([0-9]\)/#line \1/' | $(ANSI2KNR) > refclock_wwvb_.c || rm -f refclock_wwvb_.c
check_y2k_.$(OBJEXT) cmd_args_.$(OBJEXT) map_vme_.$(OBJEXT) \
ntp_config_.$(OBJEXT) ntp_control_.$(OBJEXT) ntp_crypto_.$(OBJEXT) \
ntp_filegen_.$(OBJEXT) ntp_intres_.$(OBJEXT) ntp_io_.$(OBJEXT) \
ntp_loopfilter_.$(OBJEXT) ntp_monitor_.$(OBJEXT) ntp_peer_.$(OBJEXT) \
ntp_proto_.$(OBJEXT) ntp_refclock_.$(OBJEXT) ntp_request_.$(OBJEXT) \
ntp_restrict_.$(OBJEXT) ntp_timer_.$(OBJEXT) ntp_util_.$(OBJEXT) \
ntpd_.$(OBJEXT) refclock_acts_.$(OBJEXT) refclock_arbiter_.$(OBJEXT) \
refclock_arc_.$(OBJEXT) refclock_as2201_.$(OBJEXT) \
refclock_atom_.$(OBJEXT) refclock_bancomm_.$(OBJEXT) \
refclock_chronolog_.$(OBJEXT) refclock_chu_.$(OBJEXT) \
refclock_conf_.$(OBJEXT) refclock_datum_.$(OBJEXT) \
refclock_dumbclock_.$(OBJEXT) refclock_fg_.$(OBJEXT) \
refclock_gpsvme_.$(OBJEXT) refclock_heath_.$(OBJEXT) \
refclock_hopfpci_.$(OBJEXT) refclock_hopfser_.$(OBJEXT) \
refclock_hpgps_.$(OBJEXT) refclock_irig_.$(OBJEXT) \
refclock_jjy_.$(OBJEXT) refclock_jupiter_.$(OBJEXT) \
refclock_leitch_.$(OBJEXT) refclock_local_.$(OBJEXT) \
refclock_msfees_.$(OBJEXT) refclock_mx4200_.$(OBJEXT) \
refclock_nmea_.$(OBJEXT) refclock_oncore_.$(OBJEXT) \
refclock_palisade_.$(OBJEXT) refclock_parse_.$(OBJEXT) \
refclock_pcf_.$(OBJEXT) refclock_pst_.$(OBJEXT) \
refclock_ptbacts_.$(OBJEXT) refclock_shm_.$(OBJEXT) \
refclock_tpro_.$(OBJEXT) refclock_trak_.$(OBJEXT) \
refclock_true_.$(OBJEXT) refclock_ulink_.$(OBJEXT) \
refclock_usno_.$(OBJEXT) refclock_wwv_.$(OBJEXT) \
refclock_wwvb_.$(OBJEXT) : $(ANSI2KNR)
uninstall-info-am:

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || etags $(ETAGS_ARGS) $$tags  $$unique $(LISP)

GTAGS:
	here=`CDPATH=: && cd $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH

DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  if test -f $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    $(mkinstalldirs) "$(distdir)/$$dir"; \
	  fi; \
	  if test -d $$d/$$file; then \
	    cp -pR $$d/$$file $(distdir) \
	    || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
	$(MAKE) $(AM_MAKEFLAGS) $(check_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS) check-local
check: check-am
all-am: Makefile $(PROGRAMS)

installdirs:
	$(mkinstalldirs) $(DESTDIR)$(bindir)

romfs:
	$(ROMFSINST) -e CONFIG_USER_NTPD_NTPD /bin/ntpd

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*
	-test -z "$(DISTCLEANFILES)" || rm -f $(DISTCLEANFILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-binPROGRAMS clean-checkPROGRAMS clean-generic \
	mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-compile distclean-depend \
	distclean-generic distclean-tags

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am: install-binPROGRAMS

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic mostlyclean-kr

uninstall-am: uninstall-binPROGRAMS uninstall-info-am

.PHONY: GTAGS all all-am check check-am check-local clean \
	clean-binPROGRAMS clean-checkPROGRAMS clean-generic distclean \
	distclean-compile distclean-depend distclean-generic \
	distclean-tags distdir dvi dvi-am info info-am install \
	install-am install-binPROGRAMS install-data install-data-am \
	install-exec install-exec-am install-info install-info-am \
	install-man install-strip installcheck installcheck-am \
	installdirs maintainer-clean maintainer-clean-generic \
	mostlyclean mostlyclean-compile mostlyclean-generic \
	mostlyclean-kr tags uninstall uninstall-am \
	uninstall-binPROGRAMS uninstall-info-am


check-local: 
	test -z "" || ./

$(PROGRAMS): $(LDADD)

../libntp/libntp.a:
	cd ../libntp && $(MAKE)

../libparse/libparse.a:
	cd ../libparse && $(MAKE)

version.o: $(ntpd_OBJECTS) ../libntp/libntp.a   Makefile
	env CSET=`cat $(top_srcdir)/version` $(top_builddir)/scripts/mkver ntpd
	$(COMPILE) -c version.c
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
