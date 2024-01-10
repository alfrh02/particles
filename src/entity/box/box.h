#pragma once

#include "entity.h"

class Box : public Entity {
    public:
        Box(vec2 pos, float size);

        void update(double deltaTime) override;
        void draw() override;

    private:

};