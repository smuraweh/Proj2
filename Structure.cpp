// This file contains all of the structures for myAppStore.

#include <iostream>
#include <string>

using namespace std;

struct app_info {
    string category; // name of category
    string app_name; // name of application
    string version; // version number
    float size; // size of application
    string units; // GB or MB
    float price; // Price in $ of app
};

struct tree {
    app_info record; // info about application
    struct tree *left = nullptr; // pointer to left subtree
    struct tree *right = nullptr; // pointer to right subtree
};

struct categories {
    string category; // name of category
    struct tree *root = nullptr; // points to the root of a tree
};

struct hash_table_entry {
    string app_name; // name of application
    struct tree *app_node; // pointer to node in tree containing application info
    struct hash_table_entry *next; // pointer to next entry in chain
};