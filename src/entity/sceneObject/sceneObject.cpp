#include "sceneObject.h"

SceneObject::SceneObject(vec2 pos, float size, ofColor col)
: Entity(pos, size, col) {
    _boundingBox = ofRectangle(pos, size, size);
}

void SceneObject::drawEditMode() {
    ofNoFill();
        ofSetColor(COLORS.HIGHLIGHT);
        ofDrawRectangle(_boundingBox);
    ofFill();
}

ofRectangle SceneObject::getBoundingBox() {
    return _boundingBox;
}