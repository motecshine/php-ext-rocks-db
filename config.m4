dnl $Id$
dnl config.m4 for extension rocksdb

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(rocksdb, for rocksdb support,
dnl Make sure that the comment is aligned:
dnl [  --with-rocksdb             Include rocksdb support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(rocksdb, whether to enable rocksdb support,
dnl Make sure that the comment is aligned:
[  --enable-rocksdb          Enable rocksdb support], no)

if test "$PHP_ROCKSDB" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=\`$PKG_CONFIG foo --cflags\`
  dnl     LIBFOO_LIBDIR=\`$PKG_CONFIG foo --libs\`
  dnl     LIBFOO_VERSON=\`$PKG_CONFIG foo --modversion\`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, ROCKSDB_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-rocksdb -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/rocksdb.h"  # you most likely want to change this
  dnl if test -r $PHP_ROCKSDB/$SEARCH_FOR; then # path given as parameter
  dnl   ROCKSDB_DIR=$PHP_ROCKSDB
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for rocksdb files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ROCKSDB_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ROCKSDB_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the rocksdb distribution])
  dnl fi

  dnl # --with-rocksdb -> add include path
  dnl PHP_ADD_INCLUDE($ROCKSDB_DIR/include)

  dnl # --with-rocksdb -> check for lib and symbol presence
  dnl LIBNAME=ROCKSDB # you may want to change this
  dnl LIBSYMBOL=ROCKSDB # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ROCKSDB_DIR/$PHP_LIBDIR, ROCKSDB_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ROCKSDBLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong rocksdb lib version or lib not found])
  dnl ],[
  dnl   -L$ROCKSDB_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ROCKSDB_SHARED_LIBADD)

  dnl # In case of no dependencies
  PHP_ADD_LIBRARY_WITH_PATH("rocksdb", "/usr/local/include", ROCKSDB_SHARED_LIBADD)
  PHP_SUBST(ROCKSDB_SHARED_LIBADD)
  AC_DEFINE(HAVE_ROCKSDB, 1, [ Have rocksdb support ])

  PHP_NEW_EXTENSION(rocksdb, 
  rocksdb.c   \
  src/rocksdb_connector.c, 
  $ext_shared)
fi
