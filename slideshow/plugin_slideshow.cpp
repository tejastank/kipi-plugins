/* ============================================================
 * File  : plugin_slideshow.cpp
 * Author: Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Date  : 2003-01-31
 * Description :
 *
 * Copyright 2003 by Renchi Raju

 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published bythe Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

 // KDE includes.
 
#include <klocale.h>
#include <kaction.h>
#include <kgenericfactory.h>
#include <klibloader.h>
#include <kconfig.h>
#include <kdebug.h>
#include <kmessagebox.h>

// Local includes.

#include "slideshow.h"
#include "slideshowgl.h"
#include "slideshowconfig.h"
#include "plugin_slideshow.h"

// Lib KIPI includes.

#include <libkipi/interface.h>
#include <libkipi/imagecollection.h>

typedef KGenericFactory<Plugin_SlideShow> Factory;

K_EXPORT_COMPONENT_FACTORY( kipiplugin_slideshow,
                            Factory("kipiplugin_slideshow"));

Plugin_SlideShow::Plugin_SlideShow(QObject *parent,
                                   const char*,
                                   const QStringList&)
    : KIPI::Plugin( Factory::instance(), parent, "SlideShow")
{
    kdDebug( 51001 ) << "Plugin_SlideShow plugin loaded"
                     << endl;
}

void Plugin_SlideShow::setup( QWidget* widget )
{
    KIPI::Plugin::setup( widget );
    
    m_actionSlideShow = new KAction (i18n("SlideShow..."),
                                     "slideshow",
                                     0,
                                     this,
                                     SLOT(slotActivate()),
                                     actionCollection(),
                                     "slideshow");

    KIPI::Interface* interface = dynamic_cast< KIPI::Interface* >( parent() );
    
    if ( !interface ) 
       {
       kdError( 51000 ) << "Kipi interface is null!" << endl;
       return;
       }

    KIPI::ImageCollection images = interface->currentScope();
    m_actionSlideShow->setEnabled( images.isValid() );
    
    connect( interface, SIGNAL( currentAlbumChanged( bool ) ),
             m_actionSlideShow, SLOT( setEnabled( bool ) ) );

    addAction( m_actionSlideShow );
}


Plugin_SlideShow::~Plugin_SlideShow()
{
}


void Plugin_SlideShow::slotActivate()
{
    KIPISlideShowPlugin::SlideShowConfig *slideShowConfig = new KIPISlideShowPlugin::SlideShowConfig;
    
    connect(slideShowConfig, SIGNAL(okClicked()),
            this, SLOT(slotSlideShow()));

    slideShowConfig->show();
}



void Plugin_SlideShow::slotSlideShow()
{
    KIPI::Interface* interface = dynamic_cast<KIPI::Interface*>( parent() );

    if ( !interface ) 
           {
           kdError( 51000 ) << "Kipi interface is null!" << endl;
           return;
           }
           
    KConfig config("kipirc");

    bool    opengl;
    int     delay;
    bool    printFileName;
    bool    loop;
    bool    showSelectedFilesOnly;
    QString effectName;

    config.setGroup("SlideShow Settings");
    opengl                = config.readBoolEntry("OpenGL");
    delay                 = config.readNumEntry("Delay");
    printFileName         = config.readBoolEntry("Print Filename");
    loop                  = config.readBoolEntry("Loop");
    showSelectedFilesOnly = config.readBoolEntry("Show Selected Files Only");
    if (!opengl)
        effectName        = config.readEntry("Effect Name");
    else
        effectName        = config.readEntry("Effect Name (OpenGL)");

    KIPI::ImageCollection images;
    if (showSelectedFilesOnly)
        images = interface->currentSelection();
    else
        images = interface->currentAlbum();
    if ( !images.isValid() )
        return;

    KURL::List urlList = images.images();

    // PENDING(blackie) handle real URLS
    QStringList fileList;
    
    for( KURL::List::Iterator urlIt = urlList.begin(); urlIt != urlList.end(); ++urlIt ) {
        fileList.append( (*urlIt).path() );
    }

    if (!opengl) {
        KIPISlideShowPlugin::SlideShow *slideShow =
            new KIPISlideShowPlugin::SlideShow(fileList, delay, printFileName,
                          loop, effectName);
        slideShow->show();
    }
    else {
        if (!QGLFormat::hasOpenGL())
            KMessageBox::error(0, i18n("Sorry. OpenGL support not available on your system"));
        else {
            KIPISlideShowPlugin::SlideShowGL *slideShow =
                new KIPISlideShowPlugin::SlideShowGL(fileList, delay, loop, effectName);
            slideShow->show();
        }
    }
}

KIPI::Category Plugin_SlideShow::category( KAction* action ) const
{
    if ( action == m_actionSlideShow )
       return KIPI::TOOLSPLUGIN;
    
    kdWarning( 51000 ) << "Unrecognized action for plugin category identification" << endl;
    return KIPI::TOOLSPLUGIN; // no warning from compiler, please
}


#include "plugin_slideshow.moc"
