/**
 * @file Helper.hpp
 * @brief Provides utility functions for common tasks like indentation, menu display, and string manipulation.
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
