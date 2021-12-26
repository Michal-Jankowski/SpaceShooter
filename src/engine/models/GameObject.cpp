

#include "GameObject.h"


void GameObject::render() {
    if(useCollision()){
        col->drawDebug();
    }
}

void GameObject::onCollision(GameObject *other) {
    //std::cout << "colliding" << std::endl;
}

bool GameObject::useCollision() const {
    return col != nullptr;
}
