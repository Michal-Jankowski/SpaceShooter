//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLECTIBLE_H
#define SPACESHOOTER_COLLECTIBLE_H



class Collectible : public GameModel {
public:
    Collectible(const std::string& path,glm::vec3 pos = glm::vec3(0));
    void update(SetupWindow &gScene) override;
    void onCollision(GameModel *other) override;
};


#endif //SPACESHOOTER_COLLECTIBLE_H
