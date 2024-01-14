#include "particle.h"

Particle::Particle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: Entity(pos, size, col) {
    _speed = speed;
    _direction = normalize(dir);

    _lifetime = 0;
    _lifespan = lifespan;
}

void Particle::update(double deltaTime) {
    // multiplying by 1/framerate makes this simulation framerate agnostic
    _position += _speed * _direction * 1/ofGetFrameRate();
    _lifetime += ofGetLastFrameTime();
}

void Particle::draw() {
    ofSetColor(_color);
    ofDrawCircle(_position, _size);
}

void Particle::drawEditMode() {
    ofSetColor(COLORS.FOREGROUND);
    ofDrawLine(_position, _position + _direction*(_size*4));
}

void Particle::onCollision(ofRectangle boundingBox) {
    // calculating centre of bounding box
    vec2 v = _position - (boundingBox.getPosition() + (vec2(boundingBox.getWidth(), boundingBox.getHeight()) / 2));

    // stretch our vector according to the X:Y ratio (our rects are not all perfect squares)
    v = v * vec2(1, boundingBox.getWidth() / boundingBox.getHeight());

    // rotate by 45 degrees & normalise, as this is a directional vector
    v = normalize(rotate(v, ofDegToRad(45)));

    // our exit angle is the same as the entry value, only inverted, so we times by -1.
    // top & bottom
    if ((v.x <= 0 && v.y >= 0) || (v.x >= 0 && v.y <= 0)) {
        _direction *= vec2(1, -1);
    } else { // left & right
        _direction *= vec2(-1, 1);
    }
}

bool Particle::getIsDead() {
    // kill off-screen particles
    if ((_position.x > ofGetWidth() || _position.x < 0) || (_position.y > ofGetHeight() || _position.y < 0)) {
        return true;
    }

    return _lifetime > _lifespan;
}

void Particle::setLifetime(float lifetime) {
    _lifetime = lifetime;
}

float Particle::getLifetime() {
    return _lifetime;
}