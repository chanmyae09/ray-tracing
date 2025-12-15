#ifndef AABB_H
#define AABB_H


class aabb{
    public:
    aabb() {}
    aabb(const point3& a, const point3& b) : minimum(a), maximum(b) {}
    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    bool hit(const ray& r, interval ray_t) const {
        // Cache inverse direction (3 divisions, done once)
        const double inv_dir_x = 1.0 / r.direction().x();
        const double inv_dir_y = 1.0 / r.direction().y();
        const double inv_dir_z = 1.0 / r.direction().z();
        
        // Cache origin to avoid repeated function calls
        const auto& orig = r.origin();
        
        // X axis
        double t0_x = (minimum.x() - orig.x()) * inv_dir_x;
        double t1_x = (maximum.x() - orig.x()) * inv_dir_x;
        if (t0_x > t1_x) std::swap(t0_x, t1_x);
        
        double t_min = std::fmax(t0_x, ray_t.min);
        double t_max = std::fmin(t1_x, ray_t.max);
        
        if (t_min > t_max) return false;  // Early exit if X-axis fails
        
        // Y axis
        double t0_y = (minimum.y() - orig.y()) * inv_dir_y;
        double t1_y = (maximum.y() - orig.y()) * inv_dir_y;
        if (t0_y > t1_y) std::swap(t0_y, t1_y);
        
        t_min = std::fmax(t0_y, t_min);
        t_max = std::fmin(t1_y, t_max);
        
        if (t_min > t_max) return false;  // Early exit if Y-axis fails
        
        // Z axis
        double t0_z = (minimum.z() - orig.z()) * inv_dir_z;
        double t1_z = (maximum.z() - orig.z()) * inv_dir_z;
        if (t0_z > t1_z) std::swap(t0_z, t1_z);
        
        t_min = std::fmax(t0_z, t_min);
        t_max = std::fmin(t1_z, t_max);
        
        return t_min <= t_max;
    }
    private:
    point3 minimum;
    point3 maximum;
};




#endif

