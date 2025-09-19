#ifndef RAY_TRACER_CANVAS_H
#define RAY_TRACER_CANVAS_H
#include <vector>

#include "Color.h"

class Canvas {
    int width;
    int height;
    std::vector<std::vector<Color> > pixels;

public:
    Canvas() {
        this->width = 0;
        this->height = 0;
    }

    Canvas(const int width_, const int height_) : width(width_), height(height_) {
        this->pixels = std::vector<std::vector<Color> >(height, std::vector<Color>(width, Color(0.0, 0.0, 0.0)));
    }

    int getWidth() const {
        return this->width;
    }

    int getHeight() const {
        return this->height;
    }

    Color pixelAt(const int x, const int y) const {
        return this->pixels[y][x];
    }

    void writePixel(const int x, const int y, const Color color) {
        this->pixels[y][x] = color;
    }
};

#endif //RAY_TRACER_CANVAS_H
