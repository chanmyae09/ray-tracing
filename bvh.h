#ifndef BVH_h
#define BVH_h

#include "hittable.h"
#include <algorithm>

inline bool box_compare(const shared_ptr<hittable> a,
                        const shared_ptr<hittable> b,
                        int axis){
    return a->bounding_box().min()[axis] < b->bounding_box().min()[axis];
                        }


class bvh_node : public hittable{
 private:
    shared_ptr<hittable>left;
    shared_ptr<hittable> right;
    aabb bbox;
 public:
    bvh_node(std::vector<shared_ptr<hittable>>& objects, size_t start, size_t end){
        size_t object_span = end - start;

        if(object_span == 1){
            left = right = objects[start];
        }
        else if(object_span == 2){
            left = objects[start];
            right = objects[start+1];
        }
        else{
            int axis = random_int(0,2);

            std::sort(objects.begin() + start, objects.begin() + end,
        [axis](const auto&a, const auto& b) {return box_compare(a,b,axis);});

            size_t mid = start + object_span / 2;

            left = make_shared<bvh_node>(objects, start, mid);
            right = make_shared<bvh_node>(objects, mid, end);
        }
        bbox = surrounding_box(left->bounding_box(), right->bounding_box()); 
    }
    bool hit(const ray& r, interval ray_t, hit_record& hit_record) const override{
        if(!bbox.hit(r,ray_t))
            return false;

        bool hit_left = left->hit(r,ray_t, hit_record);
        bool hit_right = right-> hit(r, interval(ray_t.min, hit_left ? hit_record.t : ray_t.max),
                hit_record);
        return hit_left || hit_right;


    }

    aabb bounding_box() const override{
        return bbox;
    }
};



#endif