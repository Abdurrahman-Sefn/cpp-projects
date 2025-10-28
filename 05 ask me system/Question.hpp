/**
 * @file Question.hpp
 * @brief Defines the Answer and Question classes for the AskMe system.
 */

#pragma once
#include <vector>
#include <iostream>
#include <map>

class User;

/**
 * @class Answer
 * @brief Represents an answer to a question in the AskMe system.
 */
class Answer{
    std::string answer_text; /**< The content of the answer. */
public:
    /**
     * @brief Constructor for the Answer class.
     * @param answer_text The initial text of the answer.
     */
    Answer(const std::string &answer_text);

    /**
     * @brief Updates the text of the answer.
     * @param new_answer_text The new text for the answer.
     */
    void update(const std::string &new_answer_text);

    /**
     * @brief Gets the current text of the answer.
     * @return A constant reference to the answer text.
     */
    const std::string &get_answer_text()const;
};

/**
 * @class Question
 * @brief Represents a question in the AskMe system, including its details, sender, receiver, and answer.
 * 
 * This class handles the storage and management of question data, including linking to parent questions,
 * users involved, and the answer itself. It also manages anonymity and access control.
 */
class Question{
    int id{-1}; /**< Unique identifier for the question. */
    std::string question_text; /**< The content of the question. */

    Question *parent{}; /**< Pointer to the parent question if this is a reply, nullptr otherwise. */
    User* sender{}; /**< Pointer to the User who asked the question. */
    User* receptor{}; /**< Pointer to the User to whom the question was directed. */
    Answer *answer{}; /**< Pointer to the Answer object if the question has been answered, nullptr otherwise. */
    
    static const char DELIM = '|'; /**< Delimiter used for serializing question data to string. */
    int temp_parent_id{-1}; /**< Temporary storage for parent question ID during deserialization. */
    int temp_sender_id{-1}; /**< Temporary storage for sender user ID during deserialization. */
    int temp_receptor_id{-1}; /**< Temporary storage for receptor user ID during deserialization. */

    bool is_anonymous = false; /**< Flag indicating if the question was asked anonymously. */
public:
    /**
     * @brief Converts the Question object into a string representation for persistence.
     * @return A string representing the question's data.
     */
    std::string to_string()const;

    /**
     * @brief Constructs a Question object from a serialized string.
     * @param question_str The string representation of a question.
     */
    Question(const std::string &question_str);

    /**
     * @brief Constructor for the Question class.
     * @param sender A pointer to the User who sent the question.
     * @param receptor A pointer to the User who is the recipient of the question.
     * @param id The unique ID of the question.
     * @param question_text The content of the question.
     * @param is_anonymous True if the question is anonymous, false otherwise.
     * @param parent A pointer to the parent question if this is a reply, nullptr otherwise.
     */
    Question(User* sender, User* receptor, int id, const std::string &question_text, bool is_anonymous = false, Question* parent = nullptr);

    /**
     * @brief Links the temporary IDs to actual User and Question objects after all data is loaded.
     * @param users_id_map A map of user IDs to User objects.
     * @param questions_id_map A map of question IDs to Question objects.
     */
    void link_objects(const std::map<int, User*> &users_id_map, const std::map<int, Question*> &questions_id_map);

    /**
     * @brief Gets the ID of the question.
     * @return The ID of the question.
     */
    int get_id()const;

    /**
     * @brief Gets a pointer to the parent question.
     * @return A pointer to the parent Question object, or nullptr if it's a top-level question.
     */
    Question* get_parent_question()const;

    /**
     * @brief Checks if the question has been answered.
     * @return True if the question has an answer, false otherwise.
     */
    bool is_answered()const;

    /**
     * @brief Determines if a given user can view this question.
     * @param user A pointer to the User attempting to view the question.
     * @return True if the user can see the question, false otherwise.
     */
    bool can_see(User* user) const;

    /**
     * @brief Determines if a given user can edit this question.
     * @param user A pointer to the User attempting to edit the question.
     * @return True if the user can edit the question, false otherwise.
     */
    bool can_edit(User* user) const;

    /**
     * @brief Prints information about who sent the question.
     * @param indent The number of tabs to indent the output.
     */
    void print_from_whom(int indent)const;

    /**
     * @brief Prints information about to whom the question was directed.
     * @param indent The number of tabs to indent the output.
     */
    void print_to_whom(int indent)const;

    /**
     * @brief Prints the question and its answer (if any) for a user's feed.
     * @param cur_user A constant pointer to the current logged-in User.
     * @param indent The number of tabs to indent the output.
     */
    void print_feed(const User* const cur_user, int indent) const;

    /**
     * @brief Sets or updates the answer text for the question.
     * @param answer_text The text of the answer.
     */
    void set_answer_text(const std::string &answer_text);

    /**
     * @brief Gets a pointer to the sender of the question.
     * @return A pointer to the User who sent the question.
     */
    User* get_sender()const;

    /**
     * @brief Gets a pointer to the receptor (recipient) of the question.
     * @return A pointer to the User who is the recipient of the question.
     */
    User* get_receptor()const;

    /**
     * @brief Destructor for the Question class. Cleans up dynamically allocated Answer object.
     */
    ~Question();
};