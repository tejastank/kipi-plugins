SUBDIRS(icons)

SET(kipiplugin_imageshackexport_PART_SRCS
    plugin_imageshackexport.cpp
    imageshack.cpp
    imageshackwindow.cpp
    imageshackwidget.cpp
    imageshacktalker.cpp
    mpform.cpp
   )

KDE4_ADD_PLUGIN(kipiplugin_imageshackexport ${kipiplugin_imageshackexport_PART_SRCS})

TARGET_LINK_LIBRARIES(kipiplugin_imageshackexport
                      ${KDCRAW_LIBRARIES}
                      ${KIPI_LIBRARIES}
                      ${KEXIV2_LIBRARIES}
                      ${KDE4_KIO_LIBS}
                      ${KDE4_KDEUI_LIBS}
                      kipiplugins
                     )

INSTALL(TARGETS kipiplugin_imageshackexport DESTINATION ${PLUGIN_INSTALL_DIR})
INSTALL(FILES kipiplugin_imageshackexport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
