#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// Structure for categories and subcategories
struct Category {
    std::string name;
    std::vector<std::string> subcategories;
    std::unordered_map<std::string, std::vector<std::string>> baseItems; // To store base items for subcategories
};

// Function to display the options list
void displayOptions(const std::vector<std::string>& options) {
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
    std::cout << "Enter the numbers of your chosen options separated by commas (e.g., 1,3,4): ";
}

// Function to get multiple choices from the user
std::vector<int> getMultipleChoices(const std::vector<std::string>& options) {
    std::string input;
    std::vector<int> choices;

    while (true) {
        displayOptions(options);
        std::getline(std::cin, input);  // Get the input line

        std::stringstream ss(input);
        int choice;
        bool validInput = true;
        choices.clear();

        while (ss >> choice) {
            if (choice < 1 || choice > static_cast<int>(options.size())) {
                validInput = false;
                break;
            }
            choices.push_back(choice - 1); // Store the index of the choice
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
    if (items.empty()) {
        std::cout << "There are no items in this subcategory.\n";
        return;
    }

    std::cout << "Choose items:\n";
    std::vector<int> choices = getMultipleChoices(items);

    std::cout << "You have chosen the following items:\n";
    for (int idx : choices) {
        std::cout << items[idx] << "\n";
    }

    // Menu for adding or removing items
    std::cout << "Choose an action:\n";
    std::cout << "A - Add to filter\n";
    std::cout << "D - Remove from filter\n";
    char action;
    std::cin >> action;
    std::cin.ignore(); // Clear the input buffer

    if (action != 'A' && action != 'a' && action != 'D' && action != 'd') {
        std::cout << "Invalid action. Please choose A to add or D to remove.\n";
        return;
    }

    for (int idx : choices) {
        const std::string& selectedItem = items[idx];

        if (action == 'A' || action == 'a') {
            filterItems.insert(selectedItem);
            std::cout << selectedItem << " added to the filter.\n";
        } else if (action == 'D' || action == 'd') {
            filterItems.erase(selectedItem);
            std::cout << selectedItem << " removed from the filter.\n";
        }
    }
}

// Function to get a single choice from the user
int getSingleChoice(const std::vector<std::string>& options) {
    std::string input;
    while (true) {
        displayOptions(options);
        std::getline(std::cin, input);

        try {
            int choice = std::stoi(input);
            if (choice >= 1 && choice <= static_cast<int>(options.size())) {
                return choice - 1; // Indices start at 0
            } else {
                std::cout << "Invalid choice, please try again.\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input, please try again.\n";
        }
    }
}

// Main menu function
void mainMenu() {
    // Categories and subcategories
    std::unordered_map<std::string, Category> categories = {
        {"One-Handed Weapons", {"One-Handed Weapons", {"Wands", "One-Handed Maces",
                                                       "Sceptres"}, {}}},
        {"Two-Handed Weapons", {"Two-Handed Weapons", {"Bows", "Staves", "Two Hand Axes",
                                                       "Two Hand Maces", "Quarterstaves", "Crossbows"}, {}}},
        {"Off-hand", {"Off-hand", {"Quivers", "Shields", "Foci"}, {}}},
        {"Armour", {"Armour", {"Gloves", "Boots", "Body Armours", "Helmets"}, {}}},
        {"Jewellery", {"Jewellery", {"Amulets", "Rings", "Belts"}, {}}},
        {"Flasks", {"Flasks", {"Life Flasks", "Mana Flasks", "Charms"}, {}}},
        {"Currency", {"Currency", {"Stackable Currency", "Distilled Emotions", "Essence",
                                   "Splinter", "Catalysts"}, {}}},
        {"Waystones", {"Waystones", {"Waystones", "Map Fragments"}, {}}},
        {"Jewels", {"Jewels", {"Jewels"}, {}}}
    };

    // Example base items for subcategories
    categories["Armour"].baseItems["Boots"] = {
        "Rough Greaves", "Iron Greaves", "Bronze Greaves", "Trimmed Greaves", "Stone Greaves",
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
        "Advanced Lizardscale Boots", "Advanced Wrapped Sandals", "Advanced Lattice Sandals",
        "Advanced Silk Slippers", "Advanced Feathered Sandals", "Advanced Mail Sabatons",
        "Advanced Braced Sabatons", "Advanced Stacked Sabatons", "Advanced Padded Leggings",
        "Advanced Secured Leggings", "Advanced Pelt Leggings", "Advanced Frayed Shoes",
        "Advanced Threaded Shoes", "Advanced Hunting Shoes", "Expert Iron Greaves",
        "Expert Trimmed Greaves", "Expert Stone Greaves", "Expert Laced Boots", "Expert Steeltoe Boots",
        "Expert Lizardscale Boots ", "Expert Wrapped Sandals", "Expert Silk Slippers",
        "Expert Feathered Sandals", "Expert Mail Sabatons", "Expert Braced Sabatons",
        "Expert Stacked Sabatons", "Expert Padded Leggings", "Expert Secured Leggings",
        "Expert Pelt Leggings", "Expert Frayed Shoes", "Expert Threaded Shoes", "Expert Hunting Shoes"
    };

    categories["Armour"].baseItems["Gloves"] = {
        "Stocky Mitts", "Riveted Mitts", "Tempered Mitts", "Bolstered Mitts",
        "Moulded Mitts", "Detailed Mitts", "Titan Mitts", "Grand Mitts", "Suede Bracers",
        "Firm Bracers", "Bound Bracers", "Sectioned Bracers", "Spined Bracers", "Fine Bracers",
        "Hardened Bracers", "Engraved Bracers", "Torn Gloves", "Sombre Gloves",
        "Stitched Gloves", "Jewelled Gloves", "Intricate Gloves", "Paulascale Gloves",
        "Embroidered Gloves", "Adaorned Gloves", "Ringmail Gauntlets", "Linen Wraps",
        "Layered Gauntlets", "Doubled Gauntiets", "Plate Gauntlets", "Spiral Wraps",
        "Burnished Gauntlest", "Ornate Gauntlets", "Rope Guffs", "Aged Cuffs",
        "Goldcast Cuffs", "Diviner Cuffs", "Righteous Cuffs", "Signet Cuffs", "Gauze Wraps",
        "Buckled Wraps", "Furtive Wraps", "Utility Wraps", "Grand Manchettes",
        "Advanced Riveted Mitts", "Advanced Tempered Mitts", "Advanced Bolstered Mitts",
        "Advanced Moulded Mitts", "Advanced Firm Mitts", "Advanced Boud Bracers",
        "Advanced Sectioned Bracers", "Advanced Spined Bracers", "Advanced Sombre Gloves",
        "Advanced Stitched Gloves", "Advanced Jewelled Gloves", "Advanced Intricate Gloves",
        "Advanced Ringmail Gauntlets", "Advanced Layered Gauntlets",
        "Advanced Doubled Gauntlets", "Advanced Rope Cuffs", "Advanced Aged Cuffs",
        "Advanced Goldcast Cuffs", "Advanced Gauze Wraps", "Advanced Linen Wraps",
        "Advanced Spiral Wraps", "Expert Riveted Mitts", "Expert Bolstered Mitts",
        "Expert Moulded Mitts", "Expert Firm Bracers", "Expert Sectioned Bracers",
        "Expert Spined Bracers", "Expert Sombre Gloves", "Expert Jewelled Gloves",
        "Expert Intricate Gloves", "Expert Ringmail Gauntlets", "Expert Layered Gauntlets",
        "Expert Doubled Gauntlets", "Expert Rope Cuffs", "Expert Aged Cuffs", "Expert Goldcast Cuffs",
        "Expert Gauze Wraps", "Expert Limen Wraps", "Expert Spiral Wraps"
    };

    categories["Off-hand"].baseItems["Foci"] = {
        "Twig Focus", "Woven Focus", "Antier Focus", "Engraved Focus", "Tonal Focus",
        "Crystal Focus", "Voodoo Focus", "Plumed Focus", "Jade Focus", "Paula Focus",
        "Elegant Focus", "Attuned Focus", "Magus Focus", "Advanced Woven Focus",
        "Advanced Antier Focus", "Advanced Tonal Focus", "Advanced Crystal Focus",
        "Advanced Voodoo Focus", "Advances Plumed Focus", "Expert Antier Focus",
        "Expert Crystal Focus", "Epert Plumed Focus"
    };

    categories["Off-hand"].baseItems["Shields"] = {
        "Splinterred Tower Shield", "Painted Tower Shield", "Braced Tower Shield",
        "Barricade Tower Shield", "Effigial Tower Shield", "Rampart Tower Shield",
        "Heraldric Tower Shield", "Stone Tower Shield", "Crucible Tower Shield",
        "Ancestor Tower Shield", "Phalanx Tower Shield", "Defiant Tower Shield",
        "Blacksteel Tower Shield", "Hardwood Targe", "Hardwood Targe", "Pelage Targe",
        "Studded Targe", "Crescent Targe", "Chiseled Targe", "Feathered Targe",
        "Stratified Targe", "Carved Targe", "Mosaic Targe", "Aureate Targe", "Grand Targe",
        "Biazon Crest Shield", "Blazon Crest Shield", "Sigil Crest Shield",
        "Emblem Crest Shield", "Jingling Crest Shield", "Sectarian Crest Shield",
        "Omen Crest Shield", "Wayward Crest Shield", "Seer Crest Shield",
        "Stoic Crest Shield", "Empyreal Crest Shield", "Deified Crest Shield",
        "Leather Bucker", "Leather Buckier", "Wooden Buckier", "Plated Buckier",
        "Iron Buckier", "Ridged Buckier", "Spiked Buckier", "Ringed Buckier",
        "Edged Buckier", "Laminate Buckier", "Pearl Buckier", "Ornate Buckier",
        "Array Buckier", "Aegis Buckier", "Advanced Painted Tower Shield",
        "Advanced  Tower Shield", "Advanced Braced Tower Shield",
        "Advanced Effigial Tower Shield", "Advanced Rampart Tower Shield",
        "Advanced Heraldric Tower Shield", "Advanced Stone Tower Shield",
        "Advanced Hardwood Targe", "Advanced Pelage Targe", "Advanced Studded Targe",
        "Advanced Crescent Targe", "Advanced Chseled Targe", "Advanced Feathered Targe",
        "Advanced Blazon Crest Shield", "Advanced Sigil Crest Shield",
        "Advanced Emblem Crest Shield", "Advanced Jingling Crest Shield",
        "Advanced Sectarian Crest Shield", "Advanced Omen Crest Shield",
        "Advanced Wooden Buckler", "Advanced Piated Buckler", "Advanced Ridged Buckler",
        "Advanced Spiked Buckler", "Advanced Ringed Buckler", "Advanced Edged Buckler",
        "Expert Braced Tower Shield", "Expert Rampart Tower Shield",
        "Expert Stone Tower Shield", "Expert Pelage Targe", "Expert Crescent Targe",
        "Expert Feathered Targe", "Expert Sigil Crest Shield",
        "Expert jingling Crest Shield", "Expert Omen Crest Shield",
        "Expert Plated Buckler", "Expert Spiked Buckler", "Expert Edged Buckler"
    };

    categories["Off-hand"].baseItems["Quivers"] = {
        "Broadhead Quiver", "Fire Quiver", "Sacral Quiver", "Two-Point Quiver",
        "Blunt Quiver", "Toxic Quiver", "Serrated Quiver", "Primed Quiver",
        "Penetrating Quiver", "Volant Quiver", "Visceral Quiver"
    };

    categories["One-Handed Weapons"].baseItems["Wands"] = {
        "Withered Wand", "Bone Wand", "Attuned Wand", "Siphoning Wand", "Volatile Wand",
        "Galvanic Wand", "Acrid Wand", "Offering Wand", "Frigid Wand", "Torture Wand",
        "Critical Wand", "Primordial Wand", "Dueling Wand"
    };

    categories["One-Handed Weapons"].baseItems["One-Handed Maces"] = {
        "Wooden Club", "Smithing Hammer", "Slim Mace", "Spiked Club", "Warpick",
        "Plated Mace", "Brigand Mace", "Construct Hammer", "Morning Star", "Jade Club",
        "Lumen Mace", "Execratus Hammer", "Torment Club", "Advanced Smithing Hammer",
        "Advanced Slim Mace", "Advanced Warpick", "Advanced Plated Mace",
        "Advanced Brigand Mace", "Advanced Construct Hammer", "Expert Slim Mace",
        "Expert Plated Mace", "Expert Smithing Hammer", "Expert Warpick",
        "Expert Construct Hammer", "Expert Brigand Mace"
    };

    categories["One-Handed Weapons"].baseItems["Sceptres"] = {
        "Rattling Sceptre", "Stoic Sceptre", "Lupine Sceptre","Omen Sceptre",
        "Ochre Sceptre", "Shrine Sceptre", "Shrine Sceptre", "Shrine Sceptre",
        "Devouring Sceptre", "Clasped Sceptre", "Devotinal Sceptre",
        "Wrath Sceptre", "Aromatic Sceptre", "Pious Sceptre", "Hallowed Sceptre"
    };

    categories["Two-Handed Weapons"].baseItems["Bows"] = {
        "Crude Bow", "Shortbow", "Warden Bow", "Recurve Bow", "Composite Bow",
        "Dualstring Bow", "Cultist Bow", "Zealot Bow", "Artillery Bow", "Tribal Bow",
        "Greatbow", "Double Limb Bow", "Heavy Bow", "Advanced Shortbow",
        "Advanced Warden Bow", "Advanced Composite Bow", "Advanced Dualstring Bow",
        "Advanced Cultist Bow", "Advanced Zealot Bow", "Expert Shortbow",
        "Expert Composite Bow", "Expert Warden Bow", "Expert Dualstring Bow",
        "Expert Cultist Bow", "Expert Zealot Bow"
    };

    categories["Two-Handed Weapons"].baseItems["Staves"] = {
        "Ashen Staff", "Gelid Staff", "Voltaic Staff", "Spriggan Staff", "Pyrophype Staff",
        "Chiming Staff", "Rending Staff", "Reaping Staff", "Icicle Staff", "Roaring Staff",
        "Paralysing Staff", "Cleric Staff", "Dark Staff"
    };

    categories["Two-Handed Weapons"].baseItems["Two Hand Mace"] = {
        "Felled Greatclub", "Oak Greathammer", "Forge Maul", "Studded Greatclub",
        "Cultist Greathammer", "Temple Maul", "Leaden Greathammer", "Crumbling Maul",
        "Pointed Mail", "Totemic Greatclub", "Greatmace", "Precise Greathammer",
        "Giant Maul", "Advanced Oak Greathammer", "Advanced Forge Maul",
        "Advanced Cultist Greathammer", "Advanced Temple Maul",
        "Advanced Leaden Greathammer", "Advanced Crumbling Maul", "Expert Forge Maul",
        "Expert Temple Maul", "Expert Oak Greathammer", "Expert Cultist Greathammer",
        "Expert Crumbling Maul", "Expert Leaden Greathammer"
    };

    categories["Two-Handed Weapons"].baseItems["Quarterstaves"] = {
        "Wrapped Quarterstaff", "Long Quarterstaff", "Gothic Quarterstaff",
        "Crackling Quarterstaff", "Crescent Quarterstaff", "Steelpoint Quarterstaff",
        "Slicing Quarterstaff", "Barrier Quarterstaff", "Hefty Quarterstaff",
        "Smooth Quarterstaff", "Anima Quarterstaff", "Graceful Quarterstaff",
        "Wyrm Quarterstaff", "Advanced Long Quarterstaff", "Advanced Gothic Quarterstaff",
        "Advanced Crackling Quarterstaff", "Advanced Crescent Quarterstaff",
        "Advanced Slicing Quarterstaff", "Advanced Barrier Quarterstaff",
        "Expert Gothic Quarterstaff", "Expert Crescent Quarterstaff",
        "Expert Long Quarterstaff", "Expert Crackling Quarterstaff",
        "Expert Crackling Quarterstaff", "Expert Barrier Quarterstaff",
        "Expert Slicing Quarterstaff"
    };

    categories["Two-Handed Weapons"].baseItems["Crossbows"] = {
        "Makeshift Crossbow", "Tense Crossbow", "Sturdy Crossbow", "Varnished Crossbow",
        "Dyad Crossbow", "Alloy Crossbow", "Bombard Crossbow", "Construct Crossbow",
        "Blackfire Crossbow", "Piercing Crossbow", "Cumbrous Crossbow", "Dedalian Crossbow",
        "Esoteric Crossbow", "Advanced Tense Crossbow", "Advances Sturdy Crossbow",
        "Advanced Varnished Crossbow", "Advanced Dyad Crossbow",
        "Advanced Bombard Crossbow", "Advanced Foriorn Crossbow",
        "Advanced Sturdy Crossbow", "Expert Varnished Crossbow", "Expert Tense Crossbow",
        "Expert Dyad Crossbow", "Expert Bombard Crossbow", "Expert Forlorn Crossbow"
    };

    categories["Currency"].baseItems["Stackable Currency"] = {
        "Scroll of Wisdom", "Portal Scroll", "Orb of Transmutation", "Orb of Alteration",
        "Chaos Orb", "Blessed Orb", "Divine Orb", "Exalted Orb", "Orb of Annulment",
        "Mirror of Kalandra", "Vaal Orb", "Regal Orb", "Orb of Scouring", "Orb of Regret",
        "Orb of Augmentation", "Ancient Orb", "Harbinger's Orb", "Orb of Alchemy",
        "Glassblower's Bauble", "Gemcutter's Prism"
    };

    categories["Currency"].baseItems["Essence"] = {
        "Whispering Essence of Woe", "Muttering Essence of Anger",
        "Weeping Essence of Doubt", "Screaming Essence of Fear",
        "Shrieking Essence of Rage", "Deafening Essence of Greed",
        "Deafening Essence of Loathing", "Deafening Essence of Hatred",
        "Deafening Essence of Zeal"
    };

    categories["Currency"].baseItems["Splinter"] = {
        "Splinter of Xoph", "Splinter of Tul", "Splinter of Esh", "Splinter of Uul-Netol",
        "Splinter of Chayula", "Timeless Splinter", "Simulacrum Splinter"
    };

    categories["Currency"].baseItems["Catalysts"] = {
        "Flesh Catalyst", "Neural Catalyst", "Carapace Catalyst", "Uul-Netol's Catalyst",
        "Xoph's Catalyst", "Tul's Catalyst", "Esh's Catalyst", "Chayula's Catalyst",
        "Reaver Catalyst", "Sibilant Catalyst", "Skittering Catalyst", "Adaptive Catalyst"
    };

    categories["Currency"].baseItems["Distilled Emotions"] = {
        "Distilled Despair", "Distilled Envy", "Distilled Greed", "Distilled Ire",
        "Distilled Paranoia", "Distilled Disgust", "Distilled Fear", "Distilled Guilt",
        "Distilled Isolation", "Distilled Suffering"
    };

    // Set for storing filtered items
    std::set<std::string> filterItems;

    // Choose main category
    std::cout << "Choose the main category:\n";
    std::vector<std::string> mainCategories;
    for (const auto& category : categories) {
        mainCategories.push_back(category.first);
    }

    int mainChoice = getSingleChoice(mainCategories);
    const auto& selectedCategory = categories[mainCategories[mainChoice]];

    std::cout << "You chose: " << selectedCategory.name << "\n";
    std::cout << "Choose a subcategory:\n";

    int subChoice = getSingleChoice(selectedCategory.subcategories);

    const auto& subcategoryName = selectedCategory.subcategories[subChoice];
    std::cout << "You chose the subcategory: " << subcategoryName << "\n";

    try {
        if (selectedCategory.baseItems.find(subcategoryName) != selectedCategory.baseItems.end()) {
            handleItemsAction(selectedCategory.baseItems.at(subcategoryName), filterItems);
        } else {
            std::cout << "This subcategory is not yet implemented.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << "\n";
    }
}

int main() {
    mainMenu();
    return 0;
}
