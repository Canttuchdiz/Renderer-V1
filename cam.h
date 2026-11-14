#ifndef CAM_H
#define CAM_H

#include "vec3.h"

class Camera {
private:
    int image_width_;
    double aspect_ratio_;
    double horizontal_fov_;
    Point3 position_;
    Vector3 forward_;
    Vector3 up_;
    Vector3 right_;

public:

    Camera(int width, double aspect_ratio, double fov, Point3 position);

    Point3 position() const;

    Point3 plane_origin() const;

    Point3 pixel_center(int x, int y) const;

    Point3 pixel_random(int x, int y) const;
    
};

#endif