#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
    // def constructors

        ray() {}
        // when given input, cast them to private variables
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        // return references to origin and direction
        const point3& origin() const  { return orig; }
        const vec3& direction() const { return dir; }

        // formula for a ray: R = origin + time * direction.
        point3 at(double t) const {
            return orig + t*dir;
        }
  
  private:
  // define private variables origin and direction.
    point3 orig;
    vec3 dir;
};

#endif