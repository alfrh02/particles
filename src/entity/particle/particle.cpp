#include "particle.h"

Particle::Particle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: Entity(pos, size, col) {
    _speed = speed;
    _direction = normalize(dir);

    _lifetime = 0;
    _lifespan = lifespan;
}

void Particle::update(double deltaTime) {
    _position += _speed * _direction * 1/ofGetFrameRate();
    _lifetime += ofGetLastFrameTime();
}

void Particle::draw() {
    ofSetColor(_color);
    ofDrawCircle(_position, _size);
}

void Particle::drawEditMode() {
    ofSetColor(COLORS.DIRECTION);
    ofDrawLine(_position, _position + _direction*(_size*4));
}

void Particle::onCollision(ofRectangle boundingBox) {
    // change our direction
    // direction = position - centre_of_bounding_box
    float yRatio = boundingBox.getWidth() / boundingBox.getHeight();

    vec2 v = _position - (boundingBox.getPosition() + (vec2(boundingBox.getWidth(), boundingBox.getHeight()) / 2));
    v = v * vec2(1, yRatio);
    v = normalize(rotate(v, ofDegToRad(45)));

    vec2 newdir;
    if (v.x <= 0 && v.y >= 0) { // bottom
        newdir = vec2(1, -1);
    } else if (v.x >= 0 && v.y <= 0) { // top
        newdir = vec2(1, -1);
    } else if (v.x >= 0 && v.y >= 0) { // right
        newdir = vec2(-1, 1);
    } else if (v.x <= 0 && v.y <= 0) { // left
        newdir = vec2(-1, 1);
    }

    _direction *= newdir;
}

bool Particle::getIsDead() {
    if ((_position.x > ofGetWidth() || _position.x < 0) || (_position.y > ofGetHeight() || _position.y < 0)) {
        return true;
    }
    return _lifetime > _lifespan;
}