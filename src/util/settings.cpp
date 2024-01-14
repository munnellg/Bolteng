#include "settings.h"

#include <SDL2/SDL_video.h>
#include <stdio.h>

int const DEFAULT_WINDOW_WIDTH   = 800;
int const DEFAULT_WINDOW_HEIGHT  = 600;
int const DEFAULT_WINDOW_FLAGS   = 0;
int const DEFAULT_RENDERER_FLAGS = 0; 

std::filesystem::path const DEFAULT_ASSETS_DIR  = "assets";
std::filesystem::path const DEFAULT_TEXTURES_FILE = "tilesheet.png";

int const ERROR_FILE_OPEN  = 1;
int const ERROR_FILE_WRITE = 2;

#define BUFFSIZE 2048

static void
remove_comments_and_newline(char *str) {
    char* p = strpbrk(str, "#;\n");
    if (p) { *p = '\0'; }
}

static void
remove_trailing_whitespace(char *buf, size_t last) {
    for (size_t i = last; 
            i > 0 && (buf[i] == ' ' || buf[i] == '\t'); 
            i--) {
        buf[i] = '\0';
    }
}

static int
parse_section_header(char *src, char *dst) {
    char *start = &src[1];
    char *end   = strchr(start, ']');

    if (!end) {
        return 0;
    }
    
    size_t len = end - start;

    strncpy(dst, start, len);

    dst[len] = '\0';

    return 1;
}

static int
parse_field(char *src, char *field, char *value) {
    char *assign = strchr(src, '=');
    if (!assign) {
        return 0;
    }

    size_t len_field = assign - src;

    strncpy(field, src, len_field);

    field[len_field] = '\0';
    remove_trailing_whitespace(field, len_field - 1);

    // move to symbol after equals
    assign++;
    
    // find the first non-blank characters
    size_t offset = strspn(assign, "\t ");
    assign += offset;

    // copy into the value field
    size_t len_value = strlen(assign);
    strncpy(value, assign, len_value);

    value[len_value] = '\0';
    remove_trailing_whitespace(value, len_value - 1);
    
    return 1;
}

static void
process_field(char *section, char *field, char *value, Settings &settings) {
    if (strcmp("display", section) == 0) {
        if (strcmp("resolution", field) == 0) {
            if (strcmp("1920x1080", value) == 0) {
                settings.window_width  = 1920;
                settings.window_height = 1080;
            } else if (strcmp("1280x720", value) == 0) {
                settings.window_width  = 1280;
                settings.window_height = 720;
            } else if (strcmp("800x600", value) == 0) {
                settings.window_width  = 800;
                settings.window_height = 600;
            } else if (strcmp("320x200", value) == 0) {
                settings.window_width  = 320;
                settings.window_height = 200;
            } else {
                fprintf(stderr, "ignoring unsupported resolution '%s'\n", value);
            }
        } else if (strcmp("fullscreen", field) == 0) {
            if (strcmp("1", value) == 0) {
                settings.window_flags |= SDL_WINDOW_FULLSCREEN;
            } else if (strcmp("0", value) == 0) {
                settings.window_flags &= ~SDL_WINDOW_FULLSCREEN;
            } else {
                fprintf(stderr, "ignoring invalid fullscreen value '%s'\n", value);
            }
        } else { 
            fprintf(stderr, "unrecognized field '%s' in '%s'\n", field, section);
        }
    } else {
        fprintf(stderr, "unrecognized section '%s'\n", section);
    }
}

static int
parse_ini(const char *fname, Settings &settings) {
    char line[BUFFSIZE]    = {0};
    char section[BUFFSIZE] = {0};
    char field[BUFFSIZE]   = {0};
    char value[BUFFSIZE]   = {0};

    FILE *f = fopen(fname, "r");

    if (!f) {
        fprintf(stderr, "failed to open '%s'\n", fname);
        return 0;
    }

    for (int linenum = 1; fgets(line, BUFFSIZE, f); linenum++) {
        remove_comments_and_newline(line);

        // find the first non-blank characters
        size_t offset = strspn(line, "\t ");
        
        // line is the beginning of a new section
        if (line[offset] == '[') {
            if (!parse_section_header(line + offset, section)) {
                fprintf(stderr, "error: %s : line %d\n", fname, linenum);
                continue;
            }

        } else if (line[offset] != '\0') { // line is a field/value
            parse_field(line, field, value);

            process_field(section, field, value, settings);
        }
    }

    fclose(f);

    return 1;
}

static void
apply_default_config(Settings &settings) {
    // initialize program default values
    settings.window_width   = DEFAULT_WINDOW_WIDTH;
    settings.window_height  = DEFAULT_WINDOW_HEIGHT;
    settings.window_flags   = DEFAULT_WINDOW_FLAGS;
    settings.renderer_flags = DEFAULT_RENDERER_FLAGS;
    settings.assets         = DEFAULT_ASSETS_DIR;
    settings.textures       = DEFAULT_ASSETS_DIR / DEFAULT_TEXTURES_FILE;
}

int
load_settings(Settings &settings) {
    apply_default_config(settings);
    parse_ini("settings.ini", settings);
    return 0;
}

int
save_settings(Settings const &settings) {
    FILE *f = fopen("settings.ini", "w");

    if (!f) {
        return 1;
    }

    fprintf(f, "[display]\n");
    fprintf(f, "resolution = 1920x1080\n");
    fprintf(f, "fullscreen = false\n");
    fclose(f);

    return 0;
}
