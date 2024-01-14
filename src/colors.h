#pragma once

const struct {
    ofColor FOREGROUND = ofColor(0);             // black
    ofColor BACKGROUND = ofColor(190, 190, 208); // blue-tinted white
    ofColor HIGHLIGHT  = ofColor(255, 32, 32);    // red

    unsigned char SMOKE_ALPHA = 128;
    ofColor SMOKE[5] = {                         // varying levels of gray
        ofColor(24,  24,  24,  SMOKE_ALPHA),
        ofColor(48,  48,  48,  SMOKE_ALPHA),
        ofColor(72,  72,  72,  SMOKE_ALPHA),
        ofColor(96,  96,  96,  SMOKE_ALPHA),
        ofColor(120, 120, 120, SMOKE_ALPHA)
    };

    ofColor FIRE[5] = {
        ofColor(200, 25,  13,  SMOKE_ALPHA),
        ofColor(252, 140, 20,  SMOKE_ALPHA),
        ofColor(255, 187, 0,   SMOKE_ALPHA),
        ofColor(255, 96,  0,   SMOKE_ALPHA),
        ofColor(160, 30,  8,   SMOKE_ALPHA)
    };

    ofColor SPARK  = ofColor(255, 255, 0);        // yellow

    ofColor RAIN   = ofColor(96, 128, 200);       // blue

    ofColor BUBBLE = ofColor(100, 125, 150);      // light blue
} COLORS;