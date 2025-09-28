#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H
#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "World.h"

class Camera {
    double hSize;
    double vSize;
    double fieldOfView;
    Matrix transform = Matrix::identity();
    double pixelSize;
    double halfWidth;
    double halfHeight;

public:
    Camera(const double hSize_, const double vSize_, const double fOV_) : hSize(hSize_), vSize(vSize_),
                                                                          fieldOfView(fOV_) {
        const double halfView = std::tan(fieldOfView / 2.0);
        double aspect = hSize / vSize;
        if (aspect >= 1) {
            this->halfWidth = halfView;
            this->halfHeight = halfView / aspect;
        } else {
            this->halfWidth = halfView * aspect;
            this->halfHeight = halfView;
        }
        this->pixelSize = this->halfWidth * 2 / this->hSize;
    }

    double getHSize() const {
        return hSize;
    }

    double getVSize() const {
        return vSize;
    }

    double getFOV() const {
        return fieldOfView;
    }

    double getPixelSize() const {
        return pixelSize;
    }

    Matrix getTransform() const {
        return transform;
    }

    void setTransform(const Matrix &transform_) {
        this->transform = transform_;
    }

    Ray rayForPixel(const double px, const double py) const {
        const double xOffset = (px + 0.5) * pixelSize;
        const double yOffset = (py + 0.5) * pixelSize;

        const double worldX = halfWidth - xOffset;
        const double worldY = halfHeight - yOffset;

        const Point pixel = Point(Matrix::inverse(transform) * Point(worldX, worldY, -1));
        const Point origin = Point(Matrix::inverse(transform) * Point(0, 0, 0));
        const Vector direction = Vector::normalize(pixel - origin);

        return {origin, direction};
    }

    Canvas render(const World &w) const {
        Canvas image(hSize, vSize);
        for (int y = 0; y < vSize - 1; y++) {
            for (int x = 0; x < hSize; x++) {
                Ray r = rayForPixel(x, y);
                Color color = World::colorAt(w, r);
                image.writePixel(x, y, color);
            }
        }

        return image;
    }
};

#endif //RAY_TRACER_CAMERA_H
