/**
 * @file Helper.hpp
 * @brief Provides utility functions for common tasks like indentation and menu display.
 */

#pragma once

#include <iostream>
#include <vector>

/**
 * @brief Generates an indentation string with a specified number of tabs.
 * @param tabs The number of tabs for indentation.
 * @return A string containing the specified number of tab characters.
 */
std::string indenter(int tabs);

/**
 * @brief Displays a menu of options to the console and prompts the user for input.
 * @param options A vector of strings, where each string is a menu option.
 * @param prompt The message displayed to the user to solicit their choice.
 * @param tabs The number of tabs to indent the menu options.
 */
void show_menu(const std::vector<std::string> &options, const std::string &prompt, int tabs = 0);