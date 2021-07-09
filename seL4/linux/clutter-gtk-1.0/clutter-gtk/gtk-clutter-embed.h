/* gtk-clutter-embed.h: Embeddable ClutterStage
 *
 * Copyright (C) 2007 OpenedHand
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
 *   Iain Holmes  <iain@openedhand.com>
 *   Emmanuele Bassi  <ebassi@openedhand.com>
 */

#if !defined(__CLUTTER_GTK_H_INSIDE__) && !defined(CLUTTER_GTK_COMPILATION)
#error "Only <clutter-gtk/clutter-gtk.h> can be included directly."
#endif

#ifndef __GTK_CLUTTER_EMBED_H__
#define __GTK_CLUTTER_EMBED_H__

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-version.h>

G_BEGIN_DECLS

#define GTK_CLUTTER_TYPE_EMBED          (gtk_clutter_embed_get_type ())
#define GTK_CLUTTER_EMBED(o)            (G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_CLUTTER_TYPE_EMBED, GtkClutterEmbed))
#define GTK_CLUTTER_IS_EMBED(o)         (G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_CLUTTER_TYPE_EMBED))
#define GTK_CLUTTER_EMBED_CLASS(k)      (G_TYPE_CHECK_CLASS_CAST ((k), GTK_CLUTTER_TYPE_EMBED, GtkClutterEmbedClass))
#define GTK_CLUTTER_IS_EMBED_CLASS(k)   (G_TYPE_CHECK_CLASS_TYPE ((k), GTK_CLUTTER_TYPE_EMBED))
#define GTK_CLUTTER_EMBED_GET_CLASS(o)  (G_TYPE_INSTANCE_GET_CLASS ((o), GTK_CLUTTER_TYPE_EMBED, GtkClutterEmbedClass))

typedef struct _GtkClutterEmbed         GtkClutterEmbed;
typedef struct _GtkClutterEmbedPrivate  GtkClutterEmbedPrivate;
typedef struct _GtkClutterEmbedClass    GtkClutterEmbedClass;

/**
 * GtkClutterEmbed:
 *
 * A #GtkWidget containing the default Clutter stage.
 *
 * The <structname>GtkClutterEmbed</structname> structure contains only
 * private data and should be accessed using the provided API.
 */
struct _GtkClutterEmbed
{
  /*< private >*/
  GtkContainer parent_instance;

  GtkClutterEmbedPrivate *priv;
};

/**
 * GtkClutterEmbedClass:
 *
 * Base class for #GtkClutterEmbed.
 *
 * The <structname>GtkClutterEmbedClass</structname> contains only private
 * data.
 */
struct _GtkClutterEmbedClass
{
  /*< private >*/
  GtkContainerClass parent_class;

  /* padding for future expansion */
  void (*_clutter_gtk_reserved1) (void);
  void (*_clutter_gtk_reserved2) (void);
  void (*_clutter_gtk_reserved3) (void);
  void (*_clutter_gtk_reserved4) (void);
  void (*_clutter_gtk_reserved5) (void);
  void (*_clutter_gtk_reserved6) (void);
};

CLUTTER_GTK_EXTERN
GType         gtk_clutter_embed_get_type  (void) G_GNUC_CONST;

CLUTTER_GTK_EXTERN
GtkWidget *   gtk_clutter_embed_new       (void);
CLUTTER_GTK_EXTERN
ClutterActor *gtk_clutter_embed_get_stage (GtkClutterEmbed *embed);
CLUTTER_GTK_EXTERN
void          gtk_clutter_embed_set_use_layout_size (GtkClutterEmbed *embed,
						     gboolean use_layout_size);
CLUTTER_GTK_EXTERN
gboolean      gtk_clutter_embed_get_use_layout_size (GtkClutterEmbed *embed);

G_END_DECLS

#endif /* __GTK_CLUTTER_EMBED_H__ */
