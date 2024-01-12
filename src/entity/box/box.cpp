#include "box.h"

Box::Box(vec2 pos, float w, float h, ofColor col)
: Entity(pos, 0, col) {
    _width = w;
    _height = h;

    _editing = false;

    _boundingBox = ofRectangle(_position, w, h);
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
        if ((_width < 2 && _width > -2) || (_height < 2 && _height > -2)) {
            cout << "too small!" << endl;

            _width = 5;
            _height = 5;
            _rect = ofRectangle(_position, _width, _height);
            _boundingBox = ofRectangle(_position, _width, _height);
        }
        _captured = false;
        _editing = false;
    }

    if (_captured && !_editing) {
        _position = vec2(ofGetMouseX(), ofGetMouseY()) - vec2(_width, _height) / 2;

        _rect.setPosition(_position.x, _position.y);
        _boundingBox.setPosition(_position.x, _position.y);
    }
}

void Box::draw() {
    ofSetColor(_color);
    ofDrawRectangle(_rect);
}

void Box::drawEditMode() {
    ofNoFill();
        ofSetColor(COLORS.BOUNDING_BOX);
        ofDrawRectangle(_boundingBox);

        ofSetColor(COLORS.DIRECTION);
        ofDrawLine(_position, _position + (_direction * _size));
    ofFill();
}

void Box::editMesh() {
    _editing = true;
    _captured = true;
}

ofRectangle Box::getBoundingBox() {
    return _boundingBox;
}