#include "smokeParticle.h"

SmokeParticle::SmokeParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: Particle(pos, dir, size, speed, lifespan, col) {
}

void SmokeParticle::update(double deltaTime) {
    _position += _speed * _direction * 1/ofGetFrameRate();
    _direction = normalize(vec2(sin(deltaTime / 10) * 5, -1));

    _lifetime += ofGetLastFrameTime();
}