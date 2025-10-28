/**
 * @file QuestionsManager.hpp
 * @brief Manages the collection of questions in the AskMe system, including their relationships and persistence.
 */

#pragma once
#include "Question.hpp"
#include <unordered_map>
#include <map>

/**
 * @class QuestionsManager
 * @brief Handles the creation, storage, retrieval, and management of Question objects.
 * 
 * This class provides functionalities to add new questions, manage question threads (parent-child relationships),
 * print question feeds, and handle data persistence for questions.
 */
class QuestionsManager{
    std::map<int, Question*> id_question_map; /**< Maps question IDs to Question objects for quick lookup. */
    std::unordered_map<Question*, std::vector<Question*> > parent_children_map; /**< Maps parent questions to their child questions. */
    int last_id; /**< The last assigned question ID, used for generating new unique IDs. */

    /**
     * @brief Adds a question object to the internal maps.
     * @param question A pointer to the Question object to be added.
     */
    void push_question(Question* question);

    /**
     * @brief Recursively lists the question feed, including replies.
     * @param user A pointer to the current User.
     * @param question A pointer to the current Question to list.
     * @param indent The current indentation level.
     */
    void list_feed(User* user, Question* question, int indent)const;

    /**
     * @brief Prints questions received by a specific user.
     * @param received_question A pointer to the question received.
     * @param indent The indentation level for printing.
     */
    void print_questions_from_whom(Question* received_question, int indent) const;

    /**
     * @brief Recursively removes a question and its children from the system.
     * @param question A pointer to the Question to be removed.
     */
    void remove_question_threaded(Question* question);

    /**
     * @brief Clears all question data from memory.
     */
    void clear();
public:
    /**
     * @brief Links temporary IDs to actual User and Question objects after all data is loaded.
     * @param users_id_map A map of user IDs to User objects.
     */
    void link_objects(const std::map<int, User*> &users_id_map);

    /**
     * @brief Removes a question from the system.
     * @param question A pointer to the Question to be removed.
     */
    void remove_question(Question* question);

    /**
     * @brief Adds a new question to the system.
     * @param sender A pointer to the User who sent the question.
     * @param receptor A pointer to the User who is the recipient of the question.
     * @param question_text The content of the question.
     * @param is_anonymous True if the question is anonymous, false otherwise.
     * @param parent A pointer to the parent question if this is a reply, nullptr otherwise.
     * @return A pointer to the newly created Question object.
     */
    Question* add_question(User* sender, User* receptor, const std::string &question_text, bool is_anonymous = false, Question* parent = nullptr);

    /**
     * @brief Retrieves a question by its ID.
     * @param id The ID of the question to retrieve.
     * @return A pointer to the Question object if found, nullptr otherwise.
     */
    Question* get_question_by_id(int id)const;

    /**
     * @brief Prints questions received by a specific user.
     * @param received_questions A vector of Question pointers received by the user.
     */
    void print_questions_from_whom(const std::vector<Question*> &received_questions)const;

    /**
     * @brief Prints questions sent by a specific user.
     * @param sent_questions A vector of Question pointers sent by the user.
     */
    void print_questions_to_whom(const std::vector<Question*> &sent_questions)const;

    /**
     * @brief Lists the question feed for a given user.
     * @param user A pointer to the User for whom to list the feed.
     * @param indent The initial indentation level.
     */
    void list_feed(User* user, int indent = 1)const;

    /**
     * @brief Loads all question data from persistent storage.
     */
    void load_database();

    /**
     * @brief Updates all question data to persistent storage.
     */
    void update_database();

    /**
     * @brief Destructor for QuestionsManager. Cleans up dynamically allocated Question objects.
     */
    ~QuestionsManager();
};