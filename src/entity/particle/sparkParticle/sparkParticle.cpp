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

    _lifetime += _lifespan / 2;
}