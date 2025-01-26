#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>

// Структура для категорий и подкатегорий
struct Category {
    std::string name;
    std::vector<std::string> subcategories;
    std::unordered_map<std::string, std::vector<std::string>> baseItems; // Для хранения баз предметов по подкатегориям
};

// Функция для отображения списка опций
void displayOptions(const std::vector<std::string>& options) {
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
    std::cout << "Введите номера выбранных опций через запятую (например, 1,3,4): ";
}

// Функция для выбора нескольких опций
std::vector<int> getMultipleChoices(const std::vector<std::string>& options) {
    std::string input;
    std::vector<int> choices;

    while (true) {
        displayOptions(options);
        std::getline(std::cin, input);  // Получаем строку ввода

        std::stringstream ss(input);
        int choice;
        bool validInput = true;
        choices.clear();

        while (ss >> choice) {
            if (choice < 1 || choice > static_cast<int>(options.size())) {
                validInput = false;
                break;
            }
            choices.push_back(choice - 1); // Сохраняем индекс выбора
            if (ss.peek() == ',') ss.ignore(); // Пропускаем запятую
        }

        if (validInput && !choices.empty()) {
            return choices;
        } else {
            std::cout << "Некорректный ввод, попробуйте снова.\n";
        }
    }
}

// Функция для обработки выбора добавления или удаления нескольких предметов
void handleItemsAction(const std::vector<std::string>& items, std::set<std::string>& filterItems) {
    std::cout << "Выберите предметы:\n";
    std::vector<int> choices = getMultipleChoices(items);

    std::cout << "Вы выбрали следующие предметы:\n";
    for (int idx : choices) {
        std::cout << items[idx] << "\n";
    }

    // Меню с добавлением или удалением
    std::cout << "Выберите действие:\n";
    std::cout << "A - Добавить в фильтр\n";
    std::cout << "D - Удалить из фильтра\n";
    char action;
    std::cin >> action;

    for (int idx : choices) {
        const std::string& selectedItem = items[idx];

        if (action == 'A' || action == 'a') {
            filterItems.insert(selectedItem);
            std::cout << selectedItem << " добавлен в фильтр.\n";
        } else if (action == 'D' || action == 'd') {
            filterItems.erase(selectedItem);
            std::cout << selectedItem << " удалён из фильтра.\n";
        } else {
            std::cout << "Неверное действие для предмета: " << selectedItem << "\n";
        }
    }
}

// Функция для выбора одного элемента
int getSingleChoice(const std::vector<std::string>& options) {
    std::string input;
    while (true) {
        displayOptions(options);
        std::cin >> input;

        try {
            int choice = std::stoi(input);
            if (choice >= 1 && choice <= static_cast<int>(options.size())) {
                return choice - 1; // Индексы начинаются с 0
            } else {
                std::cout << "Некорректный выбор, попробуйте снова.\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Некорректный ввод, попробуйте снова.\n";
        }
    }
}

// Основное меню
void mainMenu() {
    // Категории и их подкатегории
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

    // Пример для баз предметов
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

    // Множество для хранения фильтрованных предметов
    std::set<std::string> filterItems;

    // Выбор основной категории
    std::cout << "Выберите основную категорию:\n";
    std::vector<std::string> mainCategories;
    for (const auto& category : categories) {
        mainCategories.push_back(category.first);
    }

    int mainChoice = getSingleChoice(mainCategories);
    const auto& selectedCategory = categories[mainCategories[mainChoice]];

    std::cout << "Вы выбрали: " << selectedCategory.name << "\n";
    std::cout << "Выберите подкатегорию:\n";

    int subChoice = getSingleChoice(selectedCategory.subcategories);

    const auto& subcategoryName = selectedCategory.subcategories[subChoice];
    std::cout << "Вы выбрали подкатегорию: " << subcategoryName << "\n";

    try {
        if (selectedCategory.baseItems.find(subcategoryName) != selectedCategory.baseItems.end()) {
            handleItemsAction(selectedCategory.baseItems.at(subcategoryName), filterItems);
        } else {
            std::cout << "Подкатегория " << subcategoryName << " пока не реализована.\n";
        }
    } catch (const std::out_of_range& e) {
        std::cout << "Ошибка: подкатегория не найдена.\n";
    }

    // Вывод текущих фильтруемых предметов
    std::cout << "Текущие фильтруемые предметы:\n";
    for (const auto& item : filterItems) {
        std::cout << item << "\n";
    }
}

int main() {
    mainMenu();
    return 0;
}
