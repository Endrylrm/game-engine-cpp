include(FetchContent)
set(SDLTTF_VENDORED ON CACHE BOOL "Use vendored libraries" FORCE)
FetchContent_Declare(sdl3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(sdl3_ttf)