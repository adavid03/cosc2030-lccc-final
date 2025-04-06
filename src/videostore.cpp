// Xander David
// COSC2030 Final Project
// This file contains the implementation of the VideoStore class.

#include "videostore.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp> // <- Include the json library

using json = nlohmann::json; // <- Use the json library

VideoStore::VideoStore(int capacity) {
    videoTable = new HashTable(capacity); // <- Initialize the hashtable
}

VideoStore::~VideoStore() {
    delete videoTable; // <- Delete the hashtable
}

void VideoStore::insertVideo(Video* video) {
    videoTable->insert(video->id, video); // <- Insert the video into the hashtable
}

Video* VideoStore::getVideoById(const std::string& id) const {
    return videoTable->get(id); // <- Get the video from the hashtable
}

bool VideoStore::loadFromJsonl(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open " << filename << "\n";
        return false; // <- Return false if the file is not open
    }

    std::string line;
    while (std::getline(inFile, line)) {
        json j;
        try {
            j = json::parse(line);
        } catch (...) {
            std::cerr << "Skipping invalid JSON line\n";
            continue; // <- Skip the line if it is invalid
        }

        auto* video = new Video(
            j["id"], // <- Get the id
            j["title"], // <- Get the title
            j["duration"], // <- Get the duration
            j["description"], // <- Get the description
            j["user_tags"].get<std::vector<std::string>>(), // <- Get the user tags
            j["auto_tags"]["likely"].get<std::vector<std::string>>(), // <- Get the likely auto tags
            j["auto_tags"]["potential"].get<std::vector<std::string>>() // <- Get the potential auto tags
        );

        insertVideo(video); // <- Insert the video into the hashtable
    }

    inFile.close(); // <- Close the file
    return true;
}

std::vector<Video*> VideoStore::getAllVideos() const {
    return videoTable->getAll();
}