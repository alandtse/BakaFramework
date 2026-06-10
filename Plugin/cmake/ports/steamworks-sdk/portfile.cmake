vcpkg_from_github(
	OUT_SOURCE_PATH SOURCE_PATH
	REPO rlabrecque/SteamworksSDK
	REF e7bb839178fc5a48aa380d85e2ad04cc97d9d11c
	SHA512 3cceea70fcf4eb106224d23900466209a97cfadd1ae92476e2244e7a0114926d969e12729d6e6b1b2a3ad24ea268e328d5e331de909cbc9319ef1ee0bf8605c3
	HEAD_REF main
)

set(MAJOR 1)
set(MINOR 60)

set(STAGING ${CURRENT_BUILDTREES_DIR}/src)

file(
	COPY
	${SOURCE_PATH}/public
	${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeLists.txt
	${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
	DESTINATION
	${STAGING}
)

configure_file(
	${CMAKE_CURRENT_LIST_DIR}/cmake/version.cmake.in
	${STAGING}/version.cmake
	@ONLY
)

vcpkg_cmake_configure(SOURCE_PATH ${STAGING})
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(
	PACKAGE_NAME SteamworksSDK
	CONFIG_PATH lib/cmake/SteamworksSDK
)

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

file(INSTALL ${SOURCE_PATH}/Readme.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
