/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2009-12-23
 * Description : Autodetect enfuse binary program and version
 *
 * Copyright (C) 2009 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef ENFUSEBINARY_H
#define ENFUSEBINARY_H

// Qt includes

#include <QString>

// KDE includes

#include <kurl.h>

namespace KIPIExpoBlendingPlugin
{

class EnfuseBinaryPriv;

class EnfuseBinary
{

public:

    EnfuseBinary();
    ~EnfuseBinary();

    static const char* path();
    bool               isAvailable()    const;
    QString            version()        const;
    bool               versionIsRight() const;
    QString            minimalVersion() const;
    KUrl               url()            const;

    void               checkSystem();

private:

    EnfuseBinaryPriv* const d;
};

} // namespace KIPIExpoBlendingPlugin

#endif  // ENFUSEBINARY_H