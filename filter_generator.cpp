#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>

// Structure for categories and subcategories
struct Category {
    std::string name;
    std::vector<std::string> subcategories;
    std::unordered_map<std::string, std::vector<std::string>> baseItems; // To store base items by subcategories
};

// Function to display options list
void displayOptions(const std::vector<std::string>& options) {
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
    std::cout << "Enter the numbers of the selected options separated by commas (e.g., 1,3,4): ";
}

// Function to select multiple options
std::vector<int> getMultipleChoices(const std::vector<std::string>& options) {
    std::string input;
    std::vector<int> choices;

    while (true) {
        displayOptions(options);
        std::getline(std::cin, input);  // Get input string

        std::stringstream ss(input);
        int choice;
        bool validInput = true;
        choices.clear();

        while (ss >> choice) {
            if (choice < 1 || choice > static_cast<int>(options.size())) {
                validInput = false;
                break;
            }
            choices.push_back(choice - 1); // Save the choice index
            if (ss.peek() == ',') ss.ignore(); // Skip the comma
        }

        if (validInput && !choices.empty()) {
            return choices;
        } else {
            std::cout << "Invalid input, please try again.\n";
        }
    }
}

// Function to handle adding or removing multiple items
void handleItemsAction(const std::vector<std::string>& items, std::set<std::string>& filterItems) {
    std::cout << "Choose items:\n";
    std::vector<int> choices = getMultipleChoices(items);

    std::cout << "You selected the following items:\n";
    for (int idx : choices) {
        std::cout << items[idx] << "\n";
    }

    // Menu for adding or removing
    std::cout << "Choose an action:\n";
    std::cout << "A - Add to filter\n";
    std::cout << "D - Remove from filter\n";
    char action;
    std::cin >> action;

    for (int idx : choices) {
        const std::string& selectedItem = items[idx];

        if (action == 'A' || action == 'a') {
            filterItems.insert(selectedItem);
            std::cout << selectedItem << " added to filter.\n";
        } else if (action == 'D' || action == 'd') {
            filterItems.erase(selectedItem);
            std::cout << selectedItem << " removed from filter.\n";
        } else {
            std::cout << "Invalid action for item: " << selectedItem << "\n";
        }
    }
}

// Function to select a single item
int getSingleChoice(const std::vector<std::string>& options) {
    std::string input;
    while (true) {
        displayOptions(options);
        std::cin >> input;

        try {
            int choice = std::stoi(input);
            if (choice >= 1 && choice <= static_cast<int>(options.size())) {
                return choice - 1; // Indices start from 0
            } else {
                std::cout << "Invalid choice, please try again.\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input, please try again.\n";
        }
    }
}

// Main menu
void mainMenu() {
    // Categories and their subcategories
    std::unordered_map<std::string, Category> categories = {
        {"One-Handed Weapons", {"One-Handed Weapons", {"Wands", "One-Handed Maces", "Sceptres"}, {}}},
        {"Two-Handed Weapons", {"Two-Handed Weapons", {"Bows", "Staves", "Two Hand Swords", "Two Hand Axes", "Two Hand Maces", "Quarterstaves", "Crossbows"}, {}}},
        {"Off-hand", {"Off-hand", {"Quivers", "Shields", "Foci"}, {}}},
        {"Armour", {"Armour", {"Gloves", "Boots", "Body Armours", "Helmets"}, {}}},
        {"Jewellery", {"Jewellery", {"Amulets", "Rings", "Belts"}, {}}},
        {"Flasks", {"Flasks", {"Flasks", "Life Flasks", "Mana Flasks", "Charms"}, {}}},
        {"Currency", {"Currency", {"Stackable Currency", "Distilled Emotions", "Essence", "Splinter", "Catalysts"}, {}}},
        {"Waystones", {"Waystones", {"Waystones", "Map Fragments"}, {}}},
        {"Jewels", {"Jewels", {"Jewels"}, {}}}
    };

    // Example for base items
    categories["One-Handed Weapons"].baseItems["Wands"] = {
        "Driftwood Wand", "Goat's Horn", "Quartz Wand", "Spiraled Wand", "Omen Wand",
        "Heathen Wand", "Profane Wand", "Opal Wand", "Tornado Wand", "Fossilised Wand",
        "Crystalline Wand", "Dragonbone Wand", "Pagan Wand", "Convoking Wand"
    };

    categories["One-Handed Weapons"].baseItems["One-Handed Maces"] = {
        "Driftwood Club", "Tribal Club", "Spiked Club", "Stone Hammer", "War Hammer",
        "Bladed Mace", "Ceremonial Mace", "Phantom Mace", "Pernach", "Auric Mace",
        "Nightmare Mace", "Behemoth Mace"
    };

    categories["One-Handed Weapons"].baseItems["Sceptres"] = {
        "Driftwood Sceptre", "Darkwood Sceptre", "Bronze Sceptre", "Quartz Sceptre", "Iron Sceptre",
        "Ochre Sceptre", "Ritual Sceptre", "Shadow Sceptre", "Grinning Fetish", "Sekhem",
        "Crystal Sceptre", "Lead Sceptre", "Blood Sceptre", "Royal Sceptre", "Abyssal Sceptre",
        "Stag Sceptre", "Karui Sceptre", "Tyrant's Sekhem", "Opal Sceptre", "Platinum Sceptre",
        "Vaal Sceptre", "Carnal Sceptre"
    };

    categories["Currency"].baseItems["Stackable Currency"] = {
        "Scroll of Wisdom", "Portal Scroll", "Orb of Transmutation", "Orb of Alteration", "Chaos Orb",
        "Blessed Orb", "Divine Orb", "Exalted Orb", "Orb of Annulment", "Mirror of Kalandra",
        "Vaal Orb", "Regal Orb", "Orb of Scouring", "Orb of Regret", "Orb of Augmentation",
        "Ancient Orb", "Harbinger's Orb", "Orb of Alchemy", "Glassblower's Bauble", "Gemcutter's Prism"
    };

    categories["Currency"].baseItems["Essence"] = {
        "Whispering Essence of Woe", "Muttering Essence of Anger", "Weeping Essence of Doubt",
        "Screaming Essence of Fear", "Shrieking Essence of Rage", "Deafening Essence of Greed",
        "Deafening Essence of Loathing", "Deafening Essence of Hatred", "Deafening Essence of Zeal"
    };

    categories["Currency"].baseItems["Splinter"] = {
        "Splinter of Xoph", "Splinter of Tul", "Splinter of Esh", "Splinter of Uul-Netol", "Splinter of Chayula",
        "Timeless Splinter", "Simulacrum Splinter"
    };

    categories["Currency"].baseItems["Distilled Emotions"] = {
        "Distilled Despair", "Distilled Envy", "Distilled Greed", "Distilled Ire", "Distilled Paranoia",
        "Distilled Disgust", "Distilled Fear", "Distilled Guilt", "Distilled Isolation",  "Distilled Suffering"
    };

    // Set to store filtered items
    std::set<std::string> filterItems;

    // Select main category
    std::cout << "Select a main category:\n";
    std::vector<std::string> mainCategories;
    for (const auto& category : categories) {
        mainCategories.push_back(category.first);
    }

    int mainChoice = getSingleChoice(mainCategories);
    const auto& selectedCategory = categories[mainCategories[mainChoice]];

    std::cout << "You selected: " << selectedCategory.name << "\n";
    std::cout << "Select a subcategory:\n";

    int subChoice = getSingleChoice(selectedCategory.subcategories);

    const auto& subcategoryName = selectedCategory.subcategories[subChoice];
    std::cout << "You selected subcategory: " << subcategoryName << "\n";

    try {
        if (selectedCategory.baseItems.find(subcategoryName) != selectedCategory.baseItems.end()) {
            handleItemsAction(selectedCategory.baseItems.at(subcategoryName), filterItems);
        } else {
            std::cout << "Subcategory " << subcategoryName << " is not implemented yet.\n";
        }
    } catch (const std::out_of_range& e) {
        std::cout << "Error: subcategory not found.\n";
    }

    // Display current filtered items
    std::cout << "Current filtered items:\n";
    for (const auto& item : filterItems) {
        std::cout << item << "\n";
    }
}

int main() {
    mainMenu();
    return 0;
}
