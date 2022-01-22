
#include "GameModel.h"
#include "../../game\models\Collectible.h"

GameModel::GameModel(SetupWindow* scene, const std::string& path, glm::vec3 position) : GameObject(scene) {

    mesh.loadModelFromFile(path);
    transform = std::make_unique<Transform>();
    transform->setPosition(position);
}

void GameModel::render() {
    if (dynamic_cast<Collectible*>(this)) {
        return;
    }
    mesh.render(transform->getMatrix());
}

void GameModel::reinit() {
    GameObject::reinit();
}






