#ifndef CAMERA_H
#define CAMERA_H

#include "level.h"
#include <ostream>

struct Rect {
    int x;
    int y;
    int h;
    int w;
};

struct RenderSlice {
    std::vector<int> textures;
    Rect screen;
    Rect texture;
};

class Camera {
public:
    static int const DEFAULT_X;
    static int const DEFAULT_Y;
    static int const DEFAULT_W;
    static int const DEFAULT_H;
    static int const DEFAULT_ZOOM;

    int x; // x-coordinate of upper left corner in world coordinates
    int y; // y-coordinate of upper left corner in world coordinates
    int w; // width of camera in world units
    int h; // height of camera in world units
    
    // the greater the value of zoom, the more zoomed out the camera
    size_t zoom; 
                 
    Camera();
    Camera(int const x, int const y, int const w, int const h);
    Camera(int const x, int const y, int const w, int const h, size_t const zoom);

    void project(Level const &level);

    friend std::ostream& operator<< (std::ostream& stream, Camera const &camera);
};

#endif // CAMERA_H

