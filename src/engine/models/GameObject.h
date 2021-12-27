

#ifndef SPACESHOOTER_GAMEOBJECT_H
#define SPACESHOOTER_GAMEOBJECT_H


#include <memory>
#include "Transform.h"
#include "../collisions/Collider.h"
#include "../core/SetupWindow.h"
#include "../UI/GameHUD.h"


class GameObject {
public:
    virtual void update(SetupWindow* scene) {};
    virtual void drawHud(GameHUD* hud) {};

    virtual void render();

    [[nodiscard]] bool useCollision() const;
    //TODO: filter col by target pairs
    virtual void onCollision(GameObject* other);
    std::unique_ptr<Collider> col;
    bool awaitingDestroy = false;

    std::shared_ptr<Transform> transform;
};


#endif //SPACESHOOTER_GAMEOBJECT_H
