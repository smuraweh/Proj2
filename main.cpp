#include <iostream>
#include <string>
#include "Structure.cpp"
#include "prime.cc"

using namespace std;


void insertBST(tree *app);
void nodeInsert(tree *parent, tree *insert);
struct categories *myAppStore;
int hashTableSize(int numApplications);

int main() {

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

    struct hash_table_entry *hash_table;
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

        insertBST(ptr);
    }

    //cout << "Hash Table Size: "<< hashTableSize(numApps)<< endl;

    delete[] myAppStore;

    return 0;
}


void insertBST(tree *app) {
    // for loop to find category of app
    for(int i = 0; i < sizeof(*myAppStore); i++) {

        // if the category names are the same
        if(app->record.category == myAppStore[i].category) {

            // assign the app tree to the root if it is null
            if(myAppStore[i].root == nullptr) {
                myAppStore[i].root = app;
                // testing with cout
                // cout << "App: " << myAppStore[i].root->record.app_name << " successfully stored." << endl;
            }

            // if root is not null, use nodeInsert() to recursively insert to the next available position.
            else {
                nodeInsert(myAppStore[i].root, app);
                // testing with cout
                // cout << "App: " << myAppStore[i].root->record.app_name << " successfully stored." << endl;
            }
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