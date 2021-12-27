

#ifndef SPACESHOOTER_LINECOLLIDER_H
#define SPACESHOOTER_LINECOLLIDER_H


#include "Collider.h"
#include "../buffers/Line.h"

class LineCollider : public Collider {
public:
    LineCollider(std::shared_ptr<Transform> &transformRef, Line* lineRef);
    bool isColliding(Collider* other) override;
    glm::vec3 getStart();
    glm::vec3 getEnd();
private:
    Line* lineRef;
};


#endif //SPACESHOOTER_LINECOLLIDER_H
