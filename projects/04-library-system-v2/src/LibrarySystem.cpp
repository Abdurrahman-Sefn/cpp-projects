#include "LibrarySystem.hpp"

#include <fstream>

LibrarySystem::LibrarySystem() {
    loadBorrowsDatabase();
}

void LibrarySystem::loadBorrowsDatabase() {
    std::ifstream data("BorrowOperations.txt");
    if (data.fail()) {
        data.close();
        throw std::invalid_argument(
            "CAN't open database of borrow operations --> \"BorrowOperations.txt\"");
    }
    std::string borrowStr;
    while (readAndTrim(data, borrowStr)) {
        int userId{-1};
        int bookId{-1};
        borrowsManager.deserialize(borrowStr, userId, bookId);
        const User *user = usersManager.getUserById(userId);
        const Book *book = booksManager.getBookById(bookId);
        borrowsManager.createBorrowLink(user, book);
    }
}

LibrarySystem::VerificationResult LibrarySystem::verify() {
    auto [bookPtr, bookName] = booksManager.enterBook();
    if (!bookPtr) {
        std::cout << "\tBook is not existed!\n";
        return VerificationResult();
    }
    auto [usrPtr, usrName] = usersManager.enterUser();
    if (!usrPtr) {
        std::cout << "\tUser is not existed!\n";
        return VerificationResult();
    }
    return VerificationResult{true, const_cast<User *>(usrPtr), const_cast<Book *>(bookPtr)};
}
void LibrarySystem::borrowBook() {
    VerificationResult verification = verify();
    if (!verification.success) return;
    BorrowResult borrowRequest = borrowsManager.borrowBook(verification.user, verification.book);
    std::cout << "\t";
    switch (borrowRequest) {
        case BorrowResult::SUCCESS:
            booksManager.decrementBook(verification.book);
            std::cout << "Book " << verification.book->getNameFormatted() << " is borrowed by User "
                      << verification.user->getNameFormatted() << "\n";
            break;
        case BorrowResult::BOOK_NOT_AVAILABLE:
            std::cout << "Book " << verification.book->getNameFormatted()
                      << " is not available for now\n";
            break;
        case BorrowResult::USER_REACHED_MAX_BORROWED_BOOKS:
            std::cout << "User " << verification.user->getNameFormatted()
                      << " has reached maximum limit of borrowed books. Try return a one\n";
            break;
        case BorrowResult::USER_REACHED_MAX_REPETITIONS:
            std::cout << "User " << verification.user->getNameFormatted()
                      << " has reached maximum limit of borrowing this book. Try return a one\n";
            break;
    }
}
void LibrarySystem::returnBook() {
    VerificationResult verification = verify();
    if (!verification.success) return;
    bool returnRequest = borrowsManager.returnBook(verification.user, verification.book);
    if (returnRequest) {
        booksManager.incrementBook(verification.book);
        std::cout << "\tBook " << verification.book->getNameFormatted() << " is returned by User "
                  << verification.user->getNameFormatted() << "\n";
    } else {
        std::cout << "\tThis user did not borrow this book before.\n";
    }
}

void LibrarySystem::printWhoBorrowedBookByName() {
    auto [book, bookName] = booksManager.enterBook();
    if (!book) {
        std::cout << "\tThere is no book with such name.\n";
        return;
    }
    const std::vector<BorrowOperation *> &bookHistory = borrowsManager.getBookHistory(book);
    usersManager.printBorrowers(bookHistory);
}

void LibrarySystem::printUserBorrowedBooks() {
    auto [user, userName] = usersManager.enterUser();
    if (!user) {
        std::cout << "\tThere is no users with such name.\n";
        return;
    }
    const std::vector<BorrowOperation *> &userHistory = borrowsManager.getUserHistory(user);
    booksManager.printBorrowedBooks(userHistory);
}

void LibrarySystem::addBook() {
    std::string bookAddedFormattedName;
    AddBookResult addingRequest = booksManager.addBook(bookAddedFormattedName);
    switch (addingRequest) {
        case AddBookResult::NAME_IS_EXISTED_BEFORE:
            std::cout << "\tThis name is already existed!\n";
            break;
        case AddBookResult::ID_IS_EXISTED_BEFORE:
            std::cout << "\tThis id is already existed!\n";
            break;
        case AddBookResult::INVALID_QUANTITY:
            std::cout << "\tQuantity must be greater than zero\n";
            break;
        case AddBookResult::SUCCESS:
            std::cout << "\tBook " << bookAddedFormattedName << " has been added to the system!\n";
    }
}
void LibrarySystem::addUser() {
    std::string userAddedFormattedName;
    AddUserResult addingRequest = usersManager.addUser(userAddedFormattedName);
    switch (addingRequest) {
        case AddUserResult::NAME_IS_EXISTED_BEFORE:
            std::cout << "\tThis name is already existed!\n";
            break;
        case AddUserResult::ID_IS_EXISTED_BEFORE:
            std::cout << "\tThis id is already existed!\n";
            break;
        case AddUserResult::SUCCESS:
            std::cout << "\tUser " << userAddedFormattedName << " has been added to the system!\n";
    }
}
void LibrarySystem::run() {
    std::cout << "\n****************************Welcome!****************************\n";
    std::vector<std::string> menu{"add a book",
                                  "search books by prefix",
                                  "print who borrowed a book",
                                  "print books borrowed by a user",
                                  "print library books by ID",
                                  "print library books by name",
                                  "add a user",
                                  "user borrow a book",
                                  "user return a book",
                                  "print users by name",
                                  "print users by id",
                                  "Exit"};
    while (true) {
        showMenu(menu, "\nMain menu");
        int choice = Sefn::readValidatedInput<int>("\nchoose from [1 - 12]: ");
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                booksManager.searchBooksByPrefix();
                break;
            case 3:
                printWhoBorrowedBookByName();
                break;
            case 4:
                printUserBorrowedBooks();
                break;
            case 5:
                booksManager.printLibraryById();
                break;
            case 6:
                booksManager.printLibraryByName();
                break;
            case 7:
                addUser();
                break;
            case 8:
                borrowBook();
                break;
            case 9:
                returnBook();
                break;
            case 10:
                usersManager.printUsersByName();
                break;
            case 11:
                usersManager.printUsersById();
                break;
            case 12:
                std::cout << "\n******************************Bye!******************************\n";
                return;
                break;
        }
    }
}