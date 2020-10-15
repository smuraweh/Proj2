#include <iostream>
#include <string>
#include "Structure.cpp"

using namespace std;

int main() {

    int num_categories; // number of categories in array
    //num_categories = 3; // EXAMPLE
    cout << "Enter the number of categories of applications: ";
    cin >> num_categories;
    cout << endl;

    // dynamically allocate an array of type "categories" of size n.
    struct categories *myAppStore;
    myAppStore = new struct categories[num_categories];

    //struct categories games; // EXAMPLE
    //games.category = "Games"; // EXAMPLE
    //games.root = nullptr; // EXAMPLE

    for(int i = 0; i < num_categories; i++) {
        cout << "Enter the category name: ";
        cin >> myAppStore[i].category;
        
    }



    return 0;
}
