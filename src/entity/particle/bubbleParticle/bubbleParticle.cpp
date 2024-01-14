#include "bubbleParticle.h"

BubbleParticle::BubbleParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: Particle(pos, dir, size, speed, lifespan, col) {
}

void BubbleParticle::update(double deltaTime) {
    _position += _speed * _direction * 1/ofGetFrameRate();

    if (_direction.y != 0) {
        _direction.y -= (_speed / 8) * 1/ofGetFrameRate();
        _direction = normalize(_direction);
    }

    _lifetime += ofGetLastFrameTime();
}

void BubbleParticle::draw() {
    ofSetColor(_color);
    ofNoFill();
    ofDrawCircle(_position, _size);
    ofFill();
}

void BubbleParticle::onCollision() {
    _lifetime = _lifespan;
}