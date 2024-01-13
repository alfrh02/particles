#include "sparkParticle.h"

SparkParticle::SparkParticle(vec2 pos, vec2 dir, float size, float speed, unsigned short lifespan, ofColor col)
: Particle(pos, dir, size, speed, lifespan, col) {
    _type = "Spark";
}

void SparkParticle::update(double deltaTime) {
    _position += _speed * _direction * 1/ofGetFrameRate();

    if (_direction.y < 0.98) {
        _direction.y += (_speed / 8) * 1/ofGetFrameRate();
    }

    _lifetime += ofGetLastFrameTime();
}

void SparkParticle::onCollision(ofRectangle boundingBox) {
    // change our direction
    // direction = position - centre_of_bounding_box
    float yRatio = boundingBox.getWidth() / boundingBox.getHeight();

    vec2 v = _position - (boundingBox.getPosition() + (vec2(boundingBox.getWidth(), boundingBox.getHeight()) / 2));
    v = v * vec2(1, yRatio);
    v = normalize(rotate(v, ofDegToRad(45)));

    vec2 newdir;
    if (v.x <= 0 && v.y >= 0) {        // bottom
        newdir = vec2(1, -1);
    } else if (v.x >= 0 && v.y <= 0) { // top
        newdir = vec2(1, -1);
    } else if (v.x >= 0 && v.y >= 0) { // right
        newdir = vec2(-1, 1);
    } else if (v.x <= 0 && v.y <= 0) { // left
        newdir = vec2(-1, 1);
    }

    _direction *= newdir;

    _lifetime += _lifespan / 2;
}