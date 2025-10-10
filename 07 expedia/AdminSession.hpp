#pragma once
#include "users/Admin.hpp"
class AdminSession
{
private:
    const Admin* const cur_admin;
public:
    AdminSession(Admin* cur_admin);
    void run_main_menu();
};