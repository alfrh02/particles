#include "box.h"

Box::Box(vec2 pos, float w, float h)
: GrabbableEntity(pos, 0) {
    _width = w;
    _height = h;

    rect = ofRectangle(_position, _width, _height);
}

void Box::update(double deltaTime) {
    if (_captured) {
        _position = vec2(ofGetMouseX(), ofGetMouseY());
    }
}

void Box::draw() {
    ofDrawRectangle(rect);
}