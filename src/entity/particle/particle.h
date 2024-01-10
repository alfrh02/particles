#pragma once

#include "entity.h"

class Particle : public Entity {
    public:
        Particle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col);

        void update(double deltaTime) override;
        void draw() override;

        bool getIsDead();

    private:
        vec2 _direction;

        float _lifetime;
        unsigned short _lifespan; // we keep this as an unsigned short so that we can pass -1 as an argument to mean practically infinite

        ofColor _color;

        float _alpha;
};