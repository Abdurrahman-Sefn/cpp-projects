#include "LibrarySystem.hpp"

LibrarySystem::VerificationResult LibrarySystem::verify() {
    auto [bookPtr, bookName] = booksManager.enterBook();
    if (!bookPtr) {
        std::cout << "Book is not existed!\n";
        return VerificationResult();
    }
    auto [userPtr, userName] = usersManager.enterUser();
    if (!userPtr) {
        std::cout << "User is not existed!\n";
        return VerificationResult();
    }
    return VerificationResult{true, const_cast<User*>(userPtr), const_cast<Book*>(bookPtr)};
}
void LibrarySystem::borrowBook() {
    VerificationResult verification = verify();
    if (!verification.success) return;
    if (booksManager.userBorrowBook(verification.user, verification.book)) {
        usersManager.userBorrowBook(verification.user, verification.book);
        std::cout << "Book (" << verification.book->getName() << ") is borrowed by User ("
                  << verification.user->getName() << ")\n";
    } else {
        std::cout << "Sorry, This book is not available now!\n";
    }
}
void LibrarySystem::returnBook() {
    VerificationResult verification = verify();
    if (!verification.success) return;
    bool bookResult = booksManager.userReturnBook(verification.user, verification.book);
    bool userResult = usersManager.userReturnBook(verification.user, verification.book);
    if (bookResult && userResult) {
        std::cout << "Book (" << verification.book->getName() << ") is returned by User ("
                  << verification.user->getName() << ")\n";
    } else if (!bookResult && !userResult) {
        std::cout << "This user did not borrow this book before.\n";
    } else
        throw std::invalid_argument("Incompatible data");
}

void LibrarySystem::run() {
    std::cout << "\n******************Welcome!******************\n";
    loadDatabase();
    std::vector<std::string> menu{"add a book",
                                  "search books by prefix",
                                  "print who borrowed a book",
                                  "print library books by ID",
                                  "print library books by name",
                                  "add a user",
                                  "user borrow a book",
                                  "user return a book",
                                  "print users",
                                  "Exit"};
    while (true) {
        showMenu(menu, "Main menu");
        int choice = Sefn::readValidatedInput<int>("choose from [1 - 10]: ");
        switch (choice) {
            case 1:
                booksManager.addBook();
                break;
            case 2:
                booksManager.searchBooksByPrefix();
                break;
            case 3:
                booksManager.printWhoBorrowedBookByName();
                break;
            case 4:
                booksManager.printLibraryById();
                break;
            case 5:
                booksManager.printLibraryByName();
                break;
            case 6:
                usersManager.addUser();
                break;
            case 7:
                borrowBook();
                break;
            case 8:
                returnBook();
                break;
            case 9:
                usersManager.printUsers();
                break;
            case 10:
                updateDatabase();
                std::cout << "\n********************Bye!********************\n";
                return;
                break;
        }
    }
}

void LibrarySystem::loadDatabase() {}
void LibrarySystem::updateDatabase() {}