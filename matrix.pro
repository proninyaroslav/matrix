# Copyright (c) 2014 Yaroslav Pronin
#
# This file is part of Matrix.
#
# Matrix is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Matrix is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Matrix. If not, see <http://www.gnu.org/licenses/>.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = matrix
TEMPLATE = app

RESOURCES += \
    img.qrc

SOURCES += main.cpp \
    ui.cpp \
    widget.cpp \
    matrix.cpp

HEADERS += \
    ui.h \
    widget.h \
    matrix.h
macx:ICON = $${PWD}/icon.icns
QMAKE_MAC_SDK = macosx10.9
