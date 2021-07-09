#pragma once

#if !defined(__CLUTTER_H_INSIDE__) && !defined(CLUTTER_COMPILATION)
#error "Only <clutter/clutter.h> can be included directly."
#endif

#include <glib.h>

G_BEGIN_DECLS


#define CLUTTER_HAS_WAYLAND_COMPOSITOR_SUPPORT 1
#define CLUTTER_WINDOWING_X11 "x11"
#define CLUTTER_INPUT_X11 "x11"
#define CLUTTER_WINDOWING_GDK "gdk"
#define CLUTTER_INPUT_GDK "gdk"
#define CLUTTER_WINDOWING_GLX "glx"
#define CLUTTER_WINDOWING_EGL "eglnative"
#define CLUTTER_WINDOWING_WAYLAND "wayland"
#define CLUTTER_INPUT_EVDEV "evdev"
#define CLUTTER_INPUT_WAYLAND "wayland"
#define CLUTTER_INPUT_NULL "null"

G_END_DECLS
