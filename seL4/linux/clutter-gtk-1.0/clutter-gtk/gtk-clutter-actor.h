/* gtk-clutter-actor.h: Gtk widget ClutterActor
 *
 * Copyright (C) 2009 Red Hat, Inc
 * Copyright (C) 2010 Intel Corp
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
 *   Alexander Larsson <alexl@redhat.com>
 *   Emmanuele Bassi <ebassi@linux.intel.com>
 */

#if !defined(__CLUTTER_GTK_H_INSIDE__) && !defined(CLUTTER_GTK_COMPILATION)
#error "Only <clutter-gtk/clutter-gtk.h> can be included directly."
#endif

#ifndef __GTK_CLUTTER_ACTOR_H__
#define __GTK_CLUTTER_ACTOR_H__

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-version.h>

G_BEGIN_DECLS

#define GTK_CLUTTER_TYPE_ACTOR          (gtk_clutter_actor_get_type ())
#define GTK_CLUTTER_ACTOR(o)            (G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_CLUTTER_TYPE_ACTOR, GtkClutterActor))
#define GTK_CLUTTER_IS_ACTOR(o)         (G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_CLUTTER_TYPE_ACTOR))
#define GTK_CLUTTER_ACTOR_CLASS(k)      (G_TYPE_CHECK_CLASS_CAST ((k), GTK_CLUTTER_TYPE_ACTOR, GtkClutterActorClass))
#define GTK_CLUTTER_IS_ACTOR_CLASS(k)   (G_TYPE_CHECK_CLASS_TYPE ((k), GTK_CLUTTER_TYPE_ACTOR))
#define GTK_CLUTTER_ACTOR_GET_CLASS(o)  (G_TYPE_INSTANCE_GET_CLASS ((o), GTK_CLUTTER_TYPE_ACTOR, GtkClutterActorClass))

typedef struct _GtkClutterActor         GtkClutterActor;
typedef struct _GtkClutterActorPrivate  GtkClutterActorPrivate;
typedef struct _GtkClutterActorClass    GtkClutterActorClass;

/**
 * GtkClutterActor:
 *
 * A ClutterActor containing a #GtkWidget.
 */
struct _GtkClutterActor
{
  /*< private >*/
  ClutterActor parent_instance;

  GtkClutterActorPrivate *priv;
};

/**
 * GtkClutterActorClass:
 *
 * Base class for #GtkClutterActor.
 */
struct _GtkClutterActorClass
{
  /*< private >*/
  ClutterActorClass parent_class;

  /* padding for future expansion */
  void (*_clutter_gtk_reserved1) (void);
  void (*_clutter_gtk_reserved2) (void);
  void (*_clutter_gtk_reserved3) (void);
  void (*_clutter_gtk_reserved4) (void);
  void (*_clutter_gtk_reserved5) (void);
  void (*_clutter_gtk_reserved6) (void);
};

CLUTTER_GTK_EXTERN
GType         gtk_clutter_actor_get_type          (void) G_GNUC_CONST;
CLUTTER_GTK_EXTERN
ClutterActor *gtk_clutter_actor_new               (void);
CLUTTER_GTK_EXTERN
ClutterActor *gtk_clutter_actor_new_with_contents (GtkWidget       *contents);
CLUTTER_GTK_EXTERN
GtkWidget *   gtk_clutter_actor_get_contents      (GtkClutterActor *actor);
CLUTTER_GTK_EXTERN
GtkWidget *   gtk_clutter_actor_get_widget        (GtkClutterActor *actor);

G_END_DECLS

#endif /* __GTK_CLUTTER_ACTOR_H__ */
