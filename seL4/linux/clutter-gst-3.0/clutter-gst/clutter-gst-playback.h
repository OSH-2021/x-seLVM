/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-player.h - Wrap some convenience functions around playbin2
 *
 * Authored By Damien Lespiau    <damien.lespiau@intel.com>
 *             Lionel Landwerlin <lionel.g.landwerlin@linux.intel.com>
 *             Matthew Allum     <mallum@openedhand.com>
 *             Emmanuele Bassi   <ebassi@linux.intel.com>
 *             Andre Moreira Magalhaes <andre.magalhaes@collabora.co.uk>
 *
 * Copyright (C) 2006 OpenedHand
 * Copyright (C) 2009-2013 Intel Corporation
 * Copyright (C) 2012 Collabora Ltd. <http://www.collabora.co.uk/>
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
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#if !defined(__CLUTTER_GST_H_INSIDE__) && !defined(CLUTTER_GST_COMPILATION)
#error "Only <clutter-gst/clutter-gst.h> can be include directly."
#endif

#ifndef __CLUTTER_GST_PLAYBACK_H__
#define __CLUTTER_GST_PLAYBACK_H__

#include <glib-object.h>

#include <clutter-gst/clutter-gst-types.h>
#include <gst/gst.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_PLAYBACK clutter_gst_playback_get_type()

#define CLUTTER_GST_PLAYBACK(obj)                               \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj),                           \
                               CLUTTER_GST_TYPE_PLAYBACK,       \
                               ClutterGstPlayback))

#define CLUTTER_GST_PLAYBACK_CLASS(klass)                   \
  (G_TYPE_CHECK_CLASS_CAST ((klass),                        \
                            CLUTTER_GST_TYPE_PLAYBACK,      \
                            ClutterGstPlaybackClass))

#define CLUTTER_GST_IS_PLAYBACK(obj)                            \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj),                           \
                               CLUTTER_GST_TYPE_PLAYBACK))

#define CLUTTER_GST_IS_PLAYBACK_CLASS(klass)            \
  (G_TYPE_CHECK_CLASS_TYPE ((klass),                    \
                            CLUTTER_GST_TYPE_PLAYBACK))

#define CLUTTER_GST_PLAYBACK_GET_CLASS(obj)                     \
  (G_TYPE_INSTANCE_GET_CLASS ((obj),                            \
                              CLUTTER_GST_TYPE_PLAYBACK,        \
                              ClutterGstPlaybackClass))

typedef struct _ClutterGstPlayback ClutterGstPlayback;
typedef struct _ClutterGstPlaybackClass ClutterGstPlaybackClass;
typedef struct _ClutterGstPlaybackPrivate ClutterGstPlaybackPrivate;

/**
 * ClutterGstPlayback:
 *
 * Implementation of #ClutterGstPlayback that displays media streams
 * using GStreamer.
 *
 * The #ClutterGstPlayback structure contains only private data and
 * should not be accessed directly.
 */
struct _ClutterGstPlayback
{
  GObject parent;

  ClutterGstPlaybackPrivate *priv;
};

/**
 * ClutterGstPlaybackClass:
 * @download_buffering: signal class closure for #ClutterGstPlayback::download-buffering
 *
 * Base class for #ClutterGstPlayback.
 */
struct _ClutterGstPlaybackClass
{
  /*< private >*/
  GObjectClass parent_class;

  /*< public >*/
  /* signals */
  gboolean (* should_buffer)  (ClutterGstPlayback *self,
                                GstQuery *query);
};

GType clutter_gst_playback_get_type (void) G_GNUC_CONST;

ClutterGstPlayback *      clutter_gst_playback_new (void);

void                      clutter_gst_playback_set_uri             (ClutterGstPlayback        *self,
                                                                    const gchar               *uri);
gchar *                   clutter_gst_playback_get_uri             (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_filename        (ClutterGstPlayback        *self,
                                                                    const gchar               *filename);

gchar *                   clutter_gst_playback_get_user_agent      (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_user_agent      (ClutterGstPlayback        *self,
                                                                    const gchar               *user_agent);

ClutterGstSeekFlags       clutter_gst_playback_get_seek_flags      (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_seek_flags      (ClutterGstPlayback        *self,
                                                                    ClutterGstSeekFlags        flags);

ClutterGstBufferingMode   clutter_gst_playback_get_buffering_mode  (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_buffering_mode  (ClutterGstPlayback        *self,
                                                                    ClutterGstBufferingMode    mode);
gdouble                   clutter_gst_playback_get_buffer_fill     (ClutterGstPlayback        *self);
gint                      clutter_gst_playback_get_buffer_size     (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_buffer_size     (ClutterGstPlayback        *self,
                                                                    gint                       size);
gint64                    clutter_gst_playback_get_buffer_duration (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_buffer_duration (ClutterGstPlayback        *self,
                                                                    gint64                     duration);

GList *                   clutter_gst_playback_get_audio_streams   (ClutterGstPlayback        *self);
gint                      clutter_gst_playback_get_audio_stream    (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_audio_stream    (ClutterGstPlayback        *self,
                                                                    gint                       index_);

void                      clutter_gst_playback_set_subtitle_uri    (ClutterGstPlayback        *self,
                                                                    const gchar               *uri);
gchar *                   clutter_gst_playback_get_subtitle_uri    (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_subtitle_font_name
                                                                   (ClutterGstPlayback        *self,
                                                                    const char                *font_name);
gchar *                   clutter_gst_playback_get_subtitle_font_name
                                                                   (ClutterGstPlayback        *self);
GList *                   clutter_gst_playback_get_subtitle_tracks (ClutterGstPlayback        *self);
gint                      clutter_gst_playback_get_subtitle_track  (ClutterGstPlayback        *self);
void                      clutter_gst_playback_set_subtitle_track  (ClutterGstPlayback        *self,
                                                                    gint                       index_);

gboolean                  clutter_gst_playback_get_in_seek         (ClutterGstPlayback        *self);

void                      clutter_gst_playback_set_progress        (ClutterGstPlayback        *self,
                                                                    gdouble                    progress);
gdouble                   clutter_gst_playback_get_progress        (ClutterGstPlayback        *self);
gdouble                   clutter_gst_playback_get_position        (ClutterGstPlayback        *self);
gdouble                   clutter_gst_playback_get_duration        (ClutterGstPlayback        *self);

gboolean                  clutter_gst_playback_is_live_media       (ClutterGstPlayback        *self);

G_END_DECLS

#endif /* __CLUTTER_GST_PLAYBACK_H__ */
