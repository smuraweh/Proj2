// This file contains all of the structures for myAppStore.

#include <iostream>
#include <string>

using namespace std;

//#define CAT_NAME_LEN 25
//#define APP_NAME_LEN 50
//#define VERSION_LEN 10
//#define UNIT_SIZE 3

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
    tree *left; // pointer to left subtree
    tree *right; // pointer to right subtree
};

struct categories {
    string category; // name of category
    tree *root = nullptr; // points to the root of a tree
};
