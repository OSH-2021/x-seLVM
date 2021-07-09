/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-aspectratio.c - An object implementing the
 * ClutterContent interface to render a video with respect to its
 * aspect ratio.
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

#ifndef __CLUTTER_GST_ASPECTRATIO_H__
#define __CLUTTER_GST_ASPECTRATIO_H__

#include <glib-object.h>

#include <clutter-gst/clutter-gst-content.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_ASPECTRATIO clutter_gst_aspectratio_get_type()

#define CLUTTER_GST_ASPECTRATIO(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_ASPECTRATIO, ClutterGstAspectratio))

#define CLUTTER_GST_ASPECTRATIO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_ASPECTRATIO, ClutterGstAspectratioClass))

#define CLUTTER_GST_IS_ASPECTRATIO(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_ASPECTRATIO))

#define CLUTTER_GST_IS_ASPECTRATIO_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_ASPECTRATIO))

#define CLUTTER_GST_ASPECTRATIO_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_ASPECTRATIO, ClutterGstAspectratioClass))

typedef struct _ClutterGstAspectratio ClutterGstAspectratio;
typedef struct _ClutterGstAspectratioClass ClutterGstAspectratioClass;
typedef struct _ClutterGstAspectratioPrivate ClutterGstAspectratioPrivate;

/**
 * ClutterGstAspectratio:
 *
 * Implementation of #ClutterGstContent that displays video streams
 * with respects to their aspect ratio.
 *
 * The #ClutterGstAspectratio structure contains only private data and
 * should not be accessed directly.
 */
struct _ClutterGstAspectratio
{
  /*< private >*/
  ClutterGstContent parent;

  ClutterGstAspectratioPrivate *priv;
};

/**
 * ClutterGstAspectratioClass:
 *
 * Base class for #ClutterGstAspectratio.
 */
struct _ClutterGstAspectratioClass
{
  /*< private >*/
  ClutterGstContentClass parent_class;

  void *_padding_dummy[8];
};

GType clutter_gst_aspectratio_get_type (void) G_GNUC_CONST;

ClutterContent *clutter_gst_aspectratio_new (void);

G_END_DECLS

#endif /* __CLUTTER_GST_ASPECTRATIO_H__ */
