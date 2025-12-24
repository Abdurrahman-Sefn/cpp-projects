/**
 * @file MenuHandler.hpp
 * @brief Defines a templated MenuHandler class for creating and managing console-based menus.
 */

#pragma once
#include <Sefn/InputUtils.hpp>
#include <iomanip>
#include <string>
#include <vector>

#include "Helper.hpp"

/**
 * @class MenuHandler
 * @brief A templated class to handle displaying menus and capturing user choices.
 *
 * This class simplifies the process of creating interactive console menus by managing
 * menu options, titles, and validating user input against a defined range of choices.
 * @tparam MenuEnum An enumeration type that defines the valid menu choices.
 */
template <typename MenuEnum>
class MenuHandler {
   private:
    const std::vector<std::string> options; /**< The list of menu options to display. */
    const std::string baseTitle;            /**< The base title for the menu. */
    const MenuEnum minChoice;               /**< The minimum valid choice for the menu. */
    const MenuEnum maxChoice;               /**< The maximum valid choice for the menu. */

    /**
     * @brief Displays the menu options to the console.
     * @param prompt The prompt message to display before the options.
     * @param tabs The number of tabs to indent the menu options.
     */
    void showMenu(const std::string& prompt, int tabs = 0) const {
        std::string indent = indenter(tabs);
        if (!prompt.empty()) {
            std::cout << indent << prompt;
        }
        indent.push_back('\t');
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << indent << std::right << std::setw(2) << i + 1 << ": " << options[i]
                      << "\n";
        }
    }

   public:
    /**
     * @brief Constructor for the MenuHandler class.
     * @param options A vector of strings representing the menu options.
     * @param baseTitle The base title for the menu.
     * @param minChoice The minimum valid choice (as a MenuEnum value).
     * @param maxChoice The maximum valid choice (as a MenuEnum value).
     */
    MenuHandler(const std::vector<std::string>& options, const std::string& baseTitle,
                MenuEnum minChoice, MenuEnum maxChoice)
        : options(options), baseTitle(baseTitle), minChoice(minChoice), maxChoice(maxChoice) {}

    /**
     * @brief Displays the menu and gets a validated choice from the user.
     * @return The user's validated choice as a MenuEnum value.
     */
    MenuEnum showAndGetChoice() const { return showAndGetChoice(""); }

    /**
     * @brief Displays the menu with a dynamic title and gets a validated choice from the user.
     * @param dynamicTitle An additional string to append to the base title.
     * @return The user's validated choice as a MenuEnum value.
     */
    MenuEnum showAndGetChoice(const std::string& dynamicTitle) const {
        std::string fullTitle = baseTitle;
        if (!dynamicTitle.empty()) {
            if (baseTitle.back() == '\n') {
                fullTitle.pop_back();  // Remove trailing newline
            }
            fullTitle += " " + dynamicTitle + "\n";
        }

        showMenu(fullTitle);
        int choice = Sefn::readValidatedInput<int>("Enter your choice: ", 0);

        if (choice >= static_cast<int>(minChoice) && choice <= static_cast<int>(maxChoice)) {
            return static_cast<MenuEnum>(choice);
        }

        return static_cast<MenuEnum>(0);  // InvalidChoice
    }
};