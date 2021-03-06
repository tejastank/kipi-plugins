/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2011-05-23
 * Description : Autodetect autooptimiser binary program and version
 *
 * Copyright (C) 2011-2012 by Benjamin Girault <benjamin dot girault at gmail dot com>
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

#ifndef AUTOOPTIMISERBINARY_H
#define AUTOOPTIMISERBINARY_H

// Local includes

#include "kpbinaryiface.h"

using namespace KIPIPlugins;

namespace KIPIPanoramaPlugin
{

class AutoOptimiserBinary : public KPBinaryIface
{

public:

    AutoOptimiserBinary()
        : KPBinaryIface(QString("autooptimiser"), 
                        QString("2010.4"), 
                        QString("autooptimiser version "),
                        1, 
                        QString("Hugin"), 
                        QString("http://hugin.sourceforge.net"), 
                        QString("Panorama")
                       )
        { 
            setup();
        }

    ~AutoOptimiserBinary()
    {
    }
};

} // namespace KIPIPanoramaPlugin

#endif  // AUTOOPTIMISERBINARY_H
