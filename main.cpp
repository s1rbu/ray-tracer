#include <iostream>
#include "Canvas.h"
#include "Projectile.h"
#include <fstream>
#include "CanvasUtils.h"
#include "Matrix.h"

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

int main() {
    // chapter2();
    chapter3();
    return 0;
}
