#pragma once

#include "ofMain.h"

using namespace glm;

class Entity {
    public:
        Entity(vec2 pos, float size);

        virtual void update(double deltaTime);
        virtual void draw();
        virtual void drawDebug();

    protected:
        vec2 _position;
        vec2 _direction;
        float _rotation;
        float _size;
        float _speed;

        ofRectangle _boundingBox;
};