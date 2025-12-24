/**
 * @file QuestionsManager.hpp
 * @brief Manages the collection of questions in the AskMe system, including their relationships and
 * persistence.
 */

#pragma once
#include <map>
#include <unordered_map>

#include "Question.hpp"

/**
 * @class QuestionsManager
 * @brief Handles the creation, storage, retrieval, and management of Question objects.
 *
 * This class provides functionalities to add new questions, manage question threads (parent-child
 * relationships), print question feeds, and handle data persistence for questions.
 */
class QuestionsManager {
    std::map<int, Question*>
        idToQuestionMap; /**< Maps question IDs to Question objects for quick lookup. */
    std::unordered_map<Question*, std::vector<Question*> >
        parentToChildrenMap; /**< Maps parent questions to their child questions. */
    int lastId; /**< The last assigned question ID, used for generating new unique IDs. */

    /**
     * @brief Adds a question object to the internal maps.
     * @param question A pointer to the Question object to be added.
     */
    void pushQuestion(Question* question);

    /**
     * @brief Recursively lists the question feed, including replies.
     * @param user A pointer to the current User.
     * @param question A pointer to the current Question to list.
     * @param indent The current indentation level.
     */
    void listFeed(User* user, Question* question, int indent) const;

    /**
     * @brief Prints questions received by a specific user.
     * @param receivedQuestion A pointer to the question received.
     * @param indent The indentation level for printing.
     */
    void printReceivedQuestions(Question* receivedQuestion, int indent) const;

    /**
     * @brief Recursively removes a question and its children from the system.
     * @param question A pointer to the Question to be removed.
     */
    void removeQuestionThreaded(Question* question);

    /**
     * @brief Clears all question data from memory.
     */
    void clear();

   public:
    /**
     * @brief Links temporary IDs to actual User and Question objects after all data is loaded.
     * @param usersIdMap A map of user IDs to User objects.
     */
    void linkObjects(const std::map<int, User*>& usersIdMap);

    /**
     * @brief Removes a question from the system.
     * @param question A pointer to the Question to be removed.
     */
    void removeQuestion(Question* question);

    /**
     * @brief Adds a new question to the system.
     * @param sender A pointer to the User who sent the question.
     * @param recipient A pointer to the User who is the recipient of the question.
     * @param questionText The content of the question.
     * @param isAnonymous True if the question is anonymous, false otherwise.
     * @param parent A pointer to the parent question if this is a reply, nullptr otherwise.
     * @return A pointer to the newly created Question object.
     */
    Question* addQuestion(User* sender, User* recipient, const std::string& questionText,
                          bool isAnonymous = false, Question* parent = nullptr);

    /**
     * @brief Retrieves a question by its ID.
     * @param id The ID of the question to retrieve.
     * @return A pointer to the Question object if found, nullptr otherwise.
     */
    Question* getQuestionById(int id) const;

    /**
     * @brief Prints questions received by a specific user.
     * @param receivedQuestions A vector of Question pointers received by the user.
     */
    void printReceivedQuestions(const std::vector<Question*>& receivedQuestions) const;

    /**
     * @brief Prints questions sent by a specific user.
     * @param sentQuestions A vector of Question pointers sent by the user.
     */
    void printSentQuestions(const std::vector<Question*>& sentQuestions) const;

    /**
     * @brief Lists the question feed for a given user.
     * @param user A pointer to the User for whom to list the feed.
     * @param indent The initial indentation level.
     */
    void listFeed(User* user, int indent = 1) const;

    /**
     * @brief Loads all question data from persistent storage.
     */
    void loadDatabase();

    /**
     * @brief Updates all question data to persistent storage.
     */
    void updateDatabase();

    /**
     * @brief Destructor for QuestionsManager. Cleans up dynamically allocated Question objects.
     */
    ~QuestionsManager();
};