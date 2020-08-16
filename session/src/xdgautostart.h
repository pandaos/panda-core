/*
 * Copyright (C) 2020 PandaOS Team.
 *
 * Author:     revenmartin <revenmartin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QTXDG_XDGAUTOSTART_H
#define QTXDG_XDGAUTOSTART_H

#include "xdgmacros.h"
#include "xdgdesktopfile.h"
#include <QStringList>

/*! @brief The XdgAutoStart class implements the "Desktop Application Autostart Specification"
 * from freedesktop.org.
 * This specification defines a method for automatically starting applications during the startup
 * of a desktop environment and after mounting a removable medium.
 * Now we impliment only startup.
 *
 * @sa http://standards.freedesktop.org/autostart-spec/autostart-spec-latest.html
 */
class QTXDG_API XdgAutoStart
{
public:
    /*! Returns a list of XdgDesktopFile objects for all the .desktop files in the Autostart directories
        When the .desktop file has the Hidden key set to true, the .desktop file must be ignored. But you
        can change this behavior by setting excludeHidden to false. */
    static XdgDesktopFileList desktopFileList(bool excludeHidden=true);

    /*! Returns a list of XdgDesktopFile objects for .desktop files in the specified Autostart directories
        When the .desktop file has the Hidden key set to true, the .desktop file must be ignored. But you
        can change this behavior by setting excludeHidden to false. */
    static XdgDesktopFileList desktopFileList(QStringList dirs, bool excludeHidden=true);

    /// For XdgDesktopFile returns the file path of the same name in users personal autostart directory.
    static QString localPath(const XdgDesktopFile& file);
};

#endif // XDGAUTOSTART_H
