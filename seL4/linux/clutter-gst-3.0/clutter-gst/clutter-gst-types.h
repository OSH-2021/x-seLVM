/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-types.h - Clutter-Gst common types
 *
 * Authored By Lionel Landwerlin <lionel.g.landwerlin@linux.intel.com>
 *
 * Copyright (C) 2011 Intel Corporation
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
#error "Only <clutter-gst/clutter-gst.h> can be included directly."
#endif

#include <cogl/cogl.h>

#ifndef __CLUTTER_GST_TYPES_H__
#define __CLUTTER_GST_TYPES_H__

#define CLUTTER_GST_TYPE_FRAME            (clutter_gst_frame_get_type ())
#define CLUTTER_GST_TYPE_BOX              (clutter_gst_box_get_type ())
#define CLUTTER_GST_TYPE_OVERLAY          (clutter_gst_overlay_get_type ())
#define CLUTTER_GST_TYPE_OVERLAYS         (clutter_gst_overlays_get_type ())

typedef struct _ClutterGstBox             ClutterGstBox;
typedef struct _ClutterGstFrame           ClutterGstFrame;
typedef struct _ClutterGstOverlay         ClutterGstOverlay;
typedef struct _ClutterGstOverlays        ClutterGstOverlays;
typedef struct _ClutterGstVideoResolution ClutterGstVideoResolution;

/**
 * ClutterGstSeekFlags:
 * @CLUTTER_GST_SEEK_FLAG_NONE: Fast seeks (key frame boundaries, default)
 * @CLUTTER_GST_SEEK_FLAG_ACCURATE: Accurate seeks (potentially slower)
 *
 * Flags that can be given to clutter_gst_player_set_seek_flags().
 *
 * Since: 1.4
 */
typedef enum _ClutterGstSeekFlags
{
  CLUTTER_GST_SEEK_FLAG_NONE     = 0,
  CLUTTER_GST_SEEK_FLAG_ACCURATE = 1 << 0
} ClutterGstSeekFlags;

/**
 * ClutterGstBufferingMode:
 * @CLUTTER_GST_BUFFERING_MODE_STREAM: In-memory buffering
 * @CLUTTER_GST_BUFFERING_MODE_DOWNLOAD: On-disk buffering
 *
 * Different buffering policies clutter-gst supports
 *
 * Since: 1.4
 */
typedef enum _ClutterGstBufferingMode
{
  CLUTTER_GST_BUFFERING_MODE_STREAM,
  CLUTTER_GST_BUFFERING_MODE_DOWNLOAD
} ClutterGstBufferingMode;

/**
 * ClutterGstBox:
 * @x1: X coordinate of the top left corner
 * @y1: Y coordinate of the top left corner
 * @x2: X coordinate of the bottom right corner
 * @y2: Y coordinate of the bottom right corner
 *
 * Bounding box of an area in a video texture or actor's allocation.
 * Coordinates are usually expressed in the [0, 1] interval.
 *
 * Since: 3.0
 */
struct _ClutterGstBox
{
  gfloat x1;
  gfloat y1;

  gfloat x2;
  gfloat y2;
};

/**
 * ClutterGstVideoResolution:
 * @width: the width, in pixels
 * @height: the height, in pixels
 *
 * A video resolution.
 *
 * Since: 3.0
 */
struct _ClutterGstVideoResolution
{
  gint width;
  gint height;

  gint par_n;
  gint par_d;
};

/**
 * ClutterGstFrame:
 * @resolution: a #ClutterGstVideoResolution
 * @pipeline: a #CoglPipeline to paint a frame
 *
 * Represents a frame outputted by the #ClutterGstVideoSink.
 *
 * Since: 3.0
 */
struct _ClutterGstFrame
{
  ClutterGstVideoResolution  resolution;
  CoglPipeline              *pipeline;
};

/**
 * ClutterGstOverlay:
 * @position: a #ClutterGstBox representing the position of the
 *            overlay within a #ClutterGstFrame.
 * @pipeline: a #CoglPipeline to paint an overlay
 *
 * Represents a video overlay outputted by the #ClutterGstVideoSink.
 *
 * Since: 3.0
 */
struct _ClutterGstOverlay
{
  ClutterGstBox  position;
  CoglPipeline  *pipeline;
};

/**
 * ClutterGstOverlays:
 * @overlays: an array of #ClutterGstOverlay
 *
 * Since: 3.0
 */
struct _ClutterGstOverlays
{
  GPtrArray *overlays;
};

GType clutter_gst_frame_get_type     (void) G_GNUC_CONST;
GType clutter_gst_box_get_type       (void) G_GNUC_CONST;
GType clutter_gst_overlay_get_type   (void) G_GNUC_CONST;
GType clutter_gst_overlays_get_type  (void) G_GNUC_CONST;

gfloat clutter_gst_box_get_width     (const ClutterGstBox *box);
gfloat clutter_gst_box_get_height    (const ClutterGstBox *box);

#endif /* __CLUTTER_GST_TYPES_H__ */
