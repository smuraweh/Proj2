#include <iostream>
#include <string>
#include "Structure.cpp"
#include<stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;


void insertBST(tree *app);
void nodeInsert(tree *parent, tree *insert);
int hashTableSize(int numApplications);
int hashValue(tree * app, int k);
void hash_function(tree *app, hash_table_entry *table, int pos);
void findApp(string appName, int tableSize);
bool TestForPrime( int val );
struct categories *myAppStore;
struct hash_table_entry *hash_table;

int main(int argc, char *argv[]) {

    int numCategories; // number of categories in array.

    // prompt to ask for user input.
    cout << "Enter the number of categories of applications: ";
    cin >> numCategories;
    cin.ignore();

    // dynamically allocate an array of type "categories" of size n.
    myAppStore = new struct categories[numCategories];

    // for-loop gathers category names and adds them to the array.
    for(int i = 0; i < numCategories; i++) {
        string catName;
        cout << "Enter the category name: ";
        getline(cin, catName);
        myAppStore[i].category = catName;
        myAppStore[i].root = nullptr;
    }

    // prompt for number of applications to add to myAppStore.
    int numApps;
    cout << "Enter number of applications to add: ";
    cin >> numApps;
    cin.ignore();

    int k = hashTableSize(numApps);
    hash_table = new struct hash_table_entry[k];

    // for-loop gathers app info and adds them to the array.
    for(int i = 0; i < numApps; i++) {
        struct tree app;
        cout << "Enter the app category for app #" << i+1 << ": ";
        getline(cin, app.record.category);

        //cin >> app.record.category;
        //cin.ignore();

        cout << "Enter the app name: ";
        getline(cin, app.record.app_name);

        cout << "Enter the version number: ";
        cin >> app.record.version;

        cout << "Enter the size of the application: ";
        cin >> app.record.size;

        cout << "Enter the units corresponding to the size (MB or GB): ";
        string units;
        cin >> units;
        while (units != "MB" && units != "GB") {
            cout << "Please enter either MB or GB for the units: ";
            cin >> units;
        }
        app.record.units = units;

        cout << "Enter the price of the application: ";
        cin >> app.record.price;
        cin.ignore();

        struct tree *ptr;
        ptr = &app;

        insertBST(ptr); // inserts to Binary Search Tree

        int hashPos = hashValue(ptr, k);
        hash_function(ptr, hash_table, hashPos); // hashes to hash table
    }

    while(!cin.eof()){
        string input;
        getline(cin, input);

        if(input.substr(0, 8) == "find app "){
            string name = input.substr(9, input.length()-1);
            findApp(name, k);
        }
        if(input == "no report")
            break;
    }
    delete[] myAppStore;

    return 0;
}


void insertBST(tree *app) {
    // for loop to find category of app
    for(int i = 0; i < sizeof(*myAppStore); i++) {

        // if the category names are the same
        if(app->record.category == myAppStore[i].category) {

            // assign the app tree to the root if it is null
            if(myAppStore[i].root == nullptr)
                myAppStore[i].root = app;
                // testing with cout
                // cout << "App: " << myAppStore[i].root->record.app_name << " successfully stored." << endl;

            // if root is not null, use nodeInsert() to recursively insert to the next available position.
            else
                nodeInsert(myAppStore[i].root, app);
                // testing with cout
                // cout << "App: " << myAppStore[i].root->record.app_name << " successfully stored." << endl;
        }
    }
}

// Pass the main tree and the tree to be inserted as pointers (better for memory allocation)
void nodeInsert(tree *parent, tree *insert) {
    // run comparisons to find position
    if (insert->record.app_name >= parent->record.app_name) {
        if (parent->left == nullptr)
            parent->left = insert;
        else
            nodeInsert(parent->left, insert);
    } else {
        if (parent->right == nullptr)
            parent->right = insert;
        else
            nodeInsert(parent->right, insert);
    }
}

// Returns the value of the hashtable to be allocated
int hashTableSize(int numApplications) {
    // k is the hash table size
    int k;
    k = 2 * numApplications;

    // while loop runs to increment k until it returns prime
    while (TestForPrime(k) == 0)
        k++;

    return k;
}

int hashValue(tree * app, int k) {
    int sum = 0;
    int i = 0;

    while (i < app->record.app_name.length()) {
        sum += app->record.app_name[i];
        i++;
    }

    int hashValue = sum%k;
    return hashValue;
}

void hash_function(tree *app, hash_table_entry *table, int pos) {
    // run comparisons to find position
    if (table[pos].app_name.empty()) {
            table[pos].app_name = app->record.app_name;
            table[pos].next = nullptr;
            table[pos].app_node = app;
            cout << table[pos].app_name << " was successfully hashed to position " << pos << "." << endl;
    } else {
        hash_table_entry *ptr;
        /*while (ptr->app_name.empty())
            ptr = ptr->next;
        ptr->app_name = app->record.app_name;
        ptr->next = nullptr;
        ptr->app_node = app;
        cout << table[pos].app_name << " was successfully hashed to position " << pos << "." << endl;*/

        ptr->next = &table[pos];
        ptr->app_name = app->record.app_name;
        ptr->app_node = app;
        cout << table[pos].app_name << " was successfully hashed to position " << pos << "." << endl;

        free(ptr);
    }
}

void findApp(string appName, int tableSize) {
    int sum = 0;
    int i = 0;
    bool found = false;

    while (i < appName.length()) {
        sum += appName[i];
        i++;
    }

    int pos = sum%tableSize;
    hash_table_entry *ptr;
    *ptr = hash_table[pos];

    while(ptr->next != nullptr) {
        if (ptr->app_name == appName) {
            cout << "Found Application: " << appName << endl;
            cout << "\tCategory: " << ptr->app_node->record.category << endl;
            cout << "\tApplication Name: " << ptr->app_node->record.app_name << endl;
            cout << "\tVersion: " << ptr->app_node->record.version << endl;
            cout << "\tSize: " << ptr->app_node->record.size << endl;
            cout << "\tUnits: " << ptr->app_node->record.units << endl;
            cout << "\tPrice: $" << ptr->app_node->record.price << endl;

            found = true;
        }
        else {
            ptr = ptr->next;
        }
    }
    if(found != true)
        cout << "Application " << appName << " not found." << endl;
}

bool TestForPrime( int val ){
    int limit, factor = 2;
    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;
    return( factor > limit );
}