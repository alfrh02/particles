#include "areaEmitter.h"

AreaEmitter::AreaEmitter(vec2 pos, float spawnInterval, unsigned short maxParticles, ParticleType ptype)
: Emitter(pos, spawnInterval, maxParticles, ptype) {
    _editing = true;
    _captured = true;
}

AreaEmitter::AreaEmitter(vec2 pos, float spawnInterval, float rangeSpawnInterval, unsigned short maxParticles, ParticleType ptype)
: Emitter(pos, spawnInterval, rangeSpawnInterval, maxParticles, ptype) {
    _editing = true;
    _captured = true;
}

void AreaEmitter::update(double deltaTime) {
    _timeSinceLastSpawn += ofGetLastFrameTime();

    // most of this code is lifted from box.cpp
    if (!_captured) {
        if (_editing) {
            _editing = false;
        }
        return;
    }

    if (_editing) {
        _width = ofGetMouseX() - _position.x;
        _height = ofGetMouseY() - _position.y;

        if ((_width < 2 && _width > -2) || (_height < 2 && _height > -2)) {
            _width = 5;
            _height = 5;
        }

        _rect = ofRectangle(_position, _width, _height);
        _boundingBox = ofRectangle(_position, _width, _height);
    } else {
        _position = vec2(ofGetMouseX(), ofGetMouseY()) - vec2(_width, _height) / 2;

        _rect.setPosition(_position.x, _position.y);
        _boundingBox.setPosition(_position.x, _position.y);
    }
}

void AreaEmitter::drawEditMode() {
    ofSetColor(COLORS.FOREGROUND);

    if (_captured) {
        ofSetColor(COLORS.HIGHLIGHT);
    }

    ofNoFill();
    ofDrawRectangle(_rect);
    ofFill();
}

vec2 AreaEmitter::getSpawnPosition() {
    return _position + vec2(ofRandom(_width), ofRandom(_height));
}