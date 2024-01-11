#include "box.h"

Box::Box(vec2 pos, float w, float h, ofColor col)
: SceneObject(pos, w, h, col) {
    _rect = ofRectangle(_position, _width, _height);
    editMesh();
}

void Box::update(double deltaTime) {
    if (_editing && _captured) {
        _width = ofGetMouseX() - _position.x;
        _height = ofGetMouseY() - _position.y;

        _rect = ofRectangle(_position, _width, _height);
        _boundingBox = ofRectangle(_position, _width, _height);
    } else if (_editing) {
        _captured = false;
        _editing = false;
    }

    if (_captured && !_editing) {
        _position = vec2(ofGetMouseX(), ofGetMouseY());

        _rect.setPosition(_position.x, _position.y);
        _boundingBox.setPosition(_position.x, _position.y);
    }
}

void Box::draw() {
    ofSetColor(_color);
    ofDrawRectangle(_rect);
}

void Box::editMesh() {
    _editing = true;
    _captured = true;
}