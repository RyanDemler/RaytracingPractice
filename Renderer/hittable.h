#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hitRecord {
    public:
        point3 point;
        vec3 normal;
        double time;
        bool frontFace;

        void setFaceNormal(const ray& ray, const vec3& outwardNormal){
            // set normal vector, outwardNormal is of length 1.
            frontFace = dot(ray.direction(), outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
};


class hittable
{
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, double rayTmin, double rayTmax, hitRecord& rec) const = 0;
};



#endif