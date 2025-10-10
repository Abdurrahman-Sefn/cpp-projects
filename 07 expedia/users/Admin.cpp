#include "Admin.hpp"
Admin::Admin(const std::string& username, const std::string& password, 
             const std::string& name, const std::string& email)
                : IUser(UserType::Admin, username, password, name, email) {}