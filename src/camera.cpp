#include "camera.h"

int const Camera::DEFAULT_X    = 0;
int const Camera::DEFAULT_Y    = 0;
int const Camera::DEFAULT_W    = TILE_SIZE * 16;
int const Camera::DEFAULT_H    = TILE_SIZE * 12;
int const Camera::DEFAULT_ZOOM = 1;

Camera::Camera() : 
    x(DEFAULT_X), 
    y(DEFAULT_Y), 
    w(DEFAULT_W), 
    h(DEFAULT_H), 
    zoom(DEFAULT_ZOOM) {
}

Camera::Camera(int const x, int const y, int const w, int const h) : 
    x(x), 
    y(y), 
    w(w), 
    h(h), 
    zoom(DEFAULT_ZOOM) {
}

Camera::Camera(int const x, int const y, int const w, int const h, size_t const zoom) : 
    x(x), 
    y(y), 
    w(w), 
    h(h), 
    zoom(zoom) {
}

void
Camera::project(Level const &level) {

}

std::ostream& 
operator<< (std::ostream& os, Camera const &camera) {
    os << "Camera("
        << "x = " << camera.x 
        << ", y = " << camera.y 
        << ", w = " << camera.w 
        << ", h = " << camera.h 
        << ", zoom = " << camera.zoom
        << ")";
    return os;
}
