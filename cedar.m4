# check for cedar libraries, not in usual location
AC_DEFUN(DODS_CEDAR_PACKAGE, [dnl
    AC_ARG_WITH(cedar,
        [  --with-cedar=ARG          Where is the local cedar library sources (directory)],
        CEDAR_PATH=${withval}, CEDAR_PATH="$CEDAR_PATH")
    if test ! -d "$CEDAR_PATH"
    then
	AC_MSG_ERROR([Could not find Cedar library])
    else
	INCS="$INCS -I${CEDAR_PATH}/include"
	LIBS="$LIBS -L${CEDAR_PATH}/lib -lCedar"
	AC_SUBST(INCS)
    fi])

