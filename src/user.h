// Xander David
// COSC2030 Final Project
// This file contains the implementation of the User class.

#pragma once // <- Preprocessor directive to prevent multiple inclusions
#include <string>
#include <vector>
#include <unordered_map> // <- Include the unordered_map library
#include <unordered_set> // <- Include the unordered_set library

class User {
private:
    std::unordered_map<std::string, int> tagScores; // <- Private member variable for tag scores

public:
    std::string id; // <- Public member variable for id
    std::unordered_set<std::string> watchedVideos; // <- Public member variable for watched videos
    std::unordered_set<std::string> likedVideos; // <- Public member variable for liked videos
    std::unordered_set<std::string> favoritedVideos; // <- Public member variable for favorited videos

    User(const std::string& id); // <- Constructor

    void watchVideo(const std::string& videoId, const std::vector<std::string>& tags, int secondsWatched, int videoDuration); // <- Watch a video
    void likeVideo(const std::string& videoId, const std::vector<std::string>& tags); // <- Like a video
    void favoriteVideo(const std::string& videoId, const std::vector<std::string>& tags); // <- Favorite a video
    void commentOnVideo(const std::string& videoId, const std::vector<std::string>& tags); // <- Comment on a video
    
    const std::unordered_map<std::string, int>& getTagScores() const; // <- Get the tag scores
    bool hasWatched(const std::string& videoId) const; // <- Check if the user has watched a video
};
