#pragma once

#include "sceneObject.h"

class Box : public SceneObject {
    public:
        Box(vec2 pos);

        void update(double deltaTime);
        void draw() override;

        void setRotation(float rotation);

    private:
        bool _editing;
};