#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& sphereCenter, double radius) : center(sphereCenter), radius(std::fmax(0,radius)) {}

        bool hit(const ray& ray,double rayTmin, double rayTmax, hitRecord& rec) const override{
            vec3 cq = center - ray.origin(); // (C-Q) from (C-(Q+td)) = (-td dot (C-Q))
            
            auto a = ray.direction().length_squared(); // Solved from quadratic formula, t^2 * (raydirection)^2
            auto h = dot(ray.direction(),cq); // Solved from quadratic formula, t * (-2d dot (C-Q))
            auto c = cq.length_squared() - radius*radius; // Solved from quadratic formula, 1 * (C-Q) dot (C-Q) - r^2

            auto discriminant = h*h - a*c; // Discriminant < 0 - Ray has missed the sphere.

            if (discriminant < 0) return false;

            auto sqrtDiscrmnt = std::sqrt(discriminant);

            // Nearest Root calculations
            auto root = (h-sqrtDiscrmnt) / a; // simplified quadratic formula
            if (root <= rayTmin || rayTmax <= root){ // is one root within min and max timeframe
                root = (h + sqrtDiscrmnt) / a; // is the other solution within timeframe
                if (root <= rayTmin || rayTmax <= root){
                    return false;
                }
            }

            rec.time = root;
            rec.point = ray.at(rec.time);
            vec3 outwardNormal = (rec.point - center) / radius;
            rec.setFaceNormal(ray,outwardNormal);

            return true;    
        }
    private:
        point3 center;
        double radius;
};

#endif