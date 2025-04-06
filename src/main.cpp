// Xander David
// COSC2030 Final Project
// This file contains the main function for the program.

#include "videostore.h"
#include "engine.h"
#include "user.h"
#include <iostream>
#include <algorithm>

void displayVideo(const Video* v) {
    std::cout << "- [" << v->id << "] " << v->title << " (" << v->duration << "s)\n";
    std::cout << "  Tags: ";
    for (const auto& tag : v->userTags) std::cout << tag << " ";
    std::cout << "\n\n"; // <- Display the video
}

int main() {
    VideoStore store(5000);
    if (!store.loadFromJsonl("videos.jsonl")) {
        std::cerr << "Failed to load video data.\n"; // <- Display an error message if the video data is not loaded
        return 1;
    }

    User user("simUser01"); // <- Create a user
    RecommendationEngine engine(&store); // <- Create a recommendation engine

    std::string mode;
    std::cout << "Choose mode: [manual / auto] → "; // <- Choose the mode
    std::cin >> mode;

    std::cout << "\n Creating user profile with 5 random videos...\n";
auto warmups = store.getAllVideos();
std::random_shuffle(warmups.begin(), warmups.end());

for (int i = 0; i < 5; ++i) {
    Video* v = warmups[i];
    user.watchVideo(v->id, v->userTags, v->duration - 1, v->duration);
    if (i % 2 == 0) user.likeVideo(v->id, v->userTags);
}


    for (int round = 1; round <= 5; ++round) {
        std::cout << "\n Round " << round << ": Getting recommendations...\n"; // <- Get recommendations
        auto recs = engine.recommend(user, 5); // <- Get the recommendations

        if (recs.empty()) {
            std::cout << "No more videos to recommend.\n"; // <- Display a message if there are no more videos to recommend
            break;
        }

        for (int i = 0; i < recs.size(); ++i) {
            std::cout << "[" << i << "] "; // <- Display the video
            displayVideo(recs[i]);
        }

        if (mode == "manual") {
            int choice;
            std::cout << "Choose a video to watch [0-" << recs.size() - 1 << "]: "; // <- Choose a video to watch
            std::cin >> choice;
            Video* chosen = recs[choice]; // <- Get the chosen video

            int watched;
            std::cout << "How many seconds did you watch? (max " << chosen->duration << "): "; // <- How many seconds did you watch
            std::cin >> watched;

            char liked, favorited, commented;
            std::cout << "Did you like it? [y/n]: "; // <- Did you like it
            std::cin >> liked;
            std::cout << "Did you favorite it? [y/n]: "; // <- Did you favorite it
            std::cin >> favorited;
            std::cout << "Did you comment on it? [y/n]: "; // <- Did you comment on it
            std::cin >> commented;

            user.watchVideo(chosen->id, chosen->userTags, watched, chosen->duration); // <- Watch the video
            if (liked == 'y') user.likeVideo(chosen->id, chosen->userTags); // <- Like the video
            if (favorited == 'y') user.favoriteVideo(chosen->id, chosen->userTags); // <- Favorite the video
            if (commented == 'y') user.commentOnVideo(chosen->id, chosen->userTags); // <- Comment on the video

        } else if (mode == "auto") {
            Video* chosen = recs[0]; // <- Get the chosen video
            user.watchVideo(chosen->id, chosen->userTags, chosen->duration - 3, chosen->duration); // <- Watch the video

            const auto& scores = user.getTagScores(); // <- Get the tag scores
            int tagScoreSum = 0; // <- Initialize the tag score sum
            for (const auto& tag : chosen->userTags) // <- Loop through the user tags
                if (scores.count(tag)) tagScoreSum += scores.at(tag); // <- Add the tag score to the tag score sum

            if (tagScoreSum >= 8) user.likeVideo(chosen->id, chosen->userTags); // <- Like the video
            if (tagScoreSum >= 12) user.favoriteVideo(chosen->id, chosen->userTags); // <- Favorite the video
            if (tagScoreSum >= 6) user.commentOnVideo(chosen->id, chosen->userTags); // <- Comment on the video

            std::cout << "Auto-user watched and interacted with: " << chosen->title << "\n"; // <- Display a message
        }
    }

    std::cout << "\n Simulation complete.\n"; // <- Display a message
    return 0;
}
