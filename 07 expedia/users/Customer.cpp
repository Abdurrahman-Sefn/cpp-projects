#include "Customer.hpp"

Customer::Customer(const std::string& username, const std::string& password,
         const std::string& name, const std::string& email)
            : IUser(UserType::Customer, username, password, name, email) {}

const std::vector<Itinerary*>& Customer::get_itineraries() const {
    return itineraries;
}

void Customer::add_itinerary(Itinerary* itinerary) {
    itineraries.push_back(itinerary);
}