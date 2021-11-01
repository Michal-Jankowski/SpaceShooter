//
// Created by aklin on 01.11.2021.
//

#ifndef SPACESHOOTER_PATHHELPER_H
#define SPACESHOOTER_PATHHELPER_H


class PathHelper {
public:
    static std::string GetFullTexturePath(std::string filename);
    static std::string GetFullModelPath(std::string filename);

private:
   static const std::string texturePath;
   static const std::string modelPath;

};


#endif //SPACESHOOTER_PATHHELPER_H
