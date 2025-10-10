#pragma once
#include "IUser.hpp"

class Admin : public IUser
{
public:
    Admin(const std::string& username, const std::string& password, 
          const std::string& name, const std::string& email);
    
};