#pragma once
#include "users/UsersManager.hpp"
#include "MenuHandler.hpp"

enum class SystemMainMenuChoice {
    InvalidChoice = 0,

    Login = 1,
    SignUp,
    Exit,

};

class Expedia {
    UsersManager users_manager;
    IUser* cur_user{}; 
 
    const MenuHandler<SystemMainMenuChoice> main_menu_handler;

    SystemMainMenuChoice system_menu();
    bool enter();
    void login();
    void signup();
    void load_dummy_data();
public:
    Expedia();
    void run();
};