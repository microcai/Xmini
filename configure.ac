
# Xmini - PACKAGE_DESCRIBTION

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

m4_define([package_name], [Xmini])

AC_INIT([package_name], [0.0.1], [BUG REPORT URL], [package_name])
AM_INIT_AUTOMAKE([-Wall])
# AC_GNU_SOURCE

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_GNU_SOURCE
AC_PROG_CC
AC_HEADER_STDC

AC_PREFIX_DEFAULT([/usr])

# std headers
AC_CHECK_HEADERS([errno.h sys/fcntl.h sys/types.h ])

AC_CHECK_HEADERS([drm/drm.h])

AC_CHECK_LIB([drm],[main],[],[AC_MSG_FAILURE(DRM not found!,1)])


PKG_CHECK_MODULES(GLIB2, [
	glib-2.0
])


PKG_CHECK_MODULES(ALL_NEEDED, [
	glib-2.0
])


# OUTPUT files
AC_CONFIG_FILES(
src/Makefile
icons/Makefile
doc/Makefile
Makefile
)

AC_OUTPUT
