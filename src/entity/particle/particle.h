#pragma once

#include "entity.h"

class Particle : public Entity {
    public:
        Particle(vec2 pos, vec2 dir, float size, float speed, float lifespan, ofColor col);

        void update(double deltaTime) override;
        void draw() override;

        bool getIsDead();

    private:
        vec2 _direction;

        float _lifetime;
        float _lifespan;

        ofColor _color;

        float _alpha;
};