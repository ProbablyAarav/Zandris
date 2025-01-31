#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include "item.h"
using namespace std;
// Inventory arrays
map<item, int> food; // Stores a user's food
map<item, int> weapons; // Stores a user's unequipped weapons
map<item, int> gear; // Stores a user's unequipped armour & artifacts
map<string, int> stat = {{"Strength", 1}, {"Defense", 1}, {"Intelligence", 1}, {"HP", 10}, {"Level", 1}}; // User stats
vector<string> skills; // Stores skills a user can use (may be included with weapons)
/*Stores a user's equipped items*/map<string, item> equipped = {{"Weapon", item("", "", 0)}, {"Helmet", item("", "", 0)}, {"Breastplate", item("", "", 0)}, {"Gloves", item("", "", 0)}, {"Mask", item("", "", 0)}, {"Artifact 1", item("", "", 0)}, {"Artifact 2", item("", "", 0)}, {"Artifact 3", item("", "", 0)}, {"Artifact 4", item("", "", 0)}, {"Artifact 5", item("", "", 0)}};
vector<item> ground; // Shows items on the ground
int c; // Counter for printing numbers
void inventory(){ // Functions for printing a user's inventory
    /*Instructions*/ cout << "For food: f\nFor weapons: w\nFor gear: g\nFor skills: s\nFor all items: i\nEnter your option (leave blank to exit this menu): ";
    char option;
    cin >> option;
    // Printing individual inventory menus
    if (option == 'f'){
        for (auto pair : food) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
    }
    else if (option == 'w'){
        for (const auto& pair : weapons) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
    }
    else if (option == 'g'){
        for (const auto& pair : gear) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
    }
    else if (option == 's'){
        for (string skill : skills) {
            cout << skill << "\n";
        }
    }
    // Print whole inventory
    else if(option == 'i'){
        cout << "ALL FOOD:\n";
        for (const auto& pair : food) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
        cout << "ALL WEAPONS:\n";
        for (const auto& pair : weapons) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
        cout << "ALL GEAR:\n";
        for (const auto& pair : gear) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
        cout << "ALL SKILLS:\n";
        for (string skill : skills) {
            cout << skill << " x" << skill << "\n";
        }
    }
}
void pick(){ // Picks up an item from the ground
    if (ground.empty()) cout << "There's nothing on the ground right now!\n";
    c = 1;
    for (item i : ground){ // Prints items on the ground
        string itemType = i.getType();
        transform(itemType.begin(), itemType.end(), itemType.begin(), ::toupper);
        cout << "Currently on the ground:\n" << c << ": " << i.getName() << " [" << itemType << "]" << "\n";
        c++;
    }
    int choice;
    while (true) {
        cout << "Enter the number of the item you want to pick up (0 to leave): ";
        if (!(cin >> choice)) {
            // If the input is not an integer, clear the error & ignore invalid input
            cin.clear(); // Clear error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
            cout << "Invalid input. Please enter a valid number.\n";
            continue; // Continue the code
        }
        // cin >> choice;
        if (choice == 0) break;
        else if (choice < 1 || choice > ground.size()) { // Runs if choice isn't valid
            cout << "Invalid choice. Please select a valid item number.\n";
        }
        else break;
    }
    if (choice == 0) return;
    item selected = ground[choice - 1];
    string itemType = selected.getType();
    if (ground[choice - 1].getType() == "Weapon"){
        if (weapons.find(selected) == weapons.end()) weapons[selected] = 1;
        else weapons[selected]++;
        cout << "Picked up weapon: " << selected.getName() << "\n";
    }
    else if (ground[choice - 1].getType() == "Food"){
        if (food.find(selected) == food.end()) food[selected] = 1;
        else food[selected]++;
        cout << "Picked up food: " << selected.getName() << "\n";
    }
    else if (ground[choice - 1].getType() == "Artifact" || ground[choice - 1].getType() == "Helmet" || ground[choice - 1].getType() == "Breastplate" || ground[choice - 1].getType() == "Mask" || ground[choice - 1].getType() == "Gloves"){
        if (gear.find(selected) == gear.end()) gear[selected] = 1;
        else gear[selected]++;
        cout << "Picked up gear: " << selected.getName() << "\n";
    }
    ground.erase(ground.begin() + (choice - 1));
    if (ground.empty()) cout << "There's nothing left on the ground.\n";
    else {
        cout << "Items left on the ground: ";
        for (int i = 0; i < ground.size(); i++) {
            string itemType = ground[i].getType();
            transform(itemType.begin(), itemType.end(), itemType.begin(), ::toupper);
            cout << i + 1 << ": " << ground[i].getName() << " [" << itemType << "]\n";
        }
        cout << "Type p again to pick up another item.\n";
    }
}
void equip(){ // Lets the user equip an item
    // item toEquip = item("", "", 0);
    // c = 1;
    cout << "Please select a category of item to equip\n\n";
    cout << "For weapons: w\nFor gear/ artifacts: g\nEnter your option (leave blank to exit this menu): ";
    item toEquip = item("", "", 0);
    c = 1;
    char option;
    cin >> option;
    if (option == 'w'){
        for (const auto& pair : weapons) {
            cout << c << ": " << pair.first.getName() << " x" << pair.second << "\n";
            c++;
        }
        int o;
        while (true) {
            cout << "Enter the number of the item you want to equip (0 to leave): ";
            if (!(cin >> o)) {
                // If the input is not an integer, clear the error & ignore invalid input
                cin.clear(); // Clear error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
                cout << "Invalid input. Please enter a valid number.\n";
                continue; // Continue the code
            }
            // cin >> choice;
            else if (o == 0) break;
            else if (o < 1 || o > weapons.size()) { // Runs if choice isn't valid
                cout << "Invalid choice. Please select a valid item number.\n";
            }
            else break;
        }
        if (o > 0 && o <= weapons.size()){
            auto it = next(weapons.begin(), o - 1); 
            toEquip = it->first;
            equipped["Weapon"] = toEquip; 
            stat["Strength"] += toEquip.getPower();
            weapons[toEquip]--;
            if (weapons[toEquip] == 0) weapons.erase(toEquip);
        }
    }
    else if (option == 'g'){
        for (const auto& pair : gear) {
            cout << c << ": " << pair.first.getName() << " x" << pair.second << "\n";
            c++;
        }
        int o;
        cout << "Enter an item's number";
        while (true) {
            cout << "Enter the number of the item you want to pick up (0 to leave): ";
            if (!(cin >> o)) {
                // If the input is not an integer, clear the error & ignore invalid input
                cin.clear(); // Clear error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
                cout << "Invalid input. Please enter a valid number.\n";
                continue; // Continue the code
            }
            if (o == 0) break;
            else if (o < 1 || o > gear.size()) { // Runs if choice isn't valid
                cout << "Invalid choice. Please select a valid item number.\n";
            }
            else break;
        }
        if (o != 0 && o <= gear.size()){
            auto it = next(gear.begin(), o - 1);
            toEquip = it->first;
            if (toEquip.getType() == "Helmet"){
                equipped["Helmet"] = toEquip; 
                stat["HP"] += toEquip.getPower();
                gear[toEquip]--;
                if (gear[toEquip] == 0) gear.erase(toEquip);
            }
            else if (toEquip.getType() == "Breastplate"){
                equipped["Breastplate"] = toEquip; 
                stat["HP"] += toEquip.getPower();
                gear[toEquip]--;
                if (gear[toEquip] == 0) gear.erase(toEquip);
            }
            else if (toEquip.getType() == "Gloves"){
                equipped["Gloves"] = toEquip; 
                stat["Strength"] += toEquip.getPower();
                gear[toEquip]--;
                if (gear[toEquip] == 0) gear.erase(toEquip);
            }
            else if (toEquip.getType() == "Mask"){
                equipped["Mask"] = toEquip; 
                stat["HP"] += toEquip.getPower();
                gear[toEquip]--;
                if (gear[toEquip] == 0) gear.erase(toEquip);
            }
            // Checks for artifact slots and adds to the lowest one. If full, warns the user.
            else if (toEquip.getType() == "Artifact"){
                if (equipped["Artifact 5"].getName() != ""){
                    cout << "You have too many artifacts equipped (Max 5).";
                    return;
                }
                else {
                    if (equipped["Artifact 4"].getName() != ""){
                        equipped["Artifact 5"] = toEquip;
                        gear[toEquip]--;
                        if (gear[toEquip] == 0) gear.erase(toEquip);
                    }
                    else {
                        if (equipped["Artifact 3"].getName() != ""){
                            equipped["Artifact 4"] = toEquip;
                            gear[toEquip]--;
                            if (gear[toEquip] == 0) gear.erase(toEquip);
                        }
                        else{
                            if (equipped["Artifact 2"].getName() != ""){
                                equipped["Artifact 1"] = toEquip;
                                gear[toEquip]--;
                                if (gear[toEquip] == 0) gear.erase(toEquip);
                            }
                        }
                    }
                }
            }
        } 
    }
}
void unequip(){ // Lets the user unequip/ take off an item
    cout << "Please select a category of item to equip\n\n";
    cout << "For weapon: w\nFor gear/ artifacts: g\nEnter your option (leave blank to exit this menu): ";
    c = 1;
    char option;
    cin >> option;
    if (option == 'w'){
        if (equipped["Weapon"].getName() != ""){
            item putBack = item(equipped["Weapon"].getName(), equipped["Weapon"].getType(), equipped["Weapon"].getPower());
            stat["Strength"] -= equipped["Weapon"].getPower();
            weapons[putBack]++;
            if (weapons.find(putBack) != weapons.end()) weapons[putBack]++;
            else weapons[putBack] = 1;
        }
    }
    if (option == 'g'){
        vector<item> u;
        c = 1;
        if (equipped["Helmet"].getName() != ""){
            cout << c << ") Current helmet: " << equipped["Helmet"].getName();
            u.push_back(equipped["Helmet"]);
            c++;
        }
        if (equipped["Breastplate"].getName() != ""){
            cout << c << ") Current breastplate: " << equipped["Breastplate"].getName();
            u.push_back(equipped["Breastplate"]);
            c++;
        }
        if (equipped["Gloves"].getName() != ""){
            cout << c << ") Current gloves: " << equipped["Gloves"].getName();
            u.push_back(equipped["Gloves"]);
            c++;
        }
        if (equipped["Mask"].getName() != ""){
            cout << c << ") Current mask: " << equipped["Mask"].getName();
            u.push_back(equipped["Mask"]);
            c++;
        }
        if (equipped["Artifact 1"].getName() != ""){
            cout << c << ") Current artifact in slot 1: " << equipped["Artifact 1"].getName();
            u.push_back(equipped["Artifact 1"]);
            c++;
        }
        if (equipped["Artifact 2"].getName() != ""){
            cout << c << ") Current artifact in slot 2: " << equipped["Artifact 2"].getName();
            u.push_back(equipped["Artifact 2"]);
            c++;
        }
        if (equipped["Artifact 3"].getName() != ""){
            cout << c << ") Current artifact in slot 3: " << equipped["Artifact 3"].getName();
            u.push_back(equipped["Artifact 3"]);
            c++;
        }
        if (equipped["Artifact 4"].getName() != ""){
            cout << c << ") Current artifact in slot 4: " << equipped["Artifact 4"].getName();
            u.push_back(equipped["Artifact 4"]);
            c++;
        }
        if (equipped["Artifact 5"].getName() != ""){
            cout << c << ") Current artifact in slot 5: " << equipped["Artifact 5"].getName();
            u.push_back(equipped["Artifact 5"]);
            c++;
        }
        int o;
        while (true) {
            cout << "Enter the number of the item you want to unequip (0 to leave): ";
            if (!(cin >> o)) {
                // If the input is not an integer, clear the error & ignore invalid input
                cin.clear(); // Clear error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
                cout << "Invalid input. Please enter a valid number.\n";
                continue; // Continue the code
            }
            // cin >> choice;
            else if (o == 0) break;
            else if (o < 1 || o > gear.size()) { // Runs if choice isn't valid
                cout << "Invalid choice. Please select a valid item number.\n";
            }
            else break;
        }
        item putBack = u[o - 1];
        string idk = putBack.getType();
        if (equipped[putBack.getType()].getName() != ""){
            if (gear.find(putBack) != gear.end()) gear[putBack]++;
            else gear[putBack] = 1;
        }
    }
}