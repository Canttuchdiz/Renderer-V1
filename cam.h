#ifndef CAM_H
#define CAM_H

#include "vec3.h"

class Camera {
private:
    double horizontal_fov_;
    Point3 position_;
    Vector3 forward_;
    Vector3 up_;
    Vector3 right_;
    double aspect_ratio_;
    int image_width_;

public:

    Camera(int width, double aspect_ratio, double fov, Point3 position);

    Point3 position() const;
    
    Point3 pixel_position(int x, int y) const;

};

#endif