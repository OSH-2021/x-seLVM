/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * Copyright (C) 2013 Bastian Winkler <buz@netbuz.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __CLUTTER_GST_CONTENT_H__
#define __CLUTTER_GST_CONTENT_H__

#include <glib-object.h>

#include <clutter/clutter.h>
#include <clutter-gst/clutter-gst-player.h>

G_BEGIN_DECLS


#define CLUTTER_GST_TYPE_CONTENT            (clutter_gst_content_get_type())
#define CLUTTER_GST_CONTENT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CLUTTER_GST_TYPE_CONTENT, ClutterGstContent))
#define CLUTTER_GST_IS_CONTENT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CLUTTER_GST_TYPE_CONTENT))
#define CLUTTER_GST_CONTENT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CLUTTER_GST_TYPE_CONTENT, ClutterGstContentClass))
#define CLUTTER_GST_IS_CONTENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CLUTTER_GST_TYPE_CONTENT))
#define CLUTTER_GST_CONTENT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CLUTTER_GST_TYPE_CONTENT, ClutterGstContentClass))


typedef struct _ClutterGstContent            ClutterGstContent;
typedef struct _ClutterGstContentPrivate     ClutterGstContentPrivate;
typedef struct _ClutterGstContentClass       ClutterGstContentClass;


/**
 * ClutterGstContent:
 *
 * The #ClutterGstContent structure contains only private data
 * and should be accessed using the provided API
 *
 * Since: 0.0
 */
struct _ClutterGstContent
{
  /*< private >*/
  GObject parent;

  ClutterGstContentPrivate *priv;
};

/**
 * ClutterGstContentClass:
 *
 * The #ClutterGstContentClass structure contains only private data
 * and should be accessed using the provided API
 *
 * Since: 0.0
 */
struct _ClutterGstContentClass
{
  /*< private >*/
  GObjectClass parent_class;

  gboolean (* has_painting_content) (ClutterGstContent *self);

  void *_padding_dummy[10];
};

GType                     clutter_gst_content_get_type      (void) G_GNUC_CONST;

ClutterContent *          clutter_gst_content_new           (void);

ClutterContent *          clutter_gst_content_new_with_sink (ClutterGstVideoSink *sink);

ClutterGstFrame *         clutter_gst_content_get_frame     (ClutterGstContent *self);

void                      clutter_gst_content_set_frame     (ClutterGstContent *self,
                                                             ClutterGstFrame   *frame);

ClutterGstOverlays *      clutter_gst_content_get_overlays  (ClutterGstContent *self);

void                      clutter_gst_content_set_sink      (ClutterGstContent   *self,
                                                             ClutterGstVideoSink *sink);

ClutterGstVideoSink *     clutter_gst_content_get_sink      (ClutterGstContent *self);

ClutterGstPlayer *        clutter_gst_content_get_player    (ClutterGstContent *self);

void                      clutter_gst_content_set_player    (ClutterGstContent *self,
                                                             ClutterGstPlayer  *player);

G_END_DECLS

#endif /* __CLUTTER_GST_CONTENT_H__ */
