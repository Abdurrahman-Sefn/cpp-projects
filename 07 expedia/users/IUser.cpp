#include "IUser.hpp"

IUser::IUser(UserType type, const std::string& username, const std::string& password, const std::string& name, const std::string& email)
    : type(type), username(username), password(password), name(name), email(email) {}

bool IUser::verify(const std::string &username_, const std::string &password_)const{
    return username == username_ && password == password_;
}
const std::string &IUser::get_name()const { return name; }
const std::string &IUser::get_username()const { return username; }
const std::string &IUser::get_email()const { return email; }
UserType IUser::get_user_type() const{ return type; }