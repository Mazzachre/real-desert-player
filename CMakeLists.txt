cmake_minimum_required(VERSION 3.16)
project(desert-player)

find_package(ECM REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(X11 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(real-desert-player)

target_sources(real-desert-player
	PRIVATE
	src/main.cpp
	src/app/app.cpp
	src/ui/keep_alive.cpp
	src/resources.qrc
)

target_link_libraries(real-desert-player
	Qt6::Core
	Qt6::X11Extras
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
