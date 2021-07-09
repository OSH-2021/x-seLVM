/* gtk-clutter-window.h: GtkWindow which provides a hidden ClutterStage
 *
 * Copyright (C) 2009 Collabora Ltd.
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
 *   Danielle Madeley <danielle.madeley@collabora.co.uk>
 */

#if !defined(__CLUTTER_GTK_H_INSIDE__) && !defined(CLUTTER_GTK_COMPILATION)
#error "Only <clutter-gtk/clutter-gtk.h> can be included directly."
#endif

#ifndef __GTK_CLUTTER_WINDOW_H__
#define __GTK_CLUTTER_WINDOW_H__

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-version.h>

G_BEGIN_DECLS

#define GTK_CLUTTER_TYPE_WINDOW          (gtk_clutter_window_get_type ())
#define GTK_CLUTTER_WINDOW(o)            (G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_CLUTTER_TYPE_WINDOW, GtkClutterWindow))
#define GTK_CLUTTER_IS_WINDOW(o)         (G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_CLUTTER_TYPE_WINDOW))
#define GTK_CLUTTER_WINDOW_CLASS(k)      (G_TYPE_CHECK_CLASS_CAST ((k), GTK_CLUTTER_TYPE_WINDOW, GtkClutterWindowClass))
#define GTK_CLUTTER_IS_WINDOW_CLASS(k)   (G_TYPE_CHECK_CLASS_TYPE ((k), GTK_CLUTTER_TYPE_WINDOW))
#define GTK_CLUTTER_WINDOW_GET_CLASS(o)  (G_TYPE_INSTANCE_GET_CLASS ((o), GTK_CLUTTER_TYPE_WINDOW, GtkClutterWindowClass))

typedef struct _GtkClutterWindow         GtkClutterWindow;
typedef struct _GtkClutterWindowPrivate  GtkClutterWindowPrivate;
typedef struct _GtkClutterWindowClass    GtkClutterWindowClass;

/**
 * GtkClutterWindow:
 *
 * A #GtkWindow containing a #ClutterStage.
 *
 * The <structname>GtkClutterWindow</structname> structure contains only
 * private data and it should be accessed using the provided API.
 */
struct _GtkClutterWindow
{
  /*< private >*/
  GtkWindow parent_instance;

  GtkClutterWindowPrivate *priv;
};

/**
 * GtkClutterWindowClass:
 *
 * Base class for #GtkClutterWindow.
 *
 * The <structname>GtkClutterWindowClass</structname> structure contains
 * only private data.
 */
struct _GtkClutterWindowClass
{
  /*< private >*/
  GtkWindowClass parent_class;

  /* padding for future expansion */
  void (*_clutter_gtk_reserved1) (void);
  void (*_clutter_gtk_reserved2) (void);
  void (*_clutter_gtk_reserved3) (void);
  void (*_clutter_gtk_reserved4) (void);
  void (*_clutter_gtk_reserved5) (void);
  void (*_clutter_gtk_reserved6) (void);
};

CLUTTER_GTK_EXTERN
GType gtk_clutter_window_get_type (void) G_GNUC_CONST;

CLUTTER_GTK_EXTERN
GtkWidget *   gtk_clutter_window_new       (void);
CLUTTER_GTK_EXTERN
ClutterActor *gtk_clutter_window_get_stage (GtkClutterWindow *window);

G_END_DECLS

#endif /* __GTK_CLUTTER_WINDOW_H__ */
