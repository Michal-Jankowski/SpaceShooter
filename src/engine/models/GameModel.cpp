
#include "GameModel.h"
#include "../../game\models\Collectible.h"

GameModel::GameModel(const std::string& path, glm::vec3 position) {

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






