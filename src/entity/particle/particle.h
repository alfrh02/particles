#pragma once

#include "entity.h"

class Particle : public Entity {
    public:
        Particle(vec2 pos, void (*func)(Particle&), vec2 dir, float size, float speed, unsigned short lifespan, ofColor col);

        void update(double deltaTime) override;
        void (*process)(Particle&);
        void draw() override;
        void drawEditMode() override;

        void onCollision(ofRectangle boundingBox);

        void setLifetime(float lifetime);

        bool getIsDead();
        float getLifetime();

    protected:
        float _lifetime;
        unsigned short _lifespan; // we keep this as an unsigned short so that we can pass -1 as an argument to mean practically infinite
};