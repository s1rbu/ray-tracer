#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H
#include <algorithm>

#include "Color.h"
#include "Light.h"

class Material {
    Color surfaceColor = Color(1, 1, 1);
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;

public:
    Material() {
    }

    Material(const Color &color, const double ambient, const double diffuse, const double specular,
             const double shininess) : surfaceColor(color) {
        this->ambient = std::clamp(ambient, 0.0, 1.0);
        this->diffuse = std::clamp(diffuse, 0.0, 1.0);
        this->specular = std::clamp(specular, 0.0, 1.0);
        this->shininess = std::clamp(shininess, 10.0, 200.0);
    }

    Color getSurfaceColor() const {
        return surfaceColor;
    }

    double getAmbient() const {
        return ambient;
    }

    double getDiffuse() const {
        return diffuse;
    }

    double getSpecular() const {
        return specular;
    }

    double getShininess() const {
        return shininess;
    }

    void setAmbient(const double ambient_) {
        this->ambient = std::clamp(ambient_, 0.0, 1.0);
    }

    void setDiffuse(const double diffuse_) {
        this->diffuse = std::clamp(diffuse_, 0.0, 1.0);
    }

    bool operator==(const Material &other) const {
        return surfaceColor == other.surfaceColor && ambient == other.ambient && diffuse == other.diffuse && specular ==
               other.specular && shininess == other.shininess;
    }

    static Color lighting(const Material &material, const Light &light, const Point &point, const Vector &eyeV,
                          const Vector &normalV) {
        const Color effectiveColor = Color::hadamard(material.surfaceColor, light.getIntensity());
        const Vector lightV = Vector::normalize(light.getPosition() - point);
        const Color ambient = Color(effectiveColor * material.ambient);
        Color specular, diffuse;

        const double lightDotNormal = Vector::dot(lightV, normalV);
        if (lightDotNormal < 0) {
            specular = Color(0, 0, 0);
            diffuse = Color(0, 0, 0);
        } else {
            diffuse = Color(Color(effectiveColor * material.diffuse) * lightDotNormal);
            const Vector reflectV = Vector::reflect(-lightV, normalV);
            const double reflectDotEye = Vector::dot(reflectV, eyeV);

            if (reflectDotEye <= 0) {
                specular = Color(0, 0, 0);
            } else {
                const double factor = pow(reflectDotEye, material.shininess);
                specular = Color(Color(light.getIntensity() * material.specular) * factor);
            }
        }

        return Color(ambient + diffuse + specular);
    }
};

#endif //RAY_TRACER_MATERIAL_H
