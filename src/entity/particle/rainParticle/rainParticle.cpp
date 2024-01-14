#include "rainParticle.h"

RainParticle::RainParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: Particle(pos, dir, size, speed, lifespan, col) {

}

void RainParticle::draw() {
    ofSetColor(_color);
    ofDrawLine(_position, _position + _direction*(_size*8));
}

void RainParticle::onCollision(ofRectangle boundingBox) {
    _lifetime = _lifespan;
}