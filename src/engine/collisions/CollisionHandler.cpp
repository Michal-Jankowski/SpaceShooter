

#include "CollisionHandler.h"
#include "LineCollider.h"

void CollisionHandler::registerCollider(GameObject *go) {
    colliders.push_back(go);
}

void CollisionHandler::deregisterCollider(GameObject *go) {
    for (int i = 0; i < colliders.size(); ++i) {
        if(colliders[i] == go){
            colliders.erase(colliders.begin()+i);
        }
    }
}

void CollisionHandler::runCollisionChecks() {
    for (int i = 0; i < colliders.size(); ++i) {
        if(drawDebug) {
            if (colliders[i]->useCollision(nullptr)) {
                colliders[i]->col->drawDebug();
            }
        }

        for (int j = i+1; j < colliders.size(); ++j) {
            if (colliders[i]->useCollision(colliders[j])
                || colliders[j]->useCollision(colliders[i])) {
                bool col = colliders[i]->col->isColliding(colliders[j]->col.get());
                if(col){
                    colliders[i]->onCollision(colliders[j]);
                    colliders[j]->onCollision(colliders[i]);
                }
            }
        }

    }
}

bool CollisionHandler::inLineOfSight(const GameModel &go1, const GameModel &go2, bool (*obstacle)(GameObject*)) {
    LineCollider lCollider = LineCollider(nullptr, go1.transform->getPosition(), go2.transform->getPosition());
    Line l = Line(lCollider.getStart(), lCollider.getEnd());

    for (auto & collider : colliders) {
       if(collider == &go1 || collider == &go2){
           continue;
       }
       if(!obstacle(collider)){
           continue;
       }
       if(drawDebug) {
           if (lCollider.isColliding(collider->col.get())) {
               l.setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
               l.draw();
               return false;
           }
       }
    }
    if(drawDebug) {
        l.setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        l.draw();
    }
    return true;
}
