/**
 * @file MenuHandler.hpp
 * @brief Defines a templated MenuHandler class for creating and managing console-based menus.
 */

#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <input_utils.hpp>

#include "Helper.hpp"

/**
 * @class MenuHandler
 * @brief A templated class to handle displaying menus and capturing user choices.
 * 
 * This class simplifies the process of creating interactive console menus by managing
 * menu options, titles, and validating user input against a defined range of choices.
 * @tparam MenuEnum An enumeration type that defines the valid menu choices.
 */
template<typename MenuEnum>
class MenuHandler {
private:
    const std::vector<std::string> options; /**< The list of menu options to display. */
    const std::string base_title; /**< The base title for the menu. */
    const MenuEnum min_choice; /**< The minimum valid choice for the menu. */
    const MenuEnum max_choice; /**< The maximum valid choice for the menu. */

    /**
     * @brief Displays the menu options to the console.
     * @param prompt The prompt message to display before the options.
     * @param tabs The number of tabs to indent the menu options.
     */
    void show_menu(const std::string &prompt, int tabs = 0) const {
    std::string indent = indenter(tabs);
    if(!prompt.empty()){
        std::cout << indent << prompt;
    }
    indent.push_back('\t');
    for(int i = 0; i < options.size(); ++i){
        std::cout << indent  << std::right << std::setw(2) << i + 1 << ": " << options[i] << "\n";
    }
}

public:
    /**
     * @brief Constructor for the MenuHandler class.
     * @param options A vector of strings representing the menu options.
     * @param base_title The base title for the menu.
     * @param min_choice The minimum valid choice (as a MenuEnum value).
     * @param max_choice The maximum valid choice (as a MenuEnum value).
     */
    MenuHandler(const std::vector<std::string>& options, 
              const std::string& base_title,
              MenuEnum min_choice,
              MenuEnum max_choice)
        : options(options)
        , base_title(base_title)
        , min_choice(min_choice)
        , max_choice(max_choice) {}

    /**
     * @brief Displays the menu and gets a validated choice from the user.
     * @return The user's validated choice as a MenuEnum value.
     */
    MenuEnum show_and_get_choice() const {
        return show_and_get_choice("");
    }

    /**
     * @brief Displays the menu with a dynamic title and gets a validated choice from the user.
     * @param dynamic_title An additional string to append to the base title.
     * @return The user's validated choice as a MenuEnum value.
     */
    MenuEnum show_and_get_choice(const std::string& dynamic_title) const {
        std::string full_title = base_title;
        if (!dynamic_title.empty()) {
            if (base_title.back() == '\n') {
                full_title.pop_back();  // Remove trailing newline
            }
            full_title += " " + dynamic_title + "\n";
        }
        
        show_menu(full_title);
        int choice = read_validated_input<int>("Enter your choice: ", 0);
        
        if (choice >= static_cast<int>(min_choice) && 
            choice <= static_cast<int>(max_choice)) {
            return static_cast<MenuEnum>(choice);
        }
        
        return static_cast<MenuEnum>(0);  // InvalidChoice
    }
};