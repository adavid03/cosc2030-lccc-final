// Xander David
// COSC2030 Final Project
// This file contains the implementation of the User class.

#include "user.h"

User::User(const std::string& id) : id(id) {} // <- Constructor

bool User::hasWatched(const std::string& videoId) const {
    return watchedVideos.count(videoId) > 0; // <- Check if the user has watched a video
}

const std::unordered_map<std::string, int>& User::getTagScores() const {
    return tagScores; // <- Return the tag scores
}

void User::watchVideo(const std::string& videoId, const std::vector<std::string>& tags, int secondsWatched, int videoDuration) {
    watchedVideos.insert(videoId); // <- Insert the video id into the watched videos set
    float ratio = static_cast<float>(secondsWatched) / videoDuration; // <- Calculate the ratio of the video watched

    int weight = 1; // <- Default weight
    if (ratio >= 0.9f) weight = 5; // <- If the user watched almost all of the video, set the weight to 5
    else if (ratio >= 0.75f) weight = 3; // <- If the user watched most of the video, set the weight to 3
    else if (ratio >= 0.5f) weight = 2; // <- If the user watched half of the video, set the weight to 2

    for (const auto& tag : tags)
        tagScores[tag] += weight; // <- Add the weight to the tag score
}

void User::likeVideo(const std::string& videoId, const std::vector<std::string>& tags) {
    likedVideos.insert(videoId); // <- Insert the video id into the liked videos set
    for (const auto& tag : tags)
        tagScores[tag] += 4; // <- Add 4 to the tag score
}

void User::favoriteVideo(const std::string& videoId, const std::vector<std::string>& tags) {
    favoritedVideos.insert(videoId); // <- Insert the video id into the favorited videos set
    for (const auto& tag : tags)
        tagScores[tag] += 6; // <- Add 6 to the tag score
}

void User::commentOnVideo(const std::string& videoId, const std::vector<std::string>& tags) {
    for (const auto& tag : tags)
        tagScores[tag] += 2; // <- Add 2 to the tag score
}
