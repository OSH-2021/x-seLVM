
/* This file is generated by glib-mkenums, do not modify it. This code is licensed under the same license as the containing project. Note that it links to GLib, so must comply with the LGPL linking clauses. */

/*
 * Copyright (C) 2013 Igalia S.L.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#if !defined(__WEBKIT2_H_INSIDE__) && !defined(WEBKIT2_COMPILATION)
#error "Only <webkit2/webkit2.h> can be included directly."
#endif

#ifndef WEBKIT_ENUM_TYPES_H
#define WEBKIT_ENUM_TYPES_H

#include <glib-object.h>
#include <webkit2/WebKitDefines.h>

G_BEGIN_DECLS
/* Enumerations from WebKitAuthenticationRequest.h. */
#define WEBKIT_TYPE_AUTHENTICATION_SCHEME webkit_authentication_scheme_get_type ()

WEBKIT_API GType
webkit_authentication_scheme_get_type (void);
/* Enumerations from WebKitAutomationSession.h. */
#define WEBKIT_TYPE_AUTOMATION_BROWSING_CONTEXT_PRESENTATION webkit_automation_browsing_context_presentation_get_type ()

WEBKIT_API GType
webkit_automation_browsing_context_presentation_get_type (void);
/* Enumerations from WebKitContextMenuActions.h. */
#define WEBKIT_TYPE_CONTEXT_MENU_ACTION webkit_context_menu_action_get_type ()

WEBKIT_API GType
webkit_context_menu_action_get_type (void);
/* Enumerations from WebKitCookieManager.h. */
#define WEBKIT_TYPE_COOKIE_PERSISTENT_STORAGE webkit_cookie_persistent_storage_get_type ()

WEBKIT_API GType
webkit_cookie_persistent_storage_get_type (void);
#define WEBKIT_TYPE_COOKIE_ACCEPT_POLICY webkit_cookie_accept_policy_get_type ()

WEBKIT_API GType
webkit_cookie_accept_policy_get_type (void);
/* Enumerations from WebKitCredential.h. */
#define WEBKIT_TYPE_CREDENTIAL_PERSISTENCE webkit_credential_persistence_get_type ()

WEBKIT_API GType
webkit_credential_persistence_get_type (void);
/* Enumerations from WebKitEditorState.h. */
#define WEBKIT_TYPE_EDITOR_TYPING_ATTRIBUTES webkit_editor_typing_attributes_get_type ()

WEBKIT_API GType
webkit_editor_typing_attributes_get_type (void);
/* Enumerations from WebKitError.h. */
#define WEBKIT_TYPE_NETWORK_ERROR webkit_network_error_get_type ()

WEBKIT_API GType
webkit_network_error_get_type (void);
#define WEBKIT_TYPE_POLICY_ERROR webkit_policy_error_get_type ()

WEBKIT_API GType
webkit_policy_error_get_type (void);
#define WEBKIT_TYPE_PLUGIN_ERROR webkit_plugin_error_get_type ()

WEBKIT_API GType
webkit_plugin_error_get_type (void);
#define WEBKIT_TYPE_DOWNLOAD_ERROR webkit_download_error_get_type ()

WEBKIT_API GType
webkit_download_error_get_type (void);
#define WEBKIT_TYPE_PRINT_ERROR webkit_print_error_get_type ()

WEBKIT_API GType
webkit_print_error_get_type (void);
#define WEBKIT_TYPE_JAVASCRIPT_ERROR webkit_javascript_error_get_type ()

WEBKIT_API GType
webkit_javascript_error_get_type (void);
#define WEBKIT_TYPE_SNAPSHOT_ERROR webkit_snapshot_error_get_type ()

WEBKIT_API GType
webkit_snapshot_error_get_type (void);
#define WEBKIT_TYPE_USER_CONTENT_FILTER_ERROR webkit_user_content_filter_error_get_type ()

WEBKIT_API GType
webkit_user_content_filter_error_get_type (void);
/* Enumerations from WebKitFaviconDatabase.h. */
#define WEBKIT_TYPE_FAVICON_DATABASE_ERROR webkit_favicon_database_error_get_type ()

WEBKIT_API GType
webkit_favicon_database_error_get_type (void);
/* Enumerations from WebKitFindController.h. */
#define WEBKIT_TYPE_FIND_OPTIONS webkit_find_options_get_type ()

WEBKIT_API GType
webkit_find_options_get_type (void);
/* Enumerations from WebKitHitTestResult.h. */
#define WEBKIT_TYPE_HIT_TEST_RESULT_CONTEXT webkit_hit_test_result_context_get_type ()

WEBKIT_API GType
webkit_hit_test_result_context_get_type (void);
/* Enumerations from WebKitNavigationAction.h. */
#define WEBKIT_TYPE_NAVIGATION_TYPE webkit_navigation_type_get_type ()

WEBKIT_API GType
webkit_navigation_type_get_type (void);
/* Enumerations from WebKitNetworkProxySettings.h. */
#define WEBKIT_TYPE_NETWORK_PROXY_MODE webkit_network_proxy_mode_get_type ()

WEBKIT_API GType
webkit_network_proxy_mode_get_type (void);
/* Enumerations from WebKitPrintOperation.h. */
#define WEBKIT_TYPE_PRINT_OPERATION_RESPONSE webkit_print_operation_response_get_type ()

WEBKIT_API GType
webkit_print_operation_response_get_type (void);
/* Enumerations from WebKitScriptDialog.h. */
#define WEBKIT_TYPE_SCRIPT_DIALOG_TYPE webkit_script_dialog_type_get_type ()

WEBKIT_API GType
webkit_script_dialog_type_get_type (void);
/* Enumerations from WebKitSettings.h. */
#define WEBKIT_TYPE_HARDWARE_ACCELERATION_POLICY webkit_hardware_acceleration_policy_get_type ()

WEBKIT_API GType
webkit_hardware_acceleration_policy_get_type (void);
/* Enumerations from WebKitUserContent.h. */
#define WEBKIT_TYPE_USER_CONTENT_INJECTED_FRAMES webkit_user_content_injected_frames_get_type ()

WEBKIT_API GType
webkit_user_content_injected_frames_get_type (void);
#define WEBKIT_TYPE_USER_STYLE_LEVEL webkit_user_style_level_get_type ()

WEBKIT_API GType
webkit_user_style_level_get_type (void);
#define WEBKIT_TYPE_USER_SCRIPT_INJECTION_TIME webkit_user_script_injection_time_get_type ()

WEBKIT_API GType
webkit_user_script_injection_time_get_type (void);
/* Enumerations from WebKitUserMessage.h. */
#define WEBKIT_TYPE_USER_MESSAGE_ERROR webkit_user_message_error_get_type ()

WEBKIT_API GType
webkit_user_message_error_get_type (void);
/* Enumerations from WebKitWebContext.h. */
#define WEBKIT_TYPE_CACHE_MODEL webkit_cache_model_get_type ()

WEBKIT_API GType
webkit_cache_model_get_type (void);
#define WEBKIT_TYPE_PROCESS_MODEL webkit_process_model_get_type ()

WEBKIT_API GType
webkit_process_model_get_type (void);
/* Enumerations from WebKitWebView.h. */
#define WEBKIT_TYPE_POLICY_DECISION_TYPE webkit_policy_decision_type_get_type ()

WEBKIT_API GType
webkit_policy_decision_type_get_type (void);
#define WEBKIT_TYPE_LOAD_EVENT webkit_load_event_get_type ()

WEBKIT_API GType
webkit_load_event_get_type (void);
#define WEBKIT_TYPE_SAVE_MODE webkit_save_mode_get_type ()

WEBKIT_API GType
webkit_save_mode_get_type (void);
#define WEBKIT_TYPE_INSECURE_CONTENT_EVENT webkit_insecure_content_event_get_type ()

WEBKIT_API GType
webkit_insecure_content_event_get_type (void);
#define WEBKIT_TYPE_SNAPSHOT_OPTIONS webkit_snapshot_options_get_type ()

WEBKIT_API GType
webkit_snapshot_options_get_type (void);
#define WEBKIT_TYPE_SNAPSHOT_REGION webkit_snapshot_region_get_type ()

WEBKIT_API GType
webkit_snapshot_region_get_type (void);
#define WEBKIT_TYPE_WEB_PROCESS_TERMINATION_REASON webkit_web_process_termination_reason_get_type ()

WEBKIT_API GType
webkit_web_process_termination_reason_get_type (void);
/* Enumerations from WebKitWebsiteData.h. */
#define WEBKIT_TYPE_WEBSITE_DATA_TYPES webkit_website_data_types_get_type ()

WEBKIT_API GType
webkit_website_data_types_get_type (void);
/* Enumerations from WebKitWebsiteDataManager.h. */
#define WEBKIT_TYPE_TLS_ERRORS_POLICY webkit_tls_errors_policy_get_type ()

WEBKIT_API GType
webkit_tls_errors_policy_get_type (void);
/* Enumerations from WebKitWebsitePolicies.h. */
#define WEBKIT_TYPE_AUTOPLAY_POLICY webkit_autoplay_policy_get_type ()

WEBKIT_API GType
webkit_autoplay_policy_get_type (void);
/* Enumerations from WebKitInputMethodContext.h. */
#define WEBKIT_TYPE_INPUT_PURPOSE webkit_input_purpose_get_type ()

WEBKIT_API GType
webkit_input_purpose_get_type (void);
#define WEBKIT_TYPE_INPUT_HINTS webkit_input_hints_get_type ()

WEBKIT_API GType
webkit_input_hints_get_type (void);
G_END_DECLS

#endif

/* Generated data ends here */

