SUBDIRS(icons)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/importwizard
                    ${CMAKE_CURRENT_SOURCE_DIR}/blendingdlg
                    ${CMAKE_CURRENT_SOURCE_DIR}/manager
                   )

SET(expoblending_common_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/manager/manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/manager/actionthread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importwizard/importwizarddlg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importwizard/intropage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importwizard/itemspage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importwizard/rawpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importwizard/alignpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importwizard/lastpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/blendingdlg/expoblendingdlg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/blendingdlg/enfusesettings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/blendingdlg/bracketstack.cpp
   )

INSTALL(DIRECTORY pics
        DESTINATION ${DATA_INSTALL_DIR}/kipiplugin_expoblending
        PATTERN ".svn" EXCLUDE
       )

# =======================================================
# ExpoBlending plugin

SET(kipiplugin_expoblending_PART_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/plugin_expoblending.cpp

    ${expoblending_common_SRCS}
   )

KDE4_ADD_PLUGIN(kipiplugin_expoblending ${kipiplugin_expoblending_PART_SRCS})

TARGET_LINK_LIBRARIES(kipiplugin_expoblending
                      ${KDE4_KPARTS_LIBS}
                      ${QT_AND_KDECORE_LIBS}
                      ${KIPI_LIBRARIES}
                      ${KEXIV2_LIBRARIES}
                      ${KDCRAW_LIBRARIES}
                      kipiplugins
                     )

INSTALL(TARGETS kipiplugin_expoblending DESTINATION ${PLUGIN_INSTALL_DIR})
INSTALL(FILES kipiplugin_expoblending.desktop DESTINATION ${SERVICES_INSTALL_DIR})

# =======================================================
# Stand alone version of ExpoBlending plugin

SET(expoblending_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/expoblending.cpp
    ${expoblending_common_SRCS}
   )

KDE4_ADD_APP_ICON(hdrgui_SRCS "expoblending")

KDE4_ADD_EXECUTABLE(expoblending ${expoblending_SRCS})

TARGET_LINK_LIBRARIES(expoblending
                      ${KDE4_KPARTS_LIBS}
                      ${QT_AND_KDECORE_LIBS}
                      ${KIPI_LIBRARIES}
                      ${KEXIV2_LIBRARIES}
                      ${KDCRAW_LIBRARIES}
                      kipiplugins
                     )

INSTALL(TARGETS expoblending ${INSTALL_TARGETS_DEFAULT_ARGS})
INSTALL(FILES expoblending.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )

