# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2022 test <>

add_executable(test_talbe_sql
    main.cpp
    databaseQueryModel.cpp
    resources.qrc)

target_link_libraries(test_talbe_sql
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Svg
    Qt5::Sql
    KF5::I18n
    KF5::CoreAddons
  )
install(TARGETS test_talbe_sql ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
