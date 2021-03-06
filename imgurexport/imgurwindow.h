/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2012-02-12
 * Description : a kipi plugin to export images to the Imgur web service
 *
 * Copyright (C) 2010-2012 by Marius Orcsik <marius at habarnam dot ro>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef IMGURWINDOW_H
#define IMGURWINDOW_H

// Qt includes

#include <QObject>

// LibKIPI includes

#include <libkipi/interface.h>

// Local includes

#include "kpimageslist.h"
#include "imgurtalker.h"
#include "imgurwidget.h"
#include "kptooldialog.h"

namespace KIPIPlugins
{
    class KPImagesList;
}

namespace KIPI
{
    class Interface;
}

using namespace KIPI;
using namespace KIPIPlugins;

namespace KIPIImgurExportPlugin
{

class ImgurWindow : public KPToolDialog
{
    Q_OBJECT

public:

    ImgurWindow(QWidget* const parent = 0);
    ~ImgurWindow();

    using KDialog::slotButtonClicked;

    void reactivate();

public Q_SLOTS:

    void slotImageQueueChanged();
    void slotStartUpload();
    void slotBusy(bool val);

    void slotButtonClicked(KDialog::ButtonCode button);
    void slotAddPhotoSuccess(ImgurSuccess success);
    void slotAddPhotoError(ImgurError error);

Q_SIGNALS:

    void signalImageUploadSuccess(const KUrl&, ImgurSuccess);
    void signalImageUploadError(const KUrl&, ImgurError);

private:

    void uploadNextItem();
    void closeEvent(QCloseEvent* e);
    void close();
    void readSettings();
    void saveSettings();

private:

    class ImgurWindowPriv;
    ImgurWindowPriv* const d;
};

} // namespace KIPIImgurExportPlugin

#endif /* IMGURWINDOW_H */
