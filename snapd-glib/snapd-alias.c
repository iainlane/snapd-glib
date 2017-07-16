/*
 * Copyright (C) 2017 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#include "config.h"

#include "snapd-alias.h"
#include "snapd-enum-types.h"

/**
 * SECTION: snapd-alias
 * @short_description: App aliases.
 * @include: snapd-glib/snapd-glib.h
 *
 * A #SnapdAlias represents an optional alias that can be used for an app.
 * Aliases can be queried using snapd_client_get_aliases_sync() and are used in
 * snapd_client_enable_aliases_sync(), snapd_client_disable_aliases_sync() and
 * snapd_client_reset_aliases_sync().
 */

/**
 * SnapdAlias:
 *
 * #SnapdAlias is an opaque data structure and can only be accessed
 * using the provided functions.
 *
 * Since: 1.8
 */

struct _SnapdAlias
{
    GObject parent_instance;

    gchar *app;
    gchar *command;
    gchar *name;
    gchar *snap;
    gchar *auto_target;
    gchar *manual_target;
    SnapdAliasStatus status;
};

enum
{
    PROP_APP = 1,
    PROP_NAME,
    PROP_SNAP,
    PROP_STATUS,
    PROP_COMMAND,
    PROP_AUTO_TARGET,
    PROP_MANUAL_TARGET,
    PROP_LAST
};

G_DEFINE_TYPE (SnapdAlias, snapd_alias, G_TYPE_OBJECT)

/**
 * snapd_alias_get_app:
 * @alias: a #SnapdAlias.
 *
 * Get the app this is an alias for.
 *
 * Returns: an app name.
 *
 * Since: 1.8
 * Deprecated: 1.16: Use snapd_alias_get_manual_target() or snapd_alias_get_auto_target().
 */
const gchar *
snapd_alias_get_app (SnapdAlias *alias)
{
    g_return_val_if_fail (SNAPD_IS_ALIAS (alias), NULL);
    return alias->app;
}

/**
 * snapd_alias_get_auto_target:
 * @alias: a #SnapdAlias.
 *
 * Get the automatic target this alias is for.
 *
 * Returns: (allow-none): a snap name or %NULL.
 *
 * Since: 1.16
 */
const gchar *
snapd_alias_get_auto_target (SnapdAlias *alias)
{
    g_return_val_if_fail (SNAPD_IS_ALIAS (alias), NULL);
    return alias->auto_target;
}

/**
 * snapd_alias_get_command:
 * @alias: a #SnapdAlias.
 *
 * Get the command this alias runs.
 *
 * Returns: a command.
 *
 * Since: 1.16
 */
const gchar *
snapd_alias_get_command (SnapdAlias *alias)
{
    g_return_val_if_fail (SNAPD_IS_ALIAS (alias), NULL);
    return alias->command;
}

/**
 * snapd_alias_get_manual_target:
 * @alias: a #SnapdAlias.
 *
 * Get the manual target this alias is for.
 *
 * Returns: (allow-none): a snap name or %NULL.
 *
 * Since: 1.16
 */
const gchar *
snapd_alias_get_manual_target (SnapdAlias *alias)
{
    g_return_val_if_fail (SNAPD_IS_ALIAS (alias), NULL);
    return alias->manual_target;
}

/**
 * snapd_alias_get_name:
 * @alias: a #SnapdAlias.
 *
 * Get the name of this alias.
 *
 * Returns: an alias name.
 *
 * Since: 1.8
 */
const gchar *
snapd_alias_get_name (SnapdAlias *alias)
{
    g_return_val_if_fail (SNAPD_IS_ALIAS (alias), NULL);
    return alias->name;
}

/**
 * snapd_alias_get_snap:
 * @alias: a #SnapdAlias.
 *
 * Get the snap this alias is for.
 *
 * Returns: a snap name.
 *
 * Since: 1.8
 */
const gchar *
snapd_alias_get_snap (SnapdAlias *alias)
{
    g_return_val_if_fail (SNAPD_IS_ALIAS (alias), NULL);
    return alias->snap;
}

/**
 * snapd_alias_get_status:
 * @alias: a #SnapdAlias.
 *
 * Get the status of this alias.
 *
 * Return: a #SnapdAliasStatus.
 *
 * Since: 1.8
 */
SnapdAliasStatus
snapd_alias_get_status (SnapdAlias *alias)
{
    g_return_val_if_fail (SNAPD_IS_ALIAS (alias), SNAPD_ALIAS_STATUS_UNKNOWN);
    return alias->status;
}

static void
snapd_alias_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
    SnapdAlias *alias = SNAPD_ALIAS (object);

    switch (prop_id) {
    case PROP_APP:
        g_free (alias->app);
        alias->app = g_strdup (g_value_get_string (value));
        break;
    case PROP_AUTO_TARGET:
        g_free (alias->auto_target);
        alias->auto_target = g_strdup (g_value_get_string (value));
        break;
    case PROP_COMMAND:
        g_free (alias->command);
        alias->command = g_strdup (g_value_get_string (value));
        break;
    case PROP_MANUAL_TARGET:
        g_free (alias->manual_target);
        alias->manual_target = g_strdup (g_value_get_string (value));
        break;
    case PROP_NAME:
        g_free (alias->name);
        alias->name = g_strdup (g_value_get_string (value));
        break;
    case PROP_SNAP:
        g_free (alias->snap);
        alias->snap = g_strdup (g_value_get_string (value));
        break;
    case PROP_STATUS:
        alias->status = g_value_get_enum (value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
snapd_alias_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
    SnapdAlias *alias = SNAPD_ALIAS (object);

    switch (prop_id) {
    case PROP_APP:
        g_value_set_string (value, alias->app);
        break;
    case PROP_AUTO_TARGET:
        g_value_set_string (value, alias->auto_target);
        break;
    case PROP_COMMAND:
        g_value_set_string (value, alias->command);
        break;
    case PROP_MANUAL_TARGET:
        g_value_set_string (value, alias->manual_target);
        break;
    case PROP_NAME:
        g_value_set_string (value, alias->name);
        break;
    case PROP_SNAP:
        g_value_set_string (value, alias->snap);
        break;
    case PROP_STATUS:
        g_value_set_enum (value, alias->status);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
snapd_alias_finalize (GObject *object)
{
    SnapdAlias *alias = SNAPD_ALIAS (object);

    g_clear_pointer (&alias->app, g_free);
    g_clear_pointer (&alias->auto_target, g_free);
    g_clear_pointer (&alias->command, g_free);
    g_clear_pointer (&alias->manual_target, g_free);
    g_clear_pointer (&alias->name, g_free);
    g_clear_pointer (&alias->snap, g_free);
}

static void
snapd_alias_class_init (SnapdAliasClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

    gobject_class->set_property = snapd_alias_set_property;
    gobject_class->get_property = snapd_alias_get_property;
    gobject_class->finalize = snapd_alias_finalize;

    g_object_class_install_property (gobject_class,
                                     PROP_APP,
                                     g_param_spec_string ("app",
                                                          "app",
                                                          "App this alias is for",
                                                          NULL,
                                                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

    g_object_class_install_property (gobject_class,
                                     PROP_AUTO_TARGET,
                                     g_param_spec_string ("auto-target",
                                                          "auto-target",
                                                          "Automatic target for this alias",
                                                          NULL,
                                                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

    g_object_class_install_property (gobject_class,
                                     PROP_COMMAND,
                                     g_param_spec_string ("command",
                                                          "command",
                                                          "Command this alias runs",
                                                          NULL,
                                                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

    g_object_class_install_property (gobject_class,
                                     PROP_MANUAL_TARGET,
                                     g_param_spec_string ("manual-target",
                                                          "manual-target",
                                                          "Manual target for this alias",
                                                          NULL,
                                                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

    g_object_class_install_property (gobject_class,
                                     PROP_NAME,
                                     g_param_spec_string ("name",
                                                          "name",
                                                          "Name of alias",
                                                          NULL,
                                                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

    g_object_class_install_property (gobject_class,
                                     PROP_SNAP,
                                     g_param_spec_string ("snap",
                                                          "snap",
                                                          "Snap this alias is for",
                                                          NULL,
                                                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

    g_object_class_install_property (gobject_class,
                                     PROP_STATUS,
                                     g_param_spec_enum ("status",
                                                        "status",
                                                        "Alias status",
                                                        SNAPD_TYPE_ALIAS_STATUS, SNAPD_ALIAS_STATUS_UNKNOWN,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
}

static void
snapd_alias_init (SnapdAlias *alias)
{
}
