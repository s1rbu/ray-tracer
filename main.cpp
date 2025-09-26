#include <iostream>
#include "Canvas.h"
#include "Projectile.h"
#include <fstream>
#include "CanvasUtils.h"
#include "Intersection.h"
#include "Intersections.h"
#include "Matrix.h"
#include "Sphere.h"

std::ofstream fout("output.ppm");

void chapter2() {
    Projectile p(Point(0, 1, 0), Vector(Vector::normalize(Vector(1, 1.8, 0)) * 11.25));
    const Environment e(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));
    Canvas canvas(900, 550);

    while (p.getPosition().getY() > 0) {
        const double x = p.getPosition().getX();
        const double y = canvas.getHeight() - p.getPosition().getY();
        canvas.writePixel(int(x), int(y), Color(255, 255, 255));
        p = Projectile::tick(e, p);
    }

    fout << canvas2ppm(canvas);
}

void chapter3() {
    Canvas canvas(900, 550);
    const Point twelve(0, 0, 1);
    const double radius = canvas.getWidth() * 3.0 / 12.0;
    const int x = canvas.getWidth() / 2;
    const int y = canvas.getHeight() / 2;

    for (int i = 0; i < 12; i++) {
        Matrix r = Matrix::rotationY(i * std::numbers::pi / 6);
        auto p = Point(r * twelve);

        const int fX = x + int(p.getX() * radius);
        const int fY = y + int(p.getZ() * radius);

        canvas.writePixel(fX, fY, Color(255, 255, 255));
    }

    fout << canvas2ppm(canvas);
}

void chapter5() {
    const Point rayOrigin(0, 0, -5);
    double wallZ = 10.0;
    double wallSize = 7.0;
    int canvasPixels = 100;
    double pixelSize = wallSize / canvasPixels;
    double half = wallSize / 2.0;

    Canvas canvas(canvasPixels, canvasPixels);
    const Color color(1, 0, 0);
    Sphere s;
    // s.setTransform(Matrix::scaling(1,0.5,1));
    // s.setTransform(Matrix::scaling(0.5,1,1));
    // s.setTransform(Matrix::rotationZ(std::numbers::pi/4) * Matrix::scaling(0.5,1,1));
    // s.setTransform(Matrix::shearing(1,0,0,0,0,0) * Matrix::scaling(0.5,1,1));

    for (int y = 0; y < canvasPixels; y++) {
        double worldY = half - pixelSize * y;
        for (int x = 0; x < canvasPixels; x++) {
            double worldX = -half + pixelSize * x;
            Point position(worldX, worldY, wallZ);
            Ray r(rayOrigin, Vector::normalize(position - rayOrigin));
            std::vector<Intersection> xs = Sphere::intersect(s, r);
            if (xs.size() > 0) {
                canvas.writePixel(x, y, color);
            }
        }
    }

    fout << canvas2ppm(canvas);
}

void chapter6() {
    const Point rayOrigin(0, 0, -5);
    double wallZ = 10.0;
    constexpr double wallSize = 7.0;
    const int canvasPixels = 100;
    const double pixelSize = wallSize / canvasPixels;
    const double half = wallSize / 2.0;

    Canvas canvas(canvasPixels, canvasPixels);
    Color color(1, 0, 0);
    Sphere s;
    s.getMaterial().setSurfaceColor(Color(1, 0.2, 1));

    const Light light(Point(-10, 10, -10), Color(1, 1, 1));
    // s.setTransform(Matrix::scaling(1,0.5,1));
    // s.setTransform(Matrix::scaling(0.5,1,1));
    // s.setTransform(Matrix::rotationZ(std::numbers::pi/4) * Matrix::scaling(0.5,1,1));
    // s.setTransform(Matrix::shearing(1,0,0,0,0,0) * Matrix::scaling(0.5,1,1));

    for (int y = 0; y < canvasPixels; y++) {
        const double worldY = half - pixelSize * y;
        for (int x = 0; x < canvasPixels; x++) {
            const double worldX = -half + pixelSize * x;
            Point position(worldX, worldY, wallZ);
            Ray r(rayOrigin, Vector::normalize(position - rayOrigin));
            std::vector<Intersection> xs = Sphere::intersect(s, r);
            const Intersection *hit = ::hit(xs);
            if (hit) {
                const Point point = Ray::position(r, hit->getT());
                Vector normal = hit->getObject().normal_at(point);
                const Vector eye = -r.getDirection();
                color = Material::lighting(hit->getObject().getMaterial(), light, point, eye, normal);

                canvas.writePixel(x, y, color);
            }
        }
    }

    fout << canvas2ppm(canvas);
}

int main() {
    // chapter2();
    // chapter3();
    // chapter5();
    chapter6();

    return 0;
}
