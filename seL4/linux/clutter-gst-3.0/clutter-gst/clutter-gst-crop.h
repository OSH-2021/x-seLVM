/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-aspectratio.c - An actor rendering a video with respect
 * to its aspect ratio.
 *
 * Authored by Lionel Landwerlin <lionel.g.landwerlin@linux.intel.com>
 *
 * Copyright (C) 2013 Intel Corporation
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

#ifndef __CLUTTER_GST_CROP_H__
#define __CLUTTER_GST_CROP_H__

#include <glib-object.h>

#include <clutter-gst/clutter-gst-content.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_CROP clutter_gst_crop_get_type()

#define CLUTTER_GST_CROP(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_CROP, ClutterGstCrop))

#define CLUTTER_GST_CROP_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_CROP, ClutterGstCropClass))

#define CLUTTER_GST_IS_CROP(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_CROP))

#define CLUTTER_GST_IS_CROP_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_CROP))

#define CLUTTER_GST_CROP_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_CROP, ClutterGstCropClass))

typedef struct _ClutterGstCrop ClutterGstCrop;
typedef struct _ClutterGstCropClass ClutterGstCropClass;
typedef struct _ClutterGstCropPrivate ClutterGstCropPrivate;

/**
 * ClutterGstCrop:
 *
 * Implementation of #ClutterGstContent that displays a sub region of
 * video streams.
 *
 * The #ClutterGstCrop structure contains only private data and
 * should not be accessed directly.
 */
struct _ClutterGstCrop
{
  /*< private >*/
  ClutterGstContent parent;

  ClutterGstCropPrivate *priv;
};

/**
 * ClutterGstCropClass:
 *
 * Base class for #ClutterGstCrop.
 */
struct _ClutterGstCropClass
{
  /*< private >*/
  ClutterGstContentClass parent_class;

  void *_padding_dummy[8];
};

GType clutter_gst_crop_get_type (void) G_GNUC_CONST;

ClutterActor *clutter_gst_crop_new (void);

G_END_DECLS

#endif /* __CLUTTER_GST_CROP_H__ */
