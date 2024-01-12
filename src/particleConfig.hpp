#pragma once

#include "particle.h"

using namespace glm;

enum ParticleType { spiral, smoke };

inline void SPIRAL_UPDATE(Particle &p) {
    // pos(n+1) = pos(n) + (speed * direction * 1/framerate)
    p.setPosition(p.getPosition() + (p.getSpeed() * p.getDirection() * 1/ofGetFrameRate()));
    p.setLifetime(p.getLifetime() + ofGetLastFrameTime());
}

inline void SMOKE_UPDATE(Particle &p) {
    cout << p.getPosition() << endl;
}

const struct {
    void (*UPDATE)(Particle&) = &SPIRAL_UPDATE;
    vec2 SPAWN_DIRECTION(double deltaTime) const { return vec2(sin(deltaTime), cos(deltaTime)); }
    unsigned char SIZE = 1;
    unsigned char SPEED = 100;
    char LIFETIME = -1;
    ofColor COLOR = COLORS.FOREGROUND;
} SPIRAL;

const struct {
    void (*UPDATE)(Particle&) = &SMOKE_UPDATE;
    vec2 SPAWN_DIRECTION(double deltaTime) const { return vec2(sin(deltaTime) / 10, ofClamp(cos(deltaTime), -0.001, -1)); }
    float SIZE() const { return ofRandom(4); };
    float SPEED = 10;
    float LIFETIME = 10;
    ofColor COLOR() const { int rand = (int)ofRandom(5); return COLORS.SMOKE[rand]; };
} SMOKE;
