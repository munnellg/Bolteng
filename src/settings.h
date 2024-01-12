#ifndef CKOBAN_SETTINGS_H
#define CKOBAN_SETTINGS_H

#include <filesystem>

extern int const DEFAULT_WINDOW_WIDTH;
extern int const DEFAULT_WINDOW_HEIGHT;
extern int const DEFAULT_WINDOW_FLAGS;
extern int const DEFAULT_RENDERER_FLAGS; 
extern std::filesystem::path const DEFAULT_ASSETS_DIR;
extern std::filesystem::path const DEFAULT_TEXTURES_FILE;

extern int const ERROR_FILE_OPEN;
extern int const ERROR_FILE_WRITE;

struct Settings {
    int window_width;
    int window_height;
    int window_flags;
    int renderer_flags;

    std::filesystem::path assets;
    std::filesystem::path textures;
};

extern int load_settings(struct Settings &settings);
extern int save_settings(struct Settings const &settings);

#endif
