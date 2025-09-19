#include <iostream>
#include "Canvas.h"
#include "Projectile.h"
#include <fstream>
#include "CanvasUtils.h"

std::ofstream fout("ch2_projectile.ppm");

int main() {
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

    return 0;
}
