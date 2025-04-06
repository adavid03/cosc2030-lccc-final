// Xander David
// COSC2030 Final Project
// This file contains the implementation of the RecommendationEngine class.

#include "engine.h"
#include <unordered_set> // <- Include the unordered_set library
#include <algorithm> // <- Include the algorithm library

RecommendationEngine::RecommendationEngine(VideoStore* store) : store(store) {} // <- Constructor

std::vector<Video*> RecommendationEngine::recommend(const User& user, int maxResults) {
    const auto& tagScores = user.getTagScores(); // <- Get the tag scores
    std::vector<Video*> candidates; // <- Vector of video pointers
    std::unordered_map<Video*, int> videoScoreMap; // <- Map of video pointers to their scores

    const std::vector<Video*>& allVideos = store->getAllVideos(); // <- Get all videos

    for (Video* video : allVideos) {
        if (user.hasWatched(video->id)) continue; // <- If the user has watched the video, skip it

        int score = 0; // <- Initialize the score
        for (const auto& tag : video->userTags) { // <- Loop through the user tags
            if (tagScores.count(tag)) // <- If the tag is in the tag scores
                score += tagScores.at(tag); // <- Add the tag score to the score
        }
        for (const auto& tag : video->autoTagsLikely) { // <- Loop through the likely auto tags
            if (tagScores.count(tag)) // <- If the tag is in the tag scores
                score += tagScores.at(tag); // <- Add the tag score to the score
        }

        if (score > 0) {
            candidates.push_back(video); // <- Add the video to the candidates
            videoScoreMap[video] = score; // <- Add the score to the video score map
        }
    }

    std::sort(candidates.begin(), candidates.end(), [&](Video* a, Video* b) {
        return videoScoreMap[a] > videoScoreMap[b]; // <- Sort the candidates by score
    });

    if (candidates.size() > static_cast<size_t>(maxResults)) // <- If the number of candidates is greater than the max results
        candidates.resize(maxResults); // <- Resize the candidates to the max results

    return candidates; // <- Return the candidates
}
