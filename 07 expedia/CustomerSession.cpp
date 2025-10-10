#include "CustomerSession.hpp"
#include "Helper.hpp"
#include "payment/IPayment.hpp"
#include <iostream>

CustomerSession::CustomerSession(Customer* cur_customer)
    : cur_customer(cur_customer)
    , main_menu_handler(
        std::vector<std::string>{"View profile", "Make Itinerary", 
                                 "List my Itineraries", "Logout"},
        "\nCustomer Main Menu:\n",
        CustomerMainMenuChoice::ViewProfile,
        CustomerMainMenuChoice::Logout)
    , make_itinerary_menu_handler(
        std::vector<std::string>{"Add Flight", "Add Hotel", 
                                 "Done", "Cancel"},
        "\nMake Itinerary Menu:\n",
        CustomerMakeItineraryMenuChoice::AddFlight,
        CustomerMakeItineraryMenuChoice::Cancel)
    {}

void CustomerSession::logout(){
    cur_customer = nullptr;
    std::cout << "\nLogging out " << cur_customer->get_name() << "...\n";
}

CustomerMainMenuChoice CustomerSession::main_menu() {
    return main_menu_handler.show_and_get_choice("for Customer " + cur_customer->get_name());
}

CustomerMakeItineraryMenuChoice CustomerSession::view_make_itinerary_menu() {
    return make_itinerary_menu_handler.show_and_get_choice();
}

void CustomerSession::add_flight(Itinerary& new_itinerary) {
    std::cout << "\n\t--- Add Flight ---\n";
    std::string from, from_date, to, to_date;
    int adults, children;

    std::cout << "\tLeaving from: ";
    read_and_trim(std::cin, from);
    std::cout << "\tLeaving date (DD-MM-YYYY): ";
    read_and_trim(std::cin, from_date);
    std::cout << "\tGoing to: ";
    read_and_trim(std::cin, to);
    std::cout << "\tReturn date (DD-MM-YYYY): ";
    read_and_trim(std::cin, to_date);
    adults = read_validated_input<int>("\tNumber of adults: ", 1);
    children = read_validated_input<int>("\tNumber of children: ", 0);

    OurAirCanadaFlightService air_canada_service;
    OurTurkishFlightService turkish_service;
    
    std::vector<IFlightReservation*> flights_results;
    std::vector<IFlightReservation*> ac_flights = air_canada_service.search_flights(from, from_date, to, to_date, adults, children);
    flights_results.insert(flights_results.end(), ac_flights.begin(), ac_flights.end());
    std::vector<IFlightReservation*> tr_flights = turkish_service.search_flights(from, from_date, to, to_date, adults, children);
    flights_results.insert(flights_results.end(), tr_flights.begin(), tr_flights.end());

    std::cout << "\n\t--- Available Flights: ---\n";
    for(size_t i = 0; i < flights_results.size(); ++i) {
        std::cout << indenter(2) << i + 1 << ": ";
        flights_results[i]->print();
    }
    IFlightReservation* selected_flight = select_from(flights_results, "flight");
    if (selected_flight) {
        new_itinerary.add_reservation(selected_flight);
        std::cout << "\tFlight added to itinerary. Cost: $" << selected_flight->reservation_cost() << std::endl;
    } else {
        std::cout << "\tNo flight selected or available.\n";
    }
    for(auto flight : flights_results) {
        if(flight != selected_flight) {
            delete flight;
        }
    }
}
void CustomerSession::add_hotel(Itinerary& new_itinerary) {
    std::cout << "\n\t--- Add Hotel ---\n";
    std::string country, city, from_date, to_date;
    int adults, children, needed_rooms;
    std::cout << "\tCountry: ";
    read_and_trim(std::cin, country);
    std::cout << "\tCity: ";
    read_and_trim(std::cin, city);
    std::cout << "\tCheck-in date (DD-MM-YYYY): ";
    read_and_trim(std::cin, from_date);
    std::cout << "\tCheck-out date (DD-MM-YYYY): ";
    read_and_trim(std::cin, to_date);
    adults = read_validated_input<int>("\tNumber of adults: ", 1);
    children = read_validated_input<int>("\tNumber of children: ", 0);
    needed_rooms = read_validated_input<int>("\tNumber of rooms: ", 1);
    
    OurHiltonHotelService hilton_service;
    OurMarriotHotelService marriott_service;

    std::vector<IRoomReservation*> room_results;

    std::vector<IRoomReservation*> hilton_rooms = hilton_service.search_rooms(country, city, from_date, to_date, adults, children, needed_rooms);
    room_results.insert(room_results.end(), hilton_rooms.begin(), hilton_rooms.end());

    std::vector<IRoomReservation*> marriott_rooms = marriott_service.search_rooms(country, city, from_date, to_date, adults, children, needed_rooms);
    room_results.insert(room_results.end(), marriott_rooms.begin(), marriott_rooms.end());

    std::cout << "\n\t--- Available Rooms: ---\n";
    for(size_t i = 0; i < room_results.size(); ++i) {
        std::cout << indenter(2) << i + 1 << ": ";
        room_results[i]->print();
    }
    IRoomReservation* selected_room = select_from(room_results, "room");

    if (selected_room) {
        new_itinerary.add_reservation(selected_room);
        std::cout << "\tRoom added to itinerary. Cost: $" << selected_room->reservation_cost() << std::endl;
    } else {
        std::cout << "\tNo room selected or available.\n";
    }
    for(auto room : room_results) {
        if(room != selected_room) {
            delete room;
        }
    }
}

void CustomerSession::run_make_itinerary_menu(){
    std::cout << "\n--- Starting Itinerary Creation ---\n";
    Itinerary* new_itinerary = new Itinerary(); 
    
    while(true){
        auto choice = view_make_itinerary_menu();
        switch (choice)
        {
        case CustomerMakeItineraryMenuChoice::Done:
        {
            if (new_itinerary->total_cost() > 0) {
                
                std::cout << "\nTotal Itinerary Cost: $" << new_itinerary->total_cost() << std::endl;
                
                IPayment* payment_adapter = nullptr;
                
                std::cout << "\n1: PayPal\n2: Stripe\n3: Square\nEnter payment choice (1-3): ";
                int payment_choice = read_validated_input<int>("", 0);
                while(!is_in_range(payment_choice, 1, 3)) {
                     payment_choice = read_validated_input<int>("Invalid payment choice. Try again (1-3): ", 0);
                }

                if (payment_choice == 1) payment_adapter = new PayPalPayment();
                else if (payment_choice == 2) payment_adapter = new StripePayment();
                else if (payment_choice == 3) payment_adapter = new SquarePayment();

                
                std::string name, address, id, expiry;
                int ccv;
                std::cout << "Enter Card Holder Name: ";
                read_and_trim(std::cin, name);
                std::cout << "Enter Billing Address: ";
                read_and_trim(std::cin, address);
                std::cout << "Enter Card ID: ";
                read_and_trim(std::cin, id);
                std::cout << "Enter Expiry Date: ";
                read_and_trim(std::cin, expiry);
                ccv = read_validated_input<int>("Enter CCV: ", 100);

                payment_adapter->SetUserInfo(name, address);
                payment_adapter->SetCardInfo(id, expiry, ccv);
                
                if (payment_adapter->MakePayment(new_itinerary->total_cost())) {
                    std::cout << "\nPayment Successful! Itinerary saved.\n";
                    cur_customer->add_itinerary(new_itinerary); 
                } else {
                    std::cout << "\nPayment Failed! Itinerary not saved.\n";
                    delete new_itinerary;
                }
                
                delete payment_adapter;
            } else {
                std::cout << "\nItinerary is empty. Cancelled.\n";
                delete new_itinerary;
            }
            return; 
        }
        case CustomerMakeItineraryMenuChoice::Cancel:
            std::cout << "\nItinerary creation cancelled. All selected reservations discarded.\n";
            delete new_itinerary; 
            return; 
        case CustomerMakeItineraryMenuChoice::AddFlight:
            add_flight(*new_itinerary);
            break;
        case CustomerMakeItineraryMenuChoice::AddHotel:
            add_hotel(*new_itinerary);
            break;
        case CustomerMakeItineraryMenuChoice::InvalidChoice:
        default:
            std::cout << "\nInvalid choice!\n";
            break;
        }
    }
    std::cout << "\n--- Itinerary Creation Ended ---\n";
}
void CustomerSession::show_profile(){
    std::cout << "\n--- Profile Information---\n";
    std::cout << "\tName: " << cur_customer->get_name() << "\n";
    std::cout << "\tUsername: " << cur_customer->get_username() << "\n";
    std::cout << "\tEmail: " << cur_customer->get_email() << "\n";
    std::cout << "-------------------------------------------\n";
}
void CustomerSession::list_itineraries(){
    
    std::cout << "-------------------------------------\n";
}

void CustomerSession::run_main_menu(){
    while(cur_customer){
        auto choice = main_menu();
        switch (choice)
        {
        case CustomerMainMenuChoice::Logout:
            logout();
            return;
        case CustomerMainMenuChoice::ViewProfile:
            show_profile();
            break;
        case CustomerMainMenuChoice::MakeItinerary:
            run_make_itinerary_menu();
            break;
        case CustomerMainMenuChoice::ListMyItineraries:
            list_itineraries();
            break;
        case CustomerMainMenuChoice::InvalidChoice:
        default:
            std::cout << "\nInvalid choice!\n";
            break;
        }
    }
}