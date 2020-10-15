#include <iostream>
#include <string>
#include "Structure.cpp"

using namespace std;

int main() {

    int num_categories; // number of categories in array
    //num_categories = 3; // EXAMPLE
    cout << "Enter the number of categories of applications: ";
    cin >> num_categories;
    //cout << endl;

    // dynamically allocate an array of type "categories" of size n.
    struct categories *myAppStore;
    myAppStore = new struct categories[num_categories];

    // for-loop gathers category names and adds them to the array.
    for(int i = 0; i < num_categories; i++) {
        cout << "Enter the category name: ";
        string catName;
        cin >> catName;
        myAppStore[i].category = catName;
        myAppStore[i].root = nullptr;

    }



    return 0;
}
