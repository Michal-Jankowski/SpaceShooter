#include "GameObject.h"


GameObject::GameObject(SetupWindow *scene) : scene(scene) {}


void GameObject::render() {

}

void GameObject::onCollision(GameObject *other) {
    //std::cout << "colliding" << std::endl;
}

bool GameObject::useCollision(GameObject* other) const {
    if(col == nullptr){
        return false;
    }
    //Not checking for specific target
    else if(other == nullptr){
        return true;
    }
    else {
        return isValidCollisionTarget(other);
    }
}



