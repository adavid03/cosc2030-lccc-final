// Xander David
// COSC2030 Final Project
// This file contains the implementation of the RecommendationEngine class.

#pragma once // <- Preprocessor directive to prevent multiple inclusions
#include "user.h"
#include "videostore.h"

class RecommendationEngine {
private: // <- Private member variables
    VideoStore* store; // <- Pointer to the video store

public: // <- Public member functions
    RecommendationEngine(VideoStore* store); // <- Constructor
    std::vector<Video*> recommend(const User& user, int maxResults = 10); // <- Recommend videos
};
