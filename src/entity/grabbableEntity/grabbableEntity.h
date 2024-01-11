#pragma once

#include "entity.h"

class GrabbableEntity : public Entity {
    public:
        GrabbableEntity(vec2 pos, float size, ofColor col);

        void setCaptured(bool captured);
        bool getCaptured();

    protected:
        bool _captured;
};