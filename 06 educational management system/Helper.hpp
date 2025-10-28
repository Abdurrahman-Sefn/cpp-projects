/**
 * @file Helper.hpp
 * @brief Provides utility functions for common tasks like indentation, string manipulation, and template-based selections.
 */

#pragma once

#include <iostream>
#include <vector>
#include <input_utils.hpp>


/**
 * @brief Generates an indentation string with a specified number of tabs.
 * @param tabs The number of tabs for indentation.
 * @return A string containing the specified number of tab characters.
 */
std::string indenter(int tabs);

/**
 * @brief Converts an integer to its string representation.
 * @param val The integer value to convert.
 * @return The string representation of the integer.
 */
std::string to_string(int val);

/**
 * @brief Removes leading whitespace from a string.
 * @param s The string to trim.
 */
void ltrim(std::string &s);

/**
 * @brief Removes trailing whitespace from a string.
 * @param s The string to trim.
 */
void rtrim(std::string &s);

/**
 * @brief Removes leading and trailing whitespace from a string.
 * @param s The string to trim.
 */
void trim(std::string &s);

/**
 * @brief Reads a line from an input stream and trims leading/trailing whitespace.
 * @param is The input stream to read from.
 * @param str The string to store the trimmed input.
 * @return A reference to the input stream.
 */
std::basic_istream<char> &read_and_trim(std::istream &is, std::string &str);

/**
 * @brief Checks if a given value is within a specified range (inclusive).
 * @param val The value to check.
 * @param min The minimum allowed value.
 * @param max The maximum allowed value.
 * @return True if the value is within the range, false otherwise.
 */
bool is_in_range(int val, int min, int max);

/**
 * @brief Allows the user to select an item from a vector of items.
 * @tparam T The type of items in the vector.
 * @param items A constant reference to a vector of items to choose from.
 * @param item_type A string describing the type of items (e.g., "course", "assignment").
 * @return The selected item, or nullptr if no item was selected or the list is empty.
 */
template<typename T>
T select_from(const std::vector<T> &items, std::string item_type){
    int size = items.size();
     if(!size) {
        std::cout << "\nThere are no " << item_type << "s to display.\n";
        return nullptr;
    }
    int choice = read_validated_input<int>("\nwhich ith [1 - " + to_string(size) + "] " + item_type + " to select ?: ", 0);
    while(!is_in_range(choice, 1, size)){
        choice = read_validated_input<int>("\nYour choice must be between 1 and " + to_string(size) + ". Try again: ");
    }
    return items[choice - 1];
}

