#pragma once

#include "grabbableEntity.h"

class Box : public GrabbableEntity {
    public:
        Box(vec2 pos, float w, float h);

        void update(double deltaTime) override;
        void draw() override;

    private:
        float _width;
        float _height;

        ofRectangle rect;
};