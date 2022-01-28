
#include "Collider.h"

Collider::Collider(Transform *transformRef) {
    this->transformRef = transformRef;
}

void Collider::drawDebug() {
    drawDebugImpl();
}
