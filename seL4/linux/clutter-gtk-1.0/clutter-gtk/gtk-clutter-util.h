/* gtk-clutter-util.h: GTK+ integration utilities
 *
 * Copyright (C) 2008 OpenedHand
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
 * License along with this library. If not see <http://www.fsf.org/licensing>.
 *
 * Authors:
 *   Emmanuele Bassi  <ebassi@openedhand.com>
 */

#if !defined(__CLUTTER_GTK_H_INSIDE__) && !defined(CLUTTER_GTK_COMPILATION)
#error "Only <clutter-gtk/clutter-gtk.h> can be included directly."
#endif

#ifndef __GTK_CLUTTER_UTIL_H__
#define __GTK_CLUTTER_UTIL_H__

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-version.h>

G_BEGIN_DECLS

CLUTTER_GTK_EXTERN
ClutterInitError gtk_clutter_init           (int            *argc,
                                             char         ***argv)  G_GNUC_WARN_UNUSED_RESULT;
CLUTTER_GTK_EXTERN
ClutterInitError gtk_clutter_init_with_args (int            *argc,
                                             char         ***argv,
                                             const char     *parameter_string,
                                             GOptionEntry   *entries,
                                             const char     *translation_domain,
                                             GError        **error) G_GNUC_WARN_UNUSED_RESULT;
CLUTTER_GTK_EXTERN
GOptionGroup *gtk_clutter_get_option_group  (void);

G_END_DECLS

#endif /* __GTK_CLUTTER_UTIL_H__ */
