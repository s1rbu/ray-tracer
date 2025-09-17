#include <iostream>

#include "Projectile.h"

int main() {
    Projectile p(Point(0, 1, 0), Vector::normalize(Vector(1, 1, 0)));
    const Environment e(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));

    while (p.getPosition().getY() > 0) {
        const double y = p.getPosition().getY();
        std::cout << y << std::endl;
        p = Projectile::tick(e, p);
    }

    return 0;
}
