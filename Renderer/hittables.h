#ifndef HITTABLES_H
#define HITTABLES_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittableList : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;
        
        hittableList() {}
        hittableList(shared_ptr<hittable> object) { add(object);}

        void clear() { objects.clear();}

        void add(shared_ptr<hittable> object){
            objects.push_back(object);
        }

        bool hit(const ray& ray, double rayTmin, double rayTmax, hitRecord& rec) const override{
            hitRecord tempHitrec; // store hit record
            bool hitAnything = false; // bool to return
            auto currentClosest = rayTmax; // keep track of closest t to ray hit.

            for (const auto& object : objects){
                // for each object, see if it was hit by ray.
                if (object->hit(ray,rayTmin,currentClosest,tempHitrec)){
                    hitAnything = true;
                    currentClosest = tempHitrec.time;
                    rec = tempHitrec;
                }
            }

            return hitAnything;
        }
};

#endif