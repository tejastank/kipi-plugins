# ===========================================================
#
# This file is a part of digiKam project
# <a href="http://www.digikam.org">http://www.digikam.org</a>
#
# @date   2011-12-28
# @brief  threadweaver api test application
#
# @author Copyright (C) 2011-2012 by A Janardhan Reddy <annapareddyjanardhanreddy at gmail.com>
#
# This program is free software; you can redistribute it
# and/or modify it under the terms of the GNU General
# Public License as published by the Free Software Foundation;
# either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# ============================================================

SET(THREADWEAVER_FOUND ${KDE4_THREADWEAVER_LIBRARIES})

IF(THREADWEAVER_FOUND)

    INCLUDE_DIRECTORIES(${KDE4_INCLUDES}
                        ${JPEG_INCLUDE_DIR}
                        ${QT_INCLUDE_DIR}
                        ${QT_QTCORE_INCLUDE_DIR}
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../jpeglossless/plugin
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../jpeglossless/transform
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../jpeglossless/libjpeg
                       )

    SET(multithread_SRCS
        main.cpp
        imageselector.cpp
        ../../jpeglossless/transform/convert2grayscale.cpp
        ../../jpeglossless/transform/jpegtransform.cpp
        ../../jpeglossless/transform/imagerotate.cpp
        ../../jpeglossless/transform/imageflip.cpp
        ../../jpeglossless/libjpeg/transupp.cpp
        ../../jpeglossless/plugin/utils.cpp
        ../../jpeglossless/plugin/actionthread.cpp
    )

    KDE4_ADD_EXECUTABLE(multithread ${multithread_SRCS})

    TARGET_LINK_LIBRARIES(multithread
                          ${QT_QTGUI_LIBRARY}
                          ${QT_AND_KDECORE_LIBS}
                          ${KDE4_KPARTS_LIBS}
                          ${JPEG_LIBRARY}
                          ${KEXIV2_LIBRARIES}
                          ${KDCRAW_LIBRARIES}
                          ${KDE4_THREADWEAVER_LIBRARIES}
                          ${PNG_LIBRARIES}
                          kipiplugins
                         )

ENDIF(THREADWEAVER_FOUND)
