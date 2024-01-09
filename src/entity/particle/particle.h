#pragma once

#include "entity.h"

class Particle : public Entity {
    public:
        Particle(vec2 pos, float size, float lifespan);

        void update(double deltaTime) override;
        void draw() override;

        bool isDead(double deltaTime);

    private:
        float _lifetime = 0;
        float _lifespan;
};