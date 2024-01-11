#pragma once

#include "sceneObject.h"

class Box : public SceneObject {
    public:
        Box(vec2 pos, float w, float h, ofColor col);

        void update(double deltaTime);
        void draw() override;

        void editMesh();

    private:
        ofRectangle _rect;
};