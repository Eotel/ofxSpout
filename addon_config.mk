linux64:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =

vs:

linuxarmv6l:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =

linuxarmv7l:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =

android/armeabi:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =

android/armeabi-v7a:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =

osx:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =

msys2:
	# Enable SSSE3 path in SpoutCopy when available on target CPUs
	ADDON_CFLAGS = -mssse3
	# Link required Windows/DirectX libraries (MinGW doesn't process #pragma comment)
	ADDON_LDFLAGS = -ld3d11 -ldxgi -lversion

ios:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =

tvos:
	ADDON_SOURCES_EXCLUDE = libs/%
	ADDON_INCLUDES_EXCLUDE = libs/%
	ADDON_SOURCES =
