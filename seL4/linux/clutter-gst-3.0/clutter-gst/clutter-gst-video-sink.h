/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Cogl.
 *
 * clutter-gst-video-sink.h - Gstreamer Video Sink that renders to a
 *                            Cogl Pipeline.
 *
 * Authored by Jonathan Matthew  <jonathan@kaolin.wh9.net>,
 *             Chris Lord        <chris@openedhand.com>
 *             Damien Lespiau    <damien.lespiau@intel.com>
 *             Matthew Allum     <mallum@openedhand.com>
 *             Plamena Manolova  <plamena.n.manolova@intel.com>
 *             Lionel Landwerlin <lionel.g.landwerlin@linux.intel.com>
 *
 * Copyright (C) 2007, 2008 OpenedHand
 * Copyright (C) 2009, 2010, 2013, 2014 Intel Corporation
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

#ifndef __CLUTTER_GST_VIDEO_SINK_H__
#define __CLUTTER_GST_VIDEO_SINK_H__

#include <cogl/cogl.h>
#include <gst/video/gstvideosink.h>
#include <clutter-gst/clutter-gst-types.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_VIDEO_SINK clutter_gst_video_sink_get_type()

#define CLUTTER_GST_VIDEO_SINK(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_VIDEO_SINK, ClutterGstVideoSink))

#define CLUTTER_GST_VIDEO_SINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_VIDEO_SINK, ClutterGstVideoSinkClass))

#define CLUTTER_GST_IS_VIDEO_SINK(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_VIDEO_SINK))

#define CLUTTER_GST_IS_VIDEO_SINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_VIDEO_SINK))

#define CLUTTER_GST_VIDEO_SINK_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_VIDEO_SINK, ClutterGstVideoSinkClass))

typedef struct _ClutterGstVideoSink ClutterGstVideoSink;
typedef struct _ClutterGstVideoSinkClass ClutterGstVideoSinkClass;
typedef struct _ClutterGstVideoSinkPrivate ClutterGstVideoSinkPrivate;

/**
 * ClutterGstVideoSink:
 *
 * The #ClutterGstVideoSink structure contains only private data and
 * should be accessed using the provided API.
 *
 * Since: 3.0
 */
struct _ClutterGstVideoSink
{
  /*< private >*/
  GstVideoSink parent;
  ClutterGstVideoSinkPrivate *priv;
};

/**
 * ClutterGstVideoSinkClass:
 * @new_frame: handler for the #ClutterGstVideoSink::new-frame signal
 * @pipeline_ready: handler for the #ClutterGstVideoSink::pipeline-ready signal
 *
 * Since: 3.0
 */
struct _ClutterGstVideoSinkClass
{
  /*< private >*/
  GstVideoSinkClass parent_class;

  /*< public >*/
  void (* new_frame)      (ClutterGstVideoSink *sink);
  void (* pipeline_ready) (ClutterGstVideoSink *sink);
  void (* new_overlays)   (ClutterGstVideoSink *sink);

  /*< private >*/
  void *_padding_dummy[8];
};


GType                 clutter_gst_video_sink_get_type       (void) G_GNUC_CONST;

ClutterGstVideoSink * clutter_gst_video_sink_new            (void);

gboolean              clutter_gst_video_sink_is_ready       (ClutterGstVideoSink *sink);

ClutterGstFrame *     clutter_gst_video_sink_get_frame      (ClutterGstVideoSink *sink);

CoglPipeline *        clutter_gst_video_sink_get_pipeline   (ClutterGstVideoSink *sink);

void                  clutter_gst_video_sink_setup_pipeline (ClutterGstVideoSink *sink,
                                                             CoglPipeline        *pipeline);

ClutterGstOverlays *  clutter_gst_video_sink_get_overlays   (ClutterGstVideoSink *sink);

G_END_DECLS

#endif
