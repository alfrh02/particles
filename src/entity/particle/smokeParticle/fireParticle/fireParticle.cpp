#include "fireParticle.h"

FireParticle::FireParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: SmokeParticle(pos, dir, size, speed, lifespan, col) {
}

void FireParticle::onCollision(ofRectangle boundingBox) {
    _lifetime = _lifespan;
}