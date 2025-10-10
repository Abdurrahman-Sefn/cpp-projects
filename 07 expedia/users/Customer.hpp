#pragma once
#include "IUser.hpp"
#include "../reservations/Itinerary.hpp" 
#include <vector>

class Customer : public IUser
{
private:
    std::vector<Itinerary*> itineraries;
    
public:
    Customer(const std::string& username, const std::string& password,
             const std::string& name, const std::string& email);

    const std::vector<Itinerary*>& get_itineraries()const;
    
    void add_itinerary(Itinerary* itinerary);
};