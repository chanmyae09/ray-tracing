#ifndef AABB_H
#define AABB_H


class aabb{
    public:
    aabb() {}
    aabb(const point3& a, const point3& b) : minimum(a), maximum(b) {}
    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    bool hit(const ray& r, interval ray_t) const {
        auto t_min = ray_t.min;
        auto t_max = ray_t.max;
        for(int i = 0; i< 3; ++i){
            double t0 = (min()[i] - r.origin()[i]) / r.direction()[i];
            double t1 = (max()[i] - r.origin()[i]) / r.direction()[i];
            if(t0 > t1)
                std::swap(t0,t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
        }

       return t_min < t_max; 

    }
    private:
    point3 minimum;
    point3 maximum;
};




#endif

