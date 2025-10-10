#pragma once
#include <unordered_map>
#include "IUser.hpp"
#include "Admin.hpp"
#include "Customer.hpp"

class UsersManager
{
private:
    std::unordered_map<std::string, IUser*> usrname_user_mp;
    void push_user(IUser* user);
public:
    Customer* get_customer_by_usrname(std::string usrname)const;
    Admin* get_Admin_by_usrname(std::string usrname)const;
    bool is_username_existed(std::string usrname)const;
    IUser* login(std::string usrname, std::string password)const;
    IUser* signup(UserType type, std::string usrname, std::string password, std::string name, std::string email);
    ~UsersManager();
};
