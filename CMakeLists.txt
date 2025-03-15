cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

project(real-desert-player)

find_package(ECM CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)

find_package(Qt5 CONFIG COMPONENTS Core Widgets Qml Quick DBus REQUIRED)
find_package(X11 REQUIRED)

add_executable(real-desert-player)

target_sources(
	real-desert-player
	PRIVATE
	src/main.cpp
	src/app/application.cpp
	src/app/playback.cpp
	src/player/player.cpp
	src/resources.qrc
)

target_link_libraries(
	real-desert-player
	Qt5::Core
	Qt5::Widgets
	Qt5::Qml
	Qt5::Quick
	Qt5::DBus
	X11
)

# Install binary
install(TARGETS real-desert-player RUNTIME DESTINATION bin)
message("Installing target: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/real-desert-player to ${CMAKE_INSTALL_PREFIX}/bin")

# Install the .desktop file
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/debian/real=desert-player.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)

# Install the icons
set(ICON_SIZES 16x16 32x32 48x48 64x64 128x128 256x256)
foreach(SIZE ${ICON_SIZES})
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/debian/icons/${SIZE}/ DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/${SIZE}/apps
            FILES_MATCHING PATTERN "*.png")
endforeach()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
