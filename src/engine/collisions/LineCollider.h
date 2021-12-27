

#ifndef SPACESHOOTER_LINECOLLIDER_H
#define SPACESHOOTER_LINECOLLIDER_H


#include "Collider.h"
#include "../buffers/Line.h"

class LineCollider : public Collider {
public:
    LineCollider(std::shared_ptr<Transform> &transformRef, const glm::vec3 &lineStart, const glm::vec3 &lineEnd);
    bool isColliding(Collider* other) override;
    glm::vec3 getStart();
    glm::vec3 getEnd();

private:
    glm::vec3 lineStart;
    glm::vec3 lineEnd;
    void drawDebugImpl() override {}
};


#endif //SPACESHOOTER_LINECOLLIDER_H
