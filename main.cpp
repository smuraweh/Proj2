#include <iostream>
#include <string>
#include "Structure.cpp"

using namespace std;


void insertBST(tree *app);
void nodeInsert(tree *parent, tree *insert);
struct categories *myAppStore;

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

        insertBST(&app);
    }

    return 0;
}


void insertBST(tree *app) {
    // for loop to find category of app
    for(int i = 0; i < sizeof(*myAppStore); i++) {
        if(app->record.category == myAppStore[i].category) {
            if(myAppStore[i].root == nullptr) {
                myAppStore[i].root = app;
                cout << "App: " << myAppStore[i].root->record.app_name << " successfully stored." << endl;
            }
            else {
                nodeInsert(myAppStore[i].root, app);
                cout << "App: " << myAppStore[i].root->record.app_name << " successfully stored." << endl;
            }
        }
    }
}

void nodeInsert(tree *parent, tree *insert) {
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