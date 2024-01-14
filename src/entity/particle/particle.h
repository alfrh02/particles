#pragma once

#include "entity.h"

enum ParticleType { bullet, smoke, fire, spark, rain, bubble };

class Particle : public Entity {
    public:
        Particle(vec2 pos = vec2(0, 0), vec2 dir = vec2(0, 0), float size = 1, float speed = 100, unsigned short lifespan = -1, ofColor col = COLORS.FOREGROUND);

        void update(double deltaTime) override;
        void draw() override;
        void drawEditMode() override;

        virtual void onCollision(ofRectangle boundingBox);

        void setLifetime(float lifetime);

        bool getIsDead();
        float getLifetime();

    protected:
        float _lifetime;
        unsigned short _lifespan; // we keep this as an unsigned short so that we can pass -1 as an argument to mean practically infinite
};