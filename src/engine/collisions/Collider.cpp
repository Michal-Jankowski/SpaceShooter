//
// Created by aklin on 15.11.2021.
//

#include "Collider.h"

Collider::Collider(Transform *transformRef) {
    this->transformRef = transformRef;
}

void Collider::drawDebug() {
    drawDebugImpl();
}
