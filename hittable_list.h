#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

inline aabb surrounding_box(const aabb& box0, const aabb& box1){
    point3 small(
        std::fmin(box0.min().x(), box1.min().x()),
        std::fmin(box0.min().y(), box1.min().y()),
        std::fmin(box0.min().z(), box1.min().z())
    );
    
    point3 big(
        std::fmax(box0.max().x(), box1.max().x()),
        std::fmax(box0.max().y(), box1.max().y()),
        std::fmax(box0.max().z(), box1.max().z())
    );
    
    return aabb(small, big);

}


class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval (ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
    
    aabb bounding_box() const override{
        if(objects.empty()) return aabb();

        aabb box = objects[0]->bounding_box();

        for(size_t i = 1 ; i< objects.size(); ++ i){
            box = surrounding_box(box, objects[i]->bounding_box());
        }
        return box;
    }
    
};



#endif