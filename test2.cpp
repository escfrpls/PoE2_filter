#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Category {
    string name;
    vector<string> subcategories;
    unordered_map<string, vector<string>> baseItems;
};

unordered_map<string, Category> categories;
set<string> selectedItems;
string currentFilterFile = "";

void populateCategories() {
    categories = {
        {"One-Handed Weapons", {"One-Handed Weapons", {"Wands", "One-Handed Maces", "Sceptres"}, {}}},
        {"Two-Handed Weapons", {"Two-Handed Weapons", {"Bows", "Staves", "Two Hand Axes",
                                                       "Two Hand Maces", "Quarterstaves", "Crossbows"}, {}}},
        {"Off-hand", {"Off-hand", {"Quivers", "Shields", "Foci"}, {}}},
        {"Armour", {"Armour", {"Gloves", "Boots", "Body Armours", "Helmets"}, {}}},
        {"Jewellery", {"Jewellery", {"Amulets", "Rings", "Belts"}, {}}},
        {"Flasks", {"Flasks", {"Life Flasks", "Mana Flasks", "Charms"}, {}}},
        {"Currency", {"Currency", {"Stackable Currency", "Distilled Emotions",
                                   "Essence", "Splinter", "Catalysts"}, {}}},
        {"Waystones", {"Waystones", {"Waystones", "Map Fragments"}, {}}},
        {"Jewels", {"Jewels", {"Jewels"}, {}}}
    };

    // Armour - Boots
    categories["Armour"].baseItems["Boots"] = { "Rough Greaves", "Iron Greaves", "Bronze Greaves", "Trimmed Greaves", "Stone Greaves",
                                               "Reefsteel Greaves", "Monument Greaves", "Totemic Greaves", "Rawhide Boots", "Laced Boots",
                                               "Laced Boots", "Embossed Boots", "Steeltoe Boots", "Lizardscale Boots", "Flared Boots",
                                               "Leatherplate Boots", "Embroidered Boots", "Straw Sandals", "Wrapped Sandals", "Lattice Sandals",
                                               "Silk Slippers", "Feathered Sandals", "Flax Sandals", "Studded Sandals", "Elaborate Sandals",
                                               "Mail Sabatons", "Braced Sabatons", "Stacked Sabatons", "Covered Sabatons", "Flexile Sabatons",
                                               "Bold Sabatons", "Padded Leggings", "Secured Leggings", "Pelt Leggings", "Weaver Leggings",
                                               "Gilt Leggings", "Pious Leggings", "Frayed Shoes", "Threadd Shoes", "Hunting Shoes",
                                               "Steelpoint Shoes", "Velour Shoes", "Bladed Shoes", "Grand Cuisses", "Advanced Iron Greaves",
                                               "Advanced Bronze Greaves", "Advanced Trimmed Greaves", "Advanced Stone Greaves",
                                               "Advanced Laced Boots", "Advanced Embossed Boots", "Advanced Steeltoe Boots",
                                               "Advance Lizardscale Boots", "Advanced Wrapped Sandals", "Advanced Lattice Sandals",
                                               "Advanced Silk Slippers", "Advanced Feathered Sandals", "Advanced Mail Sabatons",
                                               "Advanced Braced Sabatons", "Advanced Stacked Sabatons", "Advanced Padded Leggings",
                                               "Advanced Secured Leggings", "Advanced Pelt Leggings", "Advanced Frayed Shoes",
                                               "Advanced Threaded Shoes", "Advanced Hunting Shoes", "Expert Iron Greaves",
                                               "Expert Trimmed Greaves", "Expert Stone Greaves", "Expert Laced Boots", "Expert Steeltoe Boots",
                                               "Expert Lizardscale Boots ", "Expert Wrapped Sandals", "Expert Silk Slippers",
                                               "Expert Feathered Sandals", "Expert Mail Sabatons", "Expert Braced Sabatons",
                                               "Expert Stacked Sabatons", "Expert Padded Leggings", "Expert Secured Leggings",
                                               "Expert Pelt Leggings", "Expert Frayed Shoes", "Expert Threaded Shoes", "Expert Hunting Shoes"};

    // Armour - Gloves
    categories["Armour"].baseItems["Gloves"] = {/* ... ваш список Gloves ...*/};

    // Off-hand - Foci
    categories["Off-hand"].baseItems["Foci"] = {/* ... ваш список Foci ...*/};

    // Off-hand - Shields
    categories["Off-hand"].baseItems["Shields"] = {/* ... ваш список Shields ...*/};

    // Off-hand - Quivers
    categories["Off-hand"].baseItems["Quivers"] = {/* ... ваш список Quivers ...*/};

    // Остальные категории и предметы (вставьте все ваши данные как в предыдущем ответе)
    // ...
    // [Вставьте ВСЕ данные из предыдущего ответа с полным списком предметов]
};

vector<string> splitString(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string item;
    while (getline(ss, item, ' ')) {
        if (!item.empty()) {
            result.push_back(item);
        }
    }
    return result;
}

void showMenu(const vector<string>& options, bool multiselect = false) {
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }
    if (multiselect) {
        cout << "\nEnter numbers separated by space (0 to cancel): ";
    } else {
        cout << "\nEnter your choice (0 to go back): ";
    }
}

void saveFilter() {
    if (currentFilterFile.empty()) {
        cout << "Enter filter file name: ";
        getline(cin, currentFilterFile);
        if (currentFilterFile.find(".filter") == string::npos) {
            currentFilterFile += ".filter";
        }
    }

    ofstream file(currentFilterFile);
    file << "Show\n";
    file << "    Class \"";

    set<string> classes;
    for (const auto& item : selectedItems) {
        for (const auto& [catName, category] : categories) {
            for (const auto& [subName, items] : category.baseItems) {
                if (find(items.begin(), items.end(), item) != items.end()) {
                    classes.insert(subName);
                }
            }
        }
    }

    for (const auto& className : classes) {
        file << "\"" << className << "\" ";
    }
    file << "\"\n";

    file << "    BaseType == \"";
    for (const auto& item : selectedItems) {
        file << item << " ";
    }
    file << "\"\n";
    file << "    SetTextColor 255 165 0\n";
    file << "    SetBackgroundColor 0 0 0 255\n";
    file << "    SetFontSize 40\n";
    file << "    MinimapIcon 0 White Star\n";

    cout << "Filter saved to " << currentFilterFile << endl;
}

void handleItems(const vector<string>& items) {
    vector<string> options = items;
    options.push_back("Add Selected");
    options.push_back("Remove Selected");
    options.push_back("Back");

    while (true) {
        cout << "\n--- Item Selection ---\n";
        showMenu(options);
        string input;
        getline(cin, input);

        if (input == "0") return;

        try {
            int choice = stoi(input);
            if (choice == options.size() - 2) {
                cout << "Enter item numbers to ADD: ";
                getline(cin, input);
                auto selections = splitString(input);
                for (const auto& s : selections) {
                    int idx = stoi(s) - 1;
                    if (idx >= 0 && idx < items.size()) {
                        selectedItems.insert(items[idx]);
                    }
                }
            }
            else if (choice == options.size() - 1) {
                cout << "Enter item numbers to REMOVE: ";
                getline(cin, input);
                auto selections = splitString(input);
                for (const auto& s : selections) {
                    int idx = stoi(s) - 1;
                    if (idx >= 0 && idx < items.size()) {
                        selectedItems.erase(items[idx]);
                    }
                }
            }
            else if (choice == options.size()) {
                return;
            }
        }
        catch (...) {
            cout << "Invalid input!\n";
        }
    }
}

void subMenu(const string& categoryName, const string& subcategory) {
    auto& items = categories[categoryName].baseItems[subcategory];
    vector<string> options = items;
    options.push_back("Back");

    while (true) {
        cout << "\n--- " << subcategory << " ---\n";
        showMenu(options, true);
        string input;
        getline(cin, input);

        if (input == "0") return;

        try {
            auto choices = splitString(input);
            for (const auto& c : choices) {
                int choice = stoi(c);
                if (choice > 0 && choice <= items.size()) {
                    handleItems(items);
                    return;
                }
            }
        }
        catch (...) {
            cout << "Invalid input!\n";
        }
    }
}

void mainMenu() {
    populateCategories();
    vector<string> mainOptions;
    for (const auto& [name, _] : categories) {
        mainOptions.push_back(name);
    }
    mainOptions.push_back("Save Filter");
    mainOptions.push_back("Exit");

    while (true) {
        cout << "\n=== Path of Exile 2 Filter Generator ===\n";
        showMenu(mainOptions);

        string input;
        getline(cin, input);

        try {
            int choice = stoi(input);
            if (choice == 0) break;

            if (choice == mainOptions.size() - 1) {
                saveFilter();
            }
            else if (choice == mainOptions.size()) {
                break;
            }
            else if (choice > 0 && choice <= categories.size()) {
                auto& category = categories[mainOptions[choice - 1]];
                vector<string> subOptions = category.subcategories;
                subOptions.push_back("Back");

                cout << "\n=== " << category.name << " ===\n";
                showMenu(subOptions);

                getline(cin, input);
                int subChoice = stoi(input);
                if (subChoice > 0 && subChoice <= category.subcategories.size()) {
                    subMenu(category.name, category.subcategories[subChoice - 1]);
                }
            }
        }
        catch (...) {
            cout << "Invalid input!\n";
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
