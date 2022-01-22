
#ifndef SPACESHOOTER_GAMEOBJECT_H
#define SPACESHOOTER_GAMEOBJECT_H

#include <memory>
#include "Transform.h"
#include "../collisions/Collider.h"
#include "../core/SetupWindow.h"
#include "../text/GameHUD.h"

class GameObject {
public:
    explicit GameObject(SetupWindow* scene);

    virtual void update() {};
    virtual void drawHud(GameHUD* hud) {};
    virtual void render();
    virtual void reinit() {};

    [[nodiscard]] bool useCollision(GameObject* other) const;
    virtual bool isValidCollisionTarget(GameObject* other) const = 0;
    virtual void onCollision(GameObject* other);
    std::unique_ptr<Collider> col;
    bool awaitingDestroy = false;
protected:
    SetupWindow* scene;
};


#endif //SPACESHOOTER_GAMEOBJECT_H
