#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <utility>
#include "object.h"

class Scene {
private:
    std::vector<std::unique_ptr<Object>> objects_;

public:
    void add_object(std::unique_ptr<Object> object) {
        objects_.push_back(std::move(object));
    }

    const std::vector<std::unique_ptr<Object>>& objects() const { return objects_; }
};

#endif