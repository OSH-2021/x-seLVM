/* gtk-clutter-texture.h
 *
 * Copyright (C) 2010  Intel Corp.
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
 *   Emmanuele Bassi  <ebassi@linux.intel.com>
 */

#if !defined(__CLUTTER_GTK_H_INSIDE__) && !defined(CLUTTER_GTK_COMPILATION)
#error "Only <clutter-gtk/clutter-gtk.h> can be included directly."
#endif

#ifndef __GTK_CLUTTER_TEXTURE_H__
#define __GTK_CLUTTER_TEXTURE_H__

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-version.h>

G_BEGIN_DECLS

#define GTK_CLUTTER_TYPE_TEXTURE                (gtk_clutter_texture_get_type ())
#define GTK_CLUTTER_TEXTURE(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_CLUTTER_TYPE_TEXTURE, GtkClutterTexture))
#define GTK_CLUTTER_IS_TEXTURE(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_CLUTTER_TYPE_TEXTURE))
#define GTK_CLUTTER_TEXTURE_CLASS(klass)        (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_CLUTTER_TYPE_TEXTURE, GtkClutterTextureClass))
#define GTK_CLUTTER_IS_TEXTURE_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_CLUTTER_TYPE_TEXTURE))
#define GTK_CLUTTER_TEXTURE_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_CLUTTER_TYPE_TEXTURE, GtkClutterTextureClass))

/**
 * GTK_CLUTTER_TEXTURE_ERROR:
 *
 * Error domain for #GtkClutterTexture
 *
 * Since: 1.0
 */
#define GTK_CLUTTER_TEXTURE_ERROR               (gtk_clutter_texture_error_quark ())

typedef struct _GtkClutterTexture               GtkClutterTexture;
typedef struct _GtkClutterTextureClass          GtkClutterTextureClass;

/**
 * GtkClutterTextureError:
 * @GTK_CLUTTER_TEXTURE_ERROR_INVALID_STOCK_ID: Invalid stock id
 *
 * Error enumeration for #GtkClutterTexture
 *
 * Since: 1.0
 */
typedef enum {
  GTK_CLUTTER_TEXTURE_ERROR_INVALID_STOCK_ID
} GtkClutterTextureError;

/**
 * GtkClutterTexture:
 *
 * The <structname>GtkClutterTexture</structname> structure contains
 * only private data and should be accessed using the provided API.
 *
 * Since: 1.0
 */
struct _GtkClutterTexture
{
  /*< private >*/
  ClutterTexture parent_instance;
};

/**
 * GtkClutterTextureClass:
 *
 * The <structname>GtkClutterTextureClass</structname> structure contains
 * only private data.
 *
 * Since: 1.0
 */
struct _GtkClutterTextureClass
{
  /*< private >*/
  ClutterTextureClass parent_class;
};

CLUTTER_GTK_EXTERN
GQuark gtk_clutter_texture_error_quark (void);
CLUTTER_GTK_EXTERN
GType gtk_clutter_texture_get_type (void) G_GNUC_CONST;

CLUTTER_GTK_EXTERN
ClutterActor *  gtk_clutter_texture_new (void);

CLUTTER_GTK_EXTERN
gboolean        gtk_clutter_texture_set_from_pixbuf     (GtkClutterTexture *texture,
                                                         GdkPixbuf         *pixbuf,
                                                         GError           **error);
CLUTTER_GTK_EXTERN
gboolean        gtk_clutter_texture_set_from_stock      (GtkClutterTexture *texture,
                                                         GtkWidget         *widget,
                                                         const gchar       *stock_id,
                                                         GtkIconSize        icon_size,
                                                         GError           **error);
CLUTTER_GTK_EXTERN
gboolean        gtk_clutter_texture_set_from_icon_name  (GtkClutterTexture *texture,
                                                         GtkWidget         *widget,
                                                         const gchar       *icon_name,
                                                         GtkIconSize        icon_size,
                                                         GError           **error);

G_END_DECLS

#endif /* __GTK_CLUTTER_TEXTURE_H__ */
