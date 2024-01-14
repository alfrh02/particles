#include "box.h"

Box::Box(vec2 pos)
: SceneObject(pos) {
    _editing = true;
    _captured = true;
}

void Box::update(double deltaTime) {
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

void Box::draw() {
    ofSetColor(_color);
    ofDrawRectangle(_rect);
}
