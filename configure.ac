#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Turns-n-Layers], [1.2.1], [simo@furrydolphin.net], [Turns-n-Layers])
AC_CONFIG_SRCDIR([src/mainappwin.cpp])

AC_MSG_NOTICE([Turns-n-Layers Version:])
AC_MSG_RESULT([$VERSION])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AC_ARG_ENABLE([optimum],
              [AS_HELP_STRING([--enable-optimum], [Enable optimum compile?])],
              [CXXFLAGS='-O3 -Wuninitialized -finline-functions -fomit-frame-pointer -fexpensive-optimizations'])

# Checks for libraries.

AC_MSG_CHECKING([Looking for working FOX libs...])

SIMO_FOX_COMPILE

SIMO_FOX_RUN

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

AC_CONFIG_FILES([Makefile
                 src/Makefile
		 src/locations.h
                 etc/Makefile])
AC_OUTPUT

cat << EOF

>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Make Application <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
>>                                                                        <<
>>  Configure complete :-)                                                <<
>>                                                                        <<
>>  Next, enter: "make" (no quotes) to compile the program.               <<
>>  Note: You may have to su to root to complete the install.             <<
>>  Then enter "make install" to install the program on your system.      <<
>>                                                                        <<
>>  If you haven't done so already, be sure to see INSTALL   for          <<
>>  some important information on the running of Turns-n-Layers.          <<
>>                                                                        <<
>>  Thanks for choosing Turns-n-Layers                                    <<
>>  Enjoy your new program :-)                                            <<
>>                                                                        <<
>>            IF SOFTWARE CAN BE FREE, WHY CAN'T DOLPHINS?                <<
>>                                                                        <<
>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Make Application <<<<<<<<<<<<<<<<<<<<<<<<<<<<<

EOF
