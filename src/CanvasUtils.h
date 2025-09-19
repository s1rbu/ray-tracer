#ifndef RAY_TRACER_CANVASUTILS_H
#define RAY_TRACER_CANVASUTILS_H
#include <algorithm>
#include <string>
#include "Canvas.h"

inline std::string canvas2ppm(const Canvas &canvas) {
    std::string ppm;
    ppm.append("P3\n");
    ppm.append(std::to_string(canvas.getWidth()) + " ");
    ppm.append(std::to_string(canvas.getHeight()) + "\n");
    ppm.append("255\n");

    const int height = canvas.getHeight();
    const int width = canvas.getWidth();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const Color c = canvas.pixelAt(x, y);
            std::string red = std::to_string(std::clamp(int(std::round(c.red() * 255)), 0, 255));
            std::string green = std::to_string(std::clamp(int(std::round(c.green() * 255)), 0, 255));
            std::string blue = std::to_string(std::clamp(int(std::round(c.blue() * 255)), 0, 255));

            ppm.append(red + " " + green + " " + blue + " ");
        }
        ppm.append("\n");
    }

    return ppm;
}

#endif //RAY_TRACER_CANVASUTILS_H
