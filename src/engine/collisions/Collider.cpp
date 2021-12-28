//
// Created by aklin on 15.11.2021.
//

#include "Collider.h"

Collider::Collider(Transform *transformRef,bool drawDebug) {
    this->debugEnable = drawDebug;
    this->transformRef = transformRef;
}

void Collider::drawDebug() {
    if(debugEnable){
        drawDebugImpl();
    }
}
