// Xander David
// COSC2030 Final Project
// This file contains the Video class that will be used to store the video data.

#pragma once // <- A preprocessor directive that tells the compiler to include this file only once
#include <string>
#include <vector>

class Video { // <- Each object will represent one video entry
public:
    std::string id; // <- The ID of the video
    std::string title; // <- The title of the video
    int duration; // <- The duration of the video
    std::string description; // <- The description of the video
    std::vector<std::string> userTags; // <- The user tags of the video
    std::vector<std::string> autoTagsLikely; // <- The likely auto tags of the video
    std::vector<std::string> autoTagsPotential; // <- The potential auto tags of the video

    Video(); // <- Creates a Video object with no data and fill it later.
    Video(const std::string& id, const std::string& title, int duration, const std::string& desc,
          const std::vector<std::string>& userTags,
          const std::vector<std::string>& autoLikely,
          const std::vector<std::string>& autoPotential); // <- Creates a Video object with all the data.

    ~Video(); // <- Destructor
};
