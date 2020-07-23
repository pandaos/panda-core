#include "xdgautostart.h"
#include "xdgdirs.h"
#include <QStringList>
#include <QDebug>
#include <QSet>
#include <QDir>

/**
 * The Autostart Directories are $XDG_CONFIG_DIRS/autostart. If the same filename is
 * located under multiple Autostart Directories only the file under the most
 * important directory should be used.
 *
 * When multiple .desktop files with the same name exists in multiple directories
 * then only the Hidden key in the most important .desktop file must be considered:
 * If it is set to true all .desktop files with the same name in the other
 * directories MUST be ignored as well.
 */

XdgDesktopFileList XdgAutoStart::desktopFileList(bool excludeHidden)
{
    QStringList dirs;
    dirs << XdgDirs::autostartHome(false) << XdgDirs::autostartDirs();

    return desktopFileList(dirs, excludeHidden);
}

XdgDesktopFileList XdgAutoStart::desktopFileList(QStringList dirs, bool excludeHidden)
{
    dirs.removeDuplicates();

    QSet<QString> processed;
    XdgDesktopFileList ret;
    for (const QString &dirName : const_cast<const QStringList&>(dirs))
    {
        QDir dir(dirName);
        if (!dir.exists())
            continue;

        const QFileInfoList files = dir.entryInfoList(QStringList(QLatin1String("*.desktop")), QDir::Files | QDir::Readable);
        for (const QFileInfo &fi : files)
        {
            if (processed.contains(fi.fileName()))
                continue;

            processed << fi.fileName();

            XdgDesktopFile desktop;
            if (!desktop.load(fi.absoluteFilePath()))
                continue;

            if (!desktop.isSuitable(excludeHidden))
                continue;

            ret << desktop;
        }
    }
    return ret;
}

QString XdgAutoStart::localPath(const XdgDesktopFile& file)
{
    QFileInfo fi(file.fileName());
    return QString::fromLatin1("%1/%2").arg(XdgDirs::autostartHome(), fi.fileName());
}
