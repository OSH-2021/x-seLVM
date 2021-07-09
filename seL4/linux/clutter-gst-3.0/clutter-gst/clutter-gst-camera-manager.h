/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-camera-manager.h - a component to list available cameras
 *
 * Authored By Lionel Landwerlin <lionel.g.landwerlin@linux.intel.com>
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

#ifndef __CLUTTER_GST_CAMERA_MANAGER_H__
#define __CLUTTER_GST_CAMERA_MANAGER_H__

#if !defined(__CLUTTER_GST_H_INSIDE__) && !defined(CLUTTER_GST_COMPILATION)
#error "Only <clutter-gst/clutter-gst.h> can be included directly."
#endif

#include <glib-object.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_CAMERA_MANAGER clutter_gst_camera_manager_get_type()

#define CLUTTER_GST_CAMERA_MANAGER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_CAMERA_MANAGER, ClutterGstCameraManager))

#define CLUTTER_GST_CAMERA_MANAGER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_CAMERA_MANAGER, ClutterGstCameraManagerClass))

#define CLUTTER_GST_IS_CAMERA_MANAGER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_CAMERA_MANAGER))

#define CLUTTER_GST_IS_CAMERA_MANAGER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_CAMERA_MANAGER))

#define CLUTTER_GST_CAMERA_MANAGER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_CAMERA_MANAGER, ClutterGstCameraManagerClass))

typedef struct _ClutterGstCameraManager ClutterGstCameraManager;
typedef struct _ClutterGstCameraManagerClass ClutterGstCameraManagerClass;
typedef struct _ClutterGstCameraManagerPrivate ClutterGstCameraManagerPrivate;

/**
 * ClutterGstCameraManager:
 *
 * An object to list available cameras on the system.
 *
 * The #ClutterGstCameraManager structure contains only private data and
 * should not be accessed directly.
 */
struct _ClutterGstCameraManager
{
  /*< private >*/
  GObject parent;

  ClutterGstCameraManagerPrivate *priv;
};

/**
 * ClutterGstCameraManagerClass:
 *
 * Base class for #ClutterGstCamera.
 */
struct _ClutterGstCameraManagerClass
{
  /*< private >*/
  GObjectClass parent_class;
};

GType clutter_gst_camera_manager_get_type (void) G_GNUC_CONST;

ClutterGstCameraManager *clutter_gst_camera_manager_get_default (void);

const GPtrArray *clutter_gst_camera_manager_get_camera_devices (ClutterGstCameraManager *self);

G_END_DECLS

#endif /* __CLUTTER_GST_CAMERA_MANAGER_H__ */
