//
// Created by aklin on 15.11.2021.
//

#include "Collider.h"

Collider::Collider(bool drawDebug) {
    this->debugEnable = drawDebug;
}

void Collider::drawDebug() {
    if(debugEnable){
        drawDebugImpl();
    }
}
