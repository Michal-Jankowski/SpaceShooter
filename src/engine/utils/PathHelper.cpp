//
// Created by aklin on 01.11.2021.
//

#include <string>
#include "PathHelper.h"

const std::string PathHelper::texturePath = "res/img/";
const std::string PathHelper::modelPath = "res/model/";

std::string PathHelper::GetFullTexturePath(std::string filename) {
    return texturePath + filename;
}

std::string PathHelper::GetFullModelPath(std::string filename) {
    return modelPath + filename;
}
