#pragma once
#include "users/Customer.hpp"
#include "Helper.hpp"
#include "MenuHandler.hpp"
enum class CustomerMainMenuChoice {
    InvalidChoice = 0,

    ViewProfile = 1,
    MakeItinerary,
    ListMyItineraries,
    Logout,

};
enum class CustomerMakeItineraryMenuChoice {
    InvalidChoice = 0,

    AddFlight = 1,
    AddHotel,
    Done,
    Cancel

};


class CustomerSession
{
private:
    Customer* cur_customer;

    // Menu handlers
    const MenuHandler<CustomerMainMenuChoice> main_menu_handler;
    const MenuHandler<CustomerMakeItineraryMenuChoice> make_itinerary_menu_handler;

    void add_flight(Itinerary& new_itinerary);
    void add_hotel(Itinerary& new_itinerary);
    void list_itineraries();
    CustomerMainMenuChoice main_menu();
    void logout();
    CustomerMakeItineraryMenuChoice view_make_itinerary_menu();
    void run_make_itinerary_menu();
    void show_profile();
public:
    CustomerSession(Customer* cur_customer);
    void run_main_menu();
};