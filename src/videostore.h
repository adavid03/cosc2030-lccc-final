// Xander David
// COSC2030 Final Project
// This file contains the implementation of the VideoStore class.

#pragma once // <- Preprocessor directive to prevent multiple inclusions
#include "hashtable.h"
#include <vector>
#include <string>

class VideoStore {
private:
    HashTable* videoTable; // <- Pointer to the hashtable

public:
    VideoStore(int capacity = 1000); // <- Constructor
    ~VideoStore(); // <- Destructor

    bool loadFromJsonl(const std::string& filename); // <- Loads the videos from the jsonl file
    Video* getVideoById(const std::string& id) const; // <- Gets the video by id
    void insertVideo(Video* video); // <- Inserts a video into the hashtable
    std::vector<Video*> getAllVideos() const; // <- Gets all videos
};
