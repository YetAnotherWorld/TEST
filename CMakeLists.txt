# SPDX-FileCopyrightText: 2022 test <>
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

project(test_talbe_sql VERSION 0.1)

include(FeatureSummary)

set(QT5_MIN_VERSION 5.15)
set(KF5_MIN_VERSION 5.83)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(Qt5 ${QT5_MIN_VERSION} REQUIRED COMPONENTS Core Gui Qml QuickControls2 Svg Sql)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Kirigami2 CoreAddons I18n)

add_subdirectory(src)

install(PROGRAMS org.kde.test_talbe_sql.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.test_talbe_sql.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
