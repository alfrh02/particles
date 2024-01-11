#include "sceneObject.h"

SceneObject::SceneObject(vec2 pos, float w, float h, ofColor col)
: GrabbableEntity(pos, 0, col) {
    _width = w;
    _height = h;

    _editing = false;

    _boundingBox = ofRectangle(_position, w, h);
}

void SceneObject::update(double deltaTime) {
    if (_captured) {
        _position = vec2(ofGetMouseX(), ofGetMouseY());
    }
}