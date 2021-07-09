/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-camera-device.h - GObject representing a camera device using GStreamer.
 *
 * Authored By Andre Moreira Magalhaes <andre.magalhaes@collabora.co.uk>
 *
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
#error "Only <clutter-gst/clutter-gst.h> can be included directly."
#endif

#ifndef __CLUTTER_GST_CAMERA_DEVICE_H__
#define __CLUTTER_GST_CAMERA_DEVICE_H__

#include <glib-object.h>
#include <gst/gstelement.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_CAMERA_DEVICE clutter_gst_camera_device_get_type()

#define CLUTTER_GST_CAMERA_DEVICE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_CAMERA_DEVICE, ClutterGstCameraDevice))

#define CLUTTER_GST_CAMERA_DEVICE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_CAMERA_DEVICE, ClutterGstCameraDeviceClass))

#define CLUTTER_GST_IS_CAMERA_DEVICE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_CAMERA_DEVICE))

#define CLUTTER_GST_IS_CAMERA_DEVICE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_CAMERA_DEVICE))

#define CLUTTER_GST_CAMERA_DEVICE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_CAMERA_DEVICE, ClutterGstCameraDeviceClass))

typedef struct _ClutterGstCameraDevice        ClutterGstCameraDevice;
typedef struct _ClutterGstCameraDeviceClass   ClutterGstCameraDeviceClass;
typedef struct _ClutterGstCameraDevicePrivate ClutterGstCameraDevicePrivate;

/**
 * ClutterGstCameraDevice:
 *
 * GObject representing a camera device using GStreamer.
 *
 * The #ClutterGstCameraDevice structure contains only private data and
 * should not be accessed directly.
 */
struct _ClutterGstCameraDevice
{
  /*< private >*/
  GObject parent;
  ClutterGstCameraDevicePrivate *priv;
};

/**
 * ClutterGstCameraDeviceClass:
 *
 * Base class for #ClutterGstCameraDevice.
 */
struct _ClutterGstCameraDeviceClass
{
  /*< private >*/
  GObjectClass parent_class;

  void (* capture_resolution_changed) (ClutterGstCameraDevice *device,
                                       gint                    width,
                                       gint                    height);

  /* Future padding */
  void (* _clutter_reserved1) (void);
  void (* _clutter_reserved2) (void);
  void (* _clutter_reserved3) (void);
  void (* _clutter_reserved4) (void);
  void (* _clutter_reserved5) (void);
  void (* _clutter_reserved6) (void);
};

GType clutter_gst_camera_device_get_type (void) G_GNUC_CONST;

const gchar *      clutter_gst_camera_device_get_node                  (ClutterGstCameraDevice *device);
const gchar *      clutter_gst_camera_device_get_name                  (ClutterGstCameraDevice *device);

const GPtrArray *  clutter_gst_camera_device_get_supported_resolutions (ClutterGstCameraDevice *device);
void               clutter_gst_camera_device_get_capture_resolution    (ClutterGstCameraDevice *device,
                                                                        gint                   *width,
                                                                        gint                   *height);
void               clutter_gst_camera_device_set_capture_resolution    (ClutterGstCameraDevice *device,
                                                                        gint                    width,
                                                                        gint                    height);

G_END_DECLS

#endif /* __CLUTTER_GST_CAMERA_DEVICE_H__ */
