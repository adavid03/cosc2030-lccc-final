// Xander David
// COSC2030 Final Project
// This file contains the implementation of the Video class.

#include "video.h"

// Default constructor
Video::Video() : duration(0) {
    // Initializes duration to 0; strings and vectors are auto-initialized
}

// Parameterized constructor
Video::Video(const std::string& id, const std::string& title, int duration, const std::string& desc,
            const std::vector<std::string>& userTags,
            const std::vector<std::string>& autoLikely,
            const std::vector<std::string>& autoPotential)
    : id(id), title(title), duration(duration), description(desc),
      userTags(userTags), autoTagsLikely(autoLikely), autoTagsPotential(autoPotential) {
    // Initializes all member variables using initializer list
}

// Destructor
Video::~Video() {
    // Nothing to clean up manually; STL containers clean up automatically
}
