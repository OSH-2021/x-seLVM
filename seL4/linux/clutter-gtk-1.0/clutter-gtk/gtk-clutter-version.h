/*
 * Clutter-GTK.
 *
 * Copyright (C) 2010 Intel Corp.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Emmanuele Bassi <ebassi@linux.intel.com>
 */

#if !defined(__CLUTTER_GTK_H_INSIDE__) && !defined(CLUTTER_GTK_COMPILATION)
#error "Only <clutter-gtk/clutter-gtk.h> can be included directly."
#endif

/**
 * SECTION:gtk-clutter-version
 * @Title: Versioning
 * @short_description: Versioning utility macros
 *
 * Clutter-GTK offers a set of macros for checking the version of the library
 * an application was linked to.
 */

#ifndef __GTK_CLUTTER_VERSION_H__
#define __GTK_CLUTTER_VERSION_H__

#include <glib.h>

G_BEGIN_DECLS

/**
 * CLUTTER_GTK_MAJOR_VERSION:
 *
 * The major version of the Clutter-GTK library (1, if %CLUTTER_GTK_VERSION
 * is 1.2.3)
 */
#define CLUTTER_GTK_MAJOR_VERSION       (1)

/**
 * CLUTTER_GTK_MINOR_VERSION:
 *
 * The minor version of the Clutter-GTK library (2, if %CLUTTER_GTK_VERSION
 * is 1.2.3)
 */
#define CLUTTER_GTK_MINOR_VERSION       (8)

/**
 * CLUTTER_GTK_MICRO_VERSION:
 *
 * The micro version of the Clutter-GTK library (3, if %CLUTTER_GTK_VERSION
 * is 1.2.3)
 */
#define CLUTTER_GTK_MICRO_VERSION       (4)

/**
 * CLUTTER_GTK_VERSION:
 *
 * The full version of the Clutter-GTK library, like 1.2.3
 */
#define CLUTTER_GTK_VERSION             1.8.4

/**
 * CLUTTER_GTK_VERSION_S:
 *
 * The full version of the Clutter-GTK library, in string form (suited for
 * string concatenation)
 */
#define CLUTTER_GTK_VERSION_S           "1.8.4"

/**
 * CLUTTER_GTK_VERSION_HEX:
 *
 * Numerically encoded version of the Clutter-GTK library, like 0x010203
 */
#define CLUTTER_GTK_VERSION_HEX         ((CLUTTER_GTK_MAJOR_VERSION << 24) | \
                                         (CLUTTER_GTK_MINOR_VERSION << 16) | \
                                         (CLUTTER_GTK_MICRO_VERSION << 8))

/**
 * CLUTTER_GTK_CHECK_VERSION:
 * @major: major version, like 1 in 1.2.3
 * @minor: minor version, like 2 in 1.2.3
 * @micro: micro version, like 3 in 1.2.3
 *
 * Evaluates to %TRUE if the version of the Clutter-GTK library is greater
 * than @major, @minor and @micro
 */
#define CLUTTER_GTK_CHECK_VERSION(major,minor,micro) \
        (CLUTTER_GTK_MAJOR_VERSION > (major) || \
         (CLUTTER_GTK_MAJOR_VERSION == (major) && CLUTTER_GTK_MINOR_VERSION > (minor)) || \
         (CLUTTER_GTK_MAJOR_VERSION == (major) && CLUTTER_GTK_MINOR_VERSION == (minor) && CLUTTER_GTK_MICRO_VERSION >= (micro)))

#ifndef CLUTTER_GTK_EXTERN
#define CLUTTER_GTK_EXTERN extern
#endif

CLUTTER_GTK_EXTERN
gboolean gtk_clutter_check_version (guint major,
                                    guint minor,
                                    guint micro);

G_END_DECLS

#endif /* __GTK_CLUTTER_VERSION_H__ */
