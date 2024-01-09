#pragma once

#include "ofMain.h"

using namespace glm;

class Particle {
    public:
        Particle(vec3 pos, float lifespan);

        void update(double deltaTime);
        void draw();

        bool isDead(double deltaTime);

    private:
        vec3 _position;

        float _lifetime = 0;
        float _lifespan;

        ofBoxPrimitive box;
};