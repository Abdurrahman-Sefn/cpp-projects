#include "Expedia.hpp"
#include "Helper.hpp"
#include "AdminSession.hpp"
#include "CustomerSession.hpp"

SystemMainMenuChoice Expedia::system_menu(){
    return main_menu_handler.show_and_get_choice();
}
bool Expedia::enter(){
    auto choice = system_menu();
    switch (choice)
    {
    case SystemMainMenuChoice::Exit:
        return false;
    case SystemMainMenuChoice::SignUp:
        signup();
        break;
    case SystemMainMenuChoice::Login:
        login();
        break;
    case SystemMainMenuChoice::InvalidChoice:
    default:
        std::cout << "\nInvalid choice!\n";
        break;
    }
    return true;
}
void Expedia::login(){
    std::string username = read_validated_input<std::string>("Enter username: ");
    std::string password = read_validated_input<std::string>("Enter password: ");
    cur_user = users_manager.login(username, password);
    if(cur_user){
        std::cout << "\n\tWelcome " << cur_user->get_name() << " !\n";
        return;
    }
    else{
        std::cout << "\n\tInvalid username or password!\n";
    }
}
void Expedia::signup(){
    std::string name;
    std::cout << "Enter your name: ";
    getline(std::cin, name);
    std::string email = read_validated_input<std::string>("Enter your email: ");
    std::string username = read_validated_input<std::string>("Enter username: ");
    while(users_manager.is_username_existed(username)){
        username = read_validated_input<std::string>("\tThis username is already existed. Enter another username: ");
    }
    std::string password = read_validated_input<std::string>("Enter password: ");
    cur_user = users_manager.signup(UserType::Customer, username, password, name, email);
    if(cur_user)
        std::cout << "\n\tWelcome " << cur_user->get_name() << " !\n";
}

void Expedia::run(){
    while(true){
        bool state = enter();
        if(!state){
            return;
        }
        if(cur_user && cur_user->get_user_type() == UserType::Admin){
            AdminSession session(dynamic_cast<Admin*>(cur_user));
            session.run_main_menu();
        }
        else if(cur_user && cur_user->get_user_type() == UserType::Customer){
            CustomerSession session(dynamic_cast<Customer*>(cur_user));
            session.run_main_menu();
        }
        cur_user = nullptr;
    }
}

Expedia::Expedia()
    : main_menu_handler(
        std::vector<std::string>{"Login", "Sign up", "Shutdown system"},
        "\nExpedia System:\n",
        SystemMainMenuChoice::Login,
        SystemMainMenuChoice::Exit)
    {
        load_dummy_data();
    }


void Expedia::load_dummy_data(){
    users_manager.signup(UserType::Customer, "customer1", "111", "Ahmed Ali", "ahmed@example.com");
    
    users_manager.signup(UserType::Admin, "admin1", "222", "Moustafa Admin", "moustafa@expedia.com");

    std::cout << "\n\tDummy data loaded (customer1:111, admin1:222).\n";
}