#pragma once

#include "ofMain.h"
#include "settings.h"

using namespace glm;

class Entity {
    public:
        Entity(vec2 pos = vec2(0, 0), float size = 0, ofColor col = COLORS.FOREGROUND);

        virtual void update(double deltaTime);
        virtual void draw();
        virtual void drawEditMode();

        void setCaptured(bool captured = false, int x = 0, int y = 0);

        bool getCaptured();
        vec2 getPosition();
        float getSize();

    protected:
        vec2 _position;
        vec2 _direction;
        float _rotation;
        float _size;
        float _speed;

        ofColor _color;

        bool _captured;
        vec2 _mouseCoordinates;
};