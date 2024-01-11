#pragma once

#include "entity.h"

class GrabbableEntity : public Entity {
    public:
        GrabbableEntity(vec2 pos, float size, ofColor col);

        void setCaptured(bool captured = false, int x = 0, int y = 0);
        bool getCaptured();

    protected:
        bool _captured;
        vec2 _mouseCoordinates;
};