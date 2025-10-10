#include "UsersManager.hpp"
#include <iostream>

void UsersManager::push_user(IUser* user){
    usrname_user_mp[user->get_username()] = user;
}

Customer* UsersManager::get_customer_by_usrname(std::string usrname)const{
    auto it = usrname_user_mp.find(usrname);
    if(it != usrname_user_mp.end() && it->second->get_user_type() == UserType::Customer)
        return dynamic_cast<Customer*>(it->second);
    return nullptr;
}

Admin* UsersManager::get_Admin_by_usrname(std::string usrname)const{
    auto it = usrname_user_mp.find(usrname);
    if(it != usrname_user_mp.end() && it->second->get_user_type() == UserType::Admin)
        return dynamic_cast<Admin*>(it->second);
    return nullptr;
}

bool UsersManager::is_username_existed(std::string usrname)const{
    return usrname_user_mp.count(usrname);
}

IUser* UsersManager::login(std::string usrname, std::string password)const{
    auto it = usrname_user_mp.find(usrname);
    if(it != usrname_user_mp.end() && it->second->verify(usrname, password))
        return it->second;
    return nullptr;
}

IUser* UsersManager::signup(UserType type, std::string usrname, std::string password, std::string name, std::string email){
    if(is_username_existed(usrname)){
        return nullptr;
    }
    IUser* new_user = nullptr;
    if(type == UserType::Admin){
        new_user = new Admin(usrname, password, name, email);
    }
    else if(type == UserType::Customer){
        new_user = new Customer(usrname, password, name, email);
    }

    if(new_user){
        push_user(new_user);
    }
    return new_user;
}

UsersManager::~UsersManager(){
    for(auto &pair : usrname_user_mp){
        delete pair.second;
    }
}