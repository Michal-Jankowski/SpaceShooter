//
// Created by aklin on 15.11.2021.
//

#ifndef SPACESHOOTER_COLLECTIBLE_H
#define SPACESHOOTER_COLLECTIBLE_H


#include "../GameModel.h"

class Collectible : public GameModel {
public:
    explicit Collectible(const std::string &modelPath);
};


#endif //SPACESHOOTER_COLLECTIBLE_H
