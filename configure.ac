AC_INIT([DCC042-PROXY], [1.0], [celso.zacarias@estudante.ufjf.br])
PKG_CHECK_MODULES([CHECK], [check >= 0.15.2])
AM_INIT_AUTOMAKE([foreign -Wall subdir-objects])
: ${CFLAGS="-I../include -O2"}
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT
