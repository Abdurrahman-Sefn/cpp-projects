#pragma once
#include <string>
#include <vector>

enum class UserType
{
    Admin,
    Customer
};

class IUser
{
protected:
    std::string name;
    std::string username;
    std::string password;
    std::string email;
    UserType type;
public:
    IUser(UserType type, const std::string& username, const std::string& password, const std::string& name, const std::string& email);
    virtual bool verify(const std::string &_username, const std::string &_password)const;
    virtual const std::string &get_name()const;
    virtual const std::string &get_username()const;
    virtual const std::string &get_email()const;
    virtual UserType get_user_type() const;
    virtual ~IUser(){}
};
