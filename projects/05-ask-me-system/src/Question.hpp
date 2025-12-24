/**
 * @file Question.hpp
 * @brief Defines the Answer and Question classes for the AskMe system.
 */

#pragma once
#include <iostream>
#include <map>
#include <vector>

class User;

/**
 * @class Answer
 * @brief Represents an answer to a question in the AskMe system.
 */
class Answer {
    std::string answerText; /**< The content of the answer. */
   public:
    /**
     * @brief Constructor for the Answer class.
     * @param answer_text The initial text of the answer.
     */
    Answer(const std::string& answerText);

    /**
     * @brief Updates the text of the answer.
     * @param new_answer_text The new text for the answer.
     */
    void update(const std::string& newAnswerText);

    /**
     * @brief Gets the current text of the answer.
     * @return A constant reference to the answer text.
     */
    const std::string& getAnswerText() const;
};

/**
 * @class Question
 * @brief Represents a question in the AskMe system, including its details, sender, receiver, and
 * answer.
 *
 * This class handles the storage and management of question data, including linking to parent
 * questions, users involved, and the answer itself. It also manages anonymity and access control.
 */
class Question {
    int id{-1};               /**< Unique identifier for the question. */
    std::string questionText; /**< The content of the question. */

    Question*
        parent{};      /**< Pointer to the parent question if this is a reply, nullptr otherwise. */
    User* sender{};    /**< Pointer to the User who asked the question. */
    User* recipient{}; /**< Pointer to the User to whom the question was directed. */
    Answer* answer{};  /**< Pointer to the Answer object if the question has been answered, nullptr
                          otherwise. */

    static const char DELIM = '|'; /**< Delimiter used for serializing question data to string. */
    int tempParentId{-1}; /**< Temporary storage for parent question ID during deserialization. */
    int tempSenderId{-1}; /**< Temporary storage for sender user ID during deserialization. */
    int tempRecipientId{-1}; /**< Temporary storage for receptor user ID during deserialization. */

    bool isAnonymous = false; /**< Flag indicating if the question was asked anonymously. */
   public:
    /**
     * @brief Converts the Question object into a string representation for persistence.
     * @return A string representing the question's data.
     */
    std::string toString() const;

    /**
     * @brief Constructs a Question object from a serialized string.
     * @param question_str The string representation of a question.
     */
    Question(const std::string& questionStr);

    /**
     * @brief Constructor for the Question class.
     * @param sender A pointer to the User who sent the question.
     * @param receptor A pointer to the User who is the recipient of the question.
     * @param id The unique ID of the question.
     * @param question_text The content of the question.
     * @param is_anonymous True if the question is anonymous, false otherwise.
     * @param parent A pointer to the parent question if this is a reply, nullptr otherwise.
     */
    Question(User* sender, User* recipient, int id, const std::string& questionText,
             bool isAnonymous = false, Question* parent = nullptr);

    /**
     * @brief Links the temporary IDs to actual User and Question objects after all data is loaded.
     * @param users_id_map A map of user IDs to User objects.
     * @param questions_id_map A map of question IDs to Question objects.
     */
    void linkObjects(const std::map<int, User*>& usersIdMap,
                     const std::map<int, Question*>& questionsIdMap);

    /**
     * @brief Gets the ID of the question.
     * @return The ID of the question.
     */
    int getId() const;

    /**
     * @brief Gets a pointer to the parent question.
     * @return A pointer to the parent Question object, or nullptr if it's a top-level question.
     */
    Question* getParentQuestion() const;

    /**
     * @brief Checks if the question has been answered.
     * @return True if the question has an answer, false otherwise.
     */
    bool isAnswered() const;

    /**
     * @brief Determines if a given user can view this question.
     * @param user A pointer to the User attempting to view the question.
     * @return True if the user can see the question, false otherwise.
     */
    bool canSee(User* user) const;

    /**
     * @brief Determines if a given user can edit this question.
     * @param user A pointer to the User attempting to edit the question.
     * @return True if the user can edit the question, false otherwise.
     */
    bool canEdit(User* user) const;

    /**
     * @brief Prints information about who sent the question.
     * @param indent The number of tabs to indent the output.
     */
    void printFromWhom(int indent) const;

    /**
     * @brief Prints information about to whom the question was directed.
     * @param indent The number of tabs to indent the output.
     */
    void printToWhom(int indent) const;

    /**
     * @brief Prints the question and its answer (if any) for a user's feed.
     * @param cur_user A constant pointer to the current logged-in User.
     * @param indent The number of tabs to indent the output.
     */
    void printFeed(const User* const currentUser, int indent) const;

    /**
     * @brief Sets or updates the answer text for the question.
     * @param answer_text The text of the answer.
     */
    void setAnswerText(const std::string& answerText);

    /**
     * @brief Gets a pointer to the sender of the question.
     * @return A pointer to the User who sent the question.
     */
    User* getSender() const;

    /**
     * @brief Gets a pointer to the receptor (recipient) of the question.
     * @return A pointer to the User who is the recipient of the question.
     */
    User* getRecipient() const;

    /**
     * @brief Destructor for the Question class. Cleans up dynamically allocated Answer object.
     */
    ~Question();
};