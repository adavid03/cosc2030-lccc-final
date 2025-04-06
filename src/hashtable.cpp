// Xander David
// COSC2030 Final Project
// This file contains the implementation of the HashTable class.

#include "hashtable.h"
#include <iostream>

HashTable::HashTable(int cap) : capacity(cap) {
    table = new Node*[capacity];
    for (int i = 0; i < capacity; ++i)
        table[i] = nullptr;
} // <- Initializes the table with a capacity of cap

HashTable::~HashTable() {
    for (int i = 0; i < capacity; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete->videoPtr;  // delete the video
            delete toDelete;            // delete the node
        }
    }
    delete[] table;
} // <- Deletes the table

int HashTable::hash(const std::string& key) const {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;
    return hash % capacity;
} // <- Returns the hash value of the key

void HashTable::insert(const std::string& key, Video* video) {
    int index = hash(key);
    Node* newNode = new Node(key, video);

    newNode->next = table[index];
    table[index] = newNode;
} // <- Inserts a video into the table

Video* HashTable::get(const std::string& key) const {
    int index = hash(key);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key)
            return current->videoPtr;
        current = current->next;
    }
    return nullptr;
} // <- Returns a video from the table

void HashTable::remove(const std::string& key) {
    int index = hash(key);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr)
                table[index] = current->next;
            else
                prev->next = current->next;

            delete current->videoPtr;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
} // <- Removes a video from the table

std::vector<Video*> HashTable::getAll() const {
    std::vector<Video*> allVideos;
    for (int i = 0; i < capacity; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            allVideos.push_back(current->videoPtr);
            current = current->next;
        }
    }
    return allVideos;
}
