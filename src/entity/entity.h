#pragma once

#include "ofMain.h"
#include "colors.h"

using namespace glm;

class Entity {
    public:
        Entity(vec2 pos = vec2(0, 0), float size = 0, ofColor col = COLORS.FOREGROUND);

        virtual void update(double deltaTime);
        virtual void draw();
        virtual void drawEditMode();

        void setPosition(vec2 position);
        void setCaptured(bool captured = false, int x = 0, int y = 0);

        vec2 getPosition();
        vec2 getDirection();
        float getSize();
        float getSpeed();
        bool getCaptured();

    protected:
        vec2 _position;
        vec2 _direction;
        float _size;
        float _speed;

        ofColor _color;

        bool _captured;
};