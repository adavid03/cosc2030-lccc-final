// Xander David
// COSC2030 Final Project
// This file contains the HashTable class that will be used to store the video data.

#pragma once // <- A preprocessor directive that tells the compiler to include this file only once
#include "video.h"

class HashTable {
private:
    struct Node {
        std::string key; // <- The key of the node
        Video* videoPtr; // <- A pointer to the video object
        Node* next; // <- A pointer to the next node

        Node(const std::string& key, Video* videoPtr)
            : key(key), videoPtr(videoPtr), next(nullptr) {} // <- Initializes the node with the key and video pointer
    };

    Node** table; // <- A pointer to the table
    int capacity; // <- The capacity of the table

    int hash(const std::string& key) const; // <- A hash function that returns the hash value of the key

public:
    HashTable(int cap = 100); // <- A constructor that initializes the table with a capacity of 100
    ~HashTable(); // <- A destructor that deletes the table

    void insert(const std::string& key, Video* video); // <- A function that inserts a video into the table
    Video* get(const std::string& key) const; // <- A function that returns a video from the table
    void remove(const std::string& key); // <- A function that removes a video from the table
    std::vector<Video*> getAll() const; // <- Gets all the videos for the getAll function in VideoStore
};
