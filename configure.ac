AC_PREREQ([2.69])
AC_INIT([RcppUUID],m4_esyscmd_s([awk '/^Version:/ {print $2}' DESCRIPTION]),[a.a.klevtsov@gmail.com])

AC_CONFIG_SRCDIR([src/RcppExports.cpp])


dnl find R home and set correct compiler + flags
if test -z "${R_HOME}" ; then
    R_HOME=`R RHOME`
fi
AC_MSG_CHECKING([R_HOME])
if test -z "${R_HOME}"; then
    AC_MSG_RESULT([No])
    AC_MSG_ERROR([Can not find ${R_HOME}.])
fi
AC_MSG_RESULT([${R_HOME}])
R_BIN="${R_HOME}/bin/R"

dnl pick all flags for testing from R
CC=`"${R_BIN}" CMD config CC`
CPP=`"${R_BIN}" CMD config CPP`
CXX=`"${R_BIN}" CMD config CXX`
CFLAGS=`"${R_BIN}" CMD config CFLAGS`
CPPFLAGS=`"${R_BIN}" CMD config CPPFLAGS`
LDFLAGS=`"${R_BIN}" CMD config LDFLAGS`

AC_PROG_CC(${CC})
AC_PROG_CPP(${CPP})
AC_PROG_CXX(${CXX})
AC_REQUIRE_CPP
AC_LANG(C++)

host_os=`uname -s`
case "${host_os}" in
    Darwin*)
        PKG_CPPFLAGS=-DGUID_CFUUID
        PKG_LIBS=-Wl,-S
        ;;
    Linux*)
        AC_CHECK_HEADER([uuid/uuid.h],LIBUUID_HEADER=yes)
        AC_CHECK_LIB([uuid],[uuid_generate],LIBUUID_LIB=yes)
        if test "x${LIBUUID_HEADER}" = "xyes" && test "x${LIBUUID_LIB}" = "xyes"; then
            PKG_CPPFLAGS=-DGUID_LIBUUID
            PKG_LIBS="-Wl,-S -luuid"
        else
            PKG_CPPFLAGS=-DGUID_RANDOM
        fi
        ;;
    SunOS*)
        AC_CHECK_HEADER([uuid/uuid.h],LIBUUID_HEADER=yes)
        AC_CHECK_LIB([uuid],[uuid_generate],LIBUUID_LIB=yes)
        if test "x${LIBUUID_HEADER}" = "xyes" && test "x${LIBUUID_LIB}" = "xyes"; then
            PKG_CPPFLAGS=-DGUID_LIBUUID
            PKG_LIBS=-luuid
        else
            PKG_CPPFLAGS=-DGUID_RANDOM
        fi
        ;;
    *)
        PKG_CPPFLAGS=-DGUID_RANDOM
        ;;
esac

AC_MSG_NOTICE([OS: ${host_os}])
AC_MSG_NOTICE([CC: ${CC}])
AC_MSG_NOTICE([CPP: ${CPP}])
AC_MSG_NOTICE([CXX: ${CXX}])
AC_MSG_NOTICE([PKG_CPPFLAGS: ${PKG_CPPFLAGS}])
AC_MSG_NOTICE([PKG_LIBS: ${PKG_LIBS}])
AC_MSG_NOTICE([${PACKAGE_NAME}: ${PACKAGE_VERSION}])

AC_SUBST([PKG_CPPFLAGS])
AC_SUBST([PKG_LIBS])

AC_CONFIG_FILES([src/Makevars])

AC_OUTPUT
