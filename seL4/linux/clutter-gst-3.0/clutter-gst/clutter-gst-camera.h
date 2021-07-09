/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-camera-actor.h - ClutterActor using GStreamer to display/manipulate a
 *                              camera stream.
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

#ifndef __CLUTTER_GST_CAMERA_H__
#define __CLUTTER_GST_CAMERA_H__

#include <clutter/clutter.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib-object.h>
#include <gst/gstelement.h>
#include <gst/pbutils/encoding-profile.h>

#include <clutter-gst/clutter-gst-camera-device.h>
#include <clutter-gst/clutter-gst-types.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_CAMERA clutter_gst_camera_get_type()

#define CLUTTER_GST_CAMERA(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_CAMERA, ClutterGstCamera))

#define CLUTTER_GST_CAMERA_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_CAMERA, ClutterGstCameraClass))

#define CLUTTER_GST_IS_CAMERA(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_CAMERA))

#define CLUTTER_GST_IS_CAMERA_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_CAMERA))

#define CLUTTER_GST_CAMERA_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_CAMERA, ClutterGstCameraClass))

typedef struct _ClutterGstCamera        ClutterGstCamera;
typedef struct _ClutterGstCameraClass   ClutterGstCameraClass;
typedef struct _ClutterGstCameraPrivate ClutterGstCameraPrivate;

/**
 * ClutterGstCamera:
 *
 * Implementation of #ClutterGstPlayer that displays camera streams
 * using GStreamer.
 *
 * The #ClutterGstCamera structure contains only private data and
 * should not be accessed directly.
 */
struct _ClutterGstCamera
{
  /*< private >*/
  GObject parent;
  ClutterGstCameraPrivate *priv;
};

/**
 * ClutterGstCameraClass:
 *
 * Base class for #ClutterGstCamera.
 */
struct _ClutterGstCameraClass
{
  /*< private >*/
  GObjectClass parent_class;

  void (* ready_for_capture) (ClutterGstCamera *self,
                              gboolean               ready);
  void (* photo_saved)       (ClutterGstCamera *self);
  void (* photo_taken)       (ClutterGstCamera *self,
                              GdkPixbuf             *pixbuf);
  void (* video_saved)       (ClutterGstCamera *self);

  /* Future padding */
  void (* _clutter_reserved1) (void);
  void (* _clutter_reserved2) (void);
  void (* _clutter_reserved3) (void);
  void (* _clutter_reserved4) (void);
  void (* _clutter_reserved5) (void);
  void (* _clutter_reserved6) (void);
};

GType clutter_gst_camera_get_type (void) G_GNUC_CONST;

ClutterGstCamera * clutter_gst_camera_new                   (void);

ClutterGstCameraDevice *
               clutter_gst_camera_get_camera_device     (ClutterGstCamera   *self);
gboolean       clutter_gst_camera_set_camera_device     (ClutterGstCamera       *self,
                                                         ClutterGstCameraDevice *device);

gboolean       clutter_gst_camera_supports_gamma_correction
                                                        (ClutterGstCamera   *self);
gboolean       clutter_gst_camera_get_gamma_range       (ClutterGstCamera   *self,
                                                         gdouble            *min_value,
                                                         gdouble            *max_value,
                                                         gdouble            *default_value);
gboolean       clutter_gst_camera_get_gamma             (ClutterGstCamera   *self,
                                                         gdouble            *cur_value);
gboolean       clutter_gst_camera_set_gamma             (ClutterGstCamera   *self,
                                                         gdouble             value);

gboolean       clutter_gst_camera_supports_color_balance
                                                        (ClutterGstCamera   *self);
gboolean       clutter_gst_camera_get_color_balance_property_range
                                                        (ClutterGstCamera   *self,
                                                         const gchar        *property,
                                                         gdouble            *min_value,
                                                         gdouble            *max_value,
                                                         gdouble            *default_value);
gboolean       clutter_gst_camera_get_color_balance_property
                                                        (ClutterGstCamera   *self,
                                                         const gchar        *property,
                                                         gdouble            *cur_value);
gboolean       clutter_gst_camera_set_color_balance_property
                                                        (ClutterGstCamera   *self,
                                                         const gchar        *property,
                                                         gdouble             value);
gboolean       clutter_gst_camera_get_brightness_range  (ClutterGstCamera   *self,
                                                         gdouble            *min_value,
                                                         gdouble            *max_value,
                                                         gdouble            *default_value);
gboolean       clutter_gst_camera_get_brightness        (ClutterGstCamera   *self,
                                                         gdouble            *cur_value);
gboolean       clutter_gst_camera_set_brightness        (ClutterGstCamera   *self,
                                                         gdouble             value);
gboolean       clutter_gst_camera_get_contrast_range    (ClutterGstCamera   *self,
                                                         gdouble            *min_value,
                                                         gdouble            *max_value,
                                                         gdouble            *default_value);
gboolean       clutter_gst_camera_get_contrast          (ClutterGstCamera   *self,
                                                         gdouble            *cur_value);
gboolean       clutter_gst_camera_set_contrast          (ClutterGstCamera   *self,
                                                         gdouble             value);
gboolean       clutter_gst_camera_get_saturation_range  (ClutterGstCamera   *self,
                                                         gdouble            *min_value,
                                                         gdouble            *max_value,
                                                         gdouble            *default_value);
gboolean       clutter_gst_camera_get_saturation        (ClutterGstCamera   *self,
                                                         gdouble            *cur_value);
gboolean       clutter_gst_camera_set_saturation        (ClutterGstCamera   *self,
                                                         gdouble             value);
gboolean       clutter_gst_camera_get_hue_range         (ClutterGstCamera   *self,
                                                         gdouble            *min_value,
                                                         gdouble            *max_value,
                                                         gdouble            *default_value);
gboolean       clutter_gst_camera_get_hue               (ClutterGstCamera   *self,
                                                         gdouble            *cur_value);
gboolean       clutter_gst_camera_set_hue               (ClutterGstCamera   *self,
                                                         gdouble             value);

GstElement *   clutter_gst_camera_get_filter            (ClutterGstCamera   *self);
gboolean       clutter_gst_camera_set_filter            (ClutterGstCamera   *self,
                                                         GstElement         *filter);
gboolean       clutter_gst_camera_remove_filter         (ClutterGstCamera   *self);

gboolean       clutter_gst_camera_is_ready_for_capture  (ClutterGstCamera   *self);

void           clutter_gst_camera_set_video_profile     (ClutterGstCamera   *self,
                                                         GstEncodingProfile *profile);
gboolean       clutter_gst_camera_is_recording_video    (ClutterGstCamera   *self);
gboolean       clutter_gst_camera_start_video_recording (ClutterGstCamera   *self,
                                                               const gchar  *filename);
void           clutter_gst_camera_stop_video_recording  (ClutterGstCamera   *self);

void           clutter_gst_camera_set_photo_profile     (ClutterGstCamera   *self,
                                                         GstEncodingProfile *profile);
gboolean       clutter_gst_camera_take_photo            (ClutterGstCamera   *self,
                                                         const gchar        *filename);
gboolean       clutter_gst_camera_take_photo_pixbuf     (ClutterGstCamera   *self);

G_END_DECLS

#endif /* __CLUTTER_GST_CAMERA_H__ */
