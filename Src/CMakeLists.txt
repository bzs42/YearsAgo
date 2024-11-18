set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES YearsAgo_de_DE.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

set(PROJECT_SOURCES
    App.qrc
    Cache.cpp
    Cache.h
    ImageGenerator.cpp
    ImageGenerator.h
    Model.cpp
    Model.h
    ScopeTimer.h
    SearchAlgorithm.cpp
    SearchAlgorithm.h
    SearchThread.cpp
    SearchThread.h
    View.cpp
    View.h
    View.ui
    ViewModel.cpp
    ViewModel.h
    main.cpp
    ${TS_FILES}
)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/App.rc")

add_executable(YearsAgo ${PROJECT_SOURCES} ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(YearsAgo PRIVATE Qt6::Widgets)

if(WIN32)
    # use WinMain() entry point to hide console window and make a GUI application
    set_target_properties(YearsAgo PROPERTIES WIN32_EXECUTABLE TRUE)

    # install

    get_target_property(_QmakeExecutable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_QtBinDir "${_QmakeExecutable}" DIRECTORY)
    find_program(_WindeployExecutable windeployqt HINTS "${_QtBinDir}")
    message(VERBOSE "_WindeployExecutable:"         ${_WindeployExecutable})

    if (_WindeployExecutable)
        add_custom_command(
            TARGET YearsAgo
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
            COMMAND "${CMAKE_COMMAND}" -E
                env PATH="${_QtBinDir}" "${_WindeployExecutable}"
                    --verbose 1
                    --dir \"${CMAKE_CURRENT_BINARY_DIR}/windeployqt\"
                    #--qmldir \"${PROJECT_SOURCE_DIR}/src/qml\"
                    #--no-compiler-runtime
                    --compiler-runtime
                    \"$<TARGET_FILE:YearsAgo>\"
            COMMENT "Execute windeployqt..."
        )
    endif()

    install(
        TARGETS YearsAgo
        DESTINATION bin
        COMPONENT _ComponentApplication
    )

    install(
        DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/windeployqt/"
        DESTINATION bin
        COMPONENT _ComponentApplication
    )

    install(
        FILES
        "${PROJECT_SOURCE_DIR}/LICENSE.GPL3-EXCEPT.txt"
        "${PROJECT_SOURCE_DIR}/LICENSE.LGPL3.txt"
        "${PROJECT_SOURCE_DIR}/LICENSE.BSD-3-Clause.txt"
        DESTINATION .
        COMPONENT _ComponentApplication
    )

    # packaging

    set(CPACK_GENERATOR "IFW" "ZIP")
    set(CPACK_PACKAGE_NAME "YearsAgo")
    set(CPACK_PACKAGE_VENDOR "${PROJECT_HOMEPAGE_URL}")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "dilishes/YearsAgo")
    set(CPACK_PACKAGE_EXECUTABLES "YearsAgo" "Years Ago Application")
    set(CPACK_COMPONENTS_ALL _ComponentApplication)
    set(CPACK_IFW_TARGET_DIRECTORY "@ApplicationsDirX64@/${CPACK_PACKAGE_INSTALL_DIRECTORY}")
    set(CPACK_IFW_PACKAGE_START_MENU_DIRECTORY "dilishes")
    set(CPACK_IFW_VERBOSE ON)

    include(CPack REQUIRED)
    include(CPackIFW REQUIRED)

    cpack_add_component(
        _ComponentApplication
        DISPLAY_NAME "Years Ago"
        DESCRIPTION "shows images from years ago"
        REQUIRED
    )

    cpack_ifw_configure_component(_ComponentApplication
        NAME de.igniti.bonusapp
        LICENSES "GPL" "${PROJECT_SOURCE_DIR}/LICENSE.GPL3-EXCEPT.txt"
        LICENSES "LGPL" "${PROJECT_SOURCE_DIR}/LICENSE.LGPL3.txt"
        LICENSES "BSD-3" "${PROJECT_SOURCE_DIR}/LICENSE.BSD-3-Clause.txt"
        DEFAULT TRUE
        SCRIPT "${PROJECT_SOURCE_DIR}/InstallScript.qs"
    )
endif()
