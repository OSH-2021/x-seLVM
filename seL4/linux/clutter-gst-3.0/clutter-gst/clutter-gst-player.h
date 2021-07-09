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

#ifndef __CLUTTER_GST_PLAYER_H__
#define __CLUTTER_GST_PLAYER_H__

#include <glib-object.h>
#include <gst/gst.h>

#include <clutter-gst/clutter-gst-types.h>
#include <clutter-gst/clutter-gst-video-sink.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_PLAYER clutter_gst_player_get_type()

#define CLUTTER_GST_PLAYER(obj)                                         \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj),                                   \
                               CLUTTER_GST_TYPE_PLAYER,                 \
                               ClutterGstPlayer))
#define CLUTTER_GST_IS_PLAYER(obj)                              \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj),                           \
                               CLUTTER_GST_TYPE_PLAYER))
#define CLUTTER_GST_PLAYER_GET_INTERFACE(obj)                           \
  (G_TYPE_INSTANCE_GET_INTERFACE ((obj),                                \
                                  CLUTTER_GST_TYPE_PLAYER,              \
                                  ClutterGstPlayerIface))

typedef struct _ClutterGstPlayer ClutterGstPlayer;
typedef struct _ClutterGstPlayerIface ClutterGstPlayerIface;
typedef struct _ClutterGstPlayerIfacePrivate ClutterGstPlayerIfacePrivate;


/**
 * ClutterGstPlayer:
 *
 * #ClutterGstPlayer is an opaque structure whose members cannot be
 * directly accessed
 *
 * Since: 1.4
 */

/**
 * ClutterGstPlayerIface:
 * @get_frame: virtual function; returns the current visible frame
 * @get_pipeline: virtual function; returns the current GStreamer pipeline
 * @get_video_sink: virtual function; returns the current ClutterGst video sink
 * @get_idle: virtual function; returns whether the player is currently in idle state
 * @get_audio_volume: virtual function; returns the current audio volume
 * @set_audio_volume: virtual function; sets the audio volume
 * @get_playing: virtual function; returns whether the player is currently playing
 * @set_playing: virtual function; starts or stops the player from playing
 * @new_frame: signal class closure for #ClutterGstPlayer::new-frame
 * @ready: signal class closure for #ClutterGstPlayer::ready
 * @eos: signal class closure for #ClutterGstPlayer::eos
 * @error: signal class closure for #ClutterGstPlayer::error
 * @size_change: signal class closure for #ClutterGstPlayer::size-change
 *
 * Interface vtable for #ClutterGstPlayer implementations
 *
 * Since: 1.4
 */
struct _ClutterGstPlayerIface
{
  /*< private >*/
  GTypeInterface base_iface;

  ClutterGstPlayerIfacePrivate *priv;

  /*< public >*/
  ClutterGstFrame     *(* get_frame)        (ClutterGstPlayer *self);
  GstElement *         (* get_pipeline)     (ClutterGstPlayer *self);
  ClutterGstVideoSink *(* get_video_sink)   (ClutterGstPlayer *self);

  gboolean             (* get_idle)         (ClutterGstPlayer *self);

  gdouble              (* get_audio_volume) (ClutterGstPlayer *self);
  void                 (* set_audio_volume) (ClutterGstPlayer *self,
                                             gdouble           volume);

  gboolean             (* get_playing)      (ClutterGstPlayer *self);
  void                 (* set_playing)      (ClutterGstPlayer *self,
                                             gboolean          playing);

  /*< private >*/
  gpointer _padding_vfuncs[16];

  /*< public >*/
  /* signals */
  void (* new_frame)           (ClutterGstPlayer *self, ClutterGstFrame *frame);
  void (* ready)               (ClutterGstPlayer *self);
  void (* eos)                 (ClutterGstPlayer *self);
  void (* error)               (ClutterGstPlayer *self,
                                const GError     *error);
  void (* size_change)         (ClutterGstPlayer *self,
                                gint              width,
                                gint              height);

  /*< private >*/
  gpointer _padding_signals[8];
};

GType clutter_gst_player_get_type (void) G_GNUC_CONST;

ClutterGstFrame *         clutter_gst_player_get_frame        (ClutterGstPlayer        *self);

GstElement *              clutter_gst_player_get_pipeline     (ClutterGstPlayer        *self);

ClutterGstVideoSink *     clutter_gst_player_get_video_sink   (ClutterGstPlayer        *self);

gboolean                  clutter_gst_player_get_idle         (ClutterGstPlayer        *self);

gboolean                  clutter_gst_player_get_playing      (ClutterGstPlayer        *self);
void                      clutter_gst_player_set_playing      (ClutterGstPlayer        *self,
                                                               gboolean                 playing);

gdouble                   clutter_gst_player_get_audio_volume (ClutterGstPlayer        *self);
void                      clutter_gst_player_set_audio_volume (ClutterGstPlayer        *self,
                                                               gdouble                  volume);

G_END_DECLS

#endif /* __CLUTTER_GST_PLAYER_H__ */
