#pragma once
#include "IReservation.hpp"

class Itinerary
{
private:
    std::vector<IRerservation*> rerservations;
public:
    double total_cost() const{
        double total = 0;
        for(auto &reservation : rerservations){
            total += reservation->reservation_cost();
        }
        return total;
    }
    void add_reservation(IRerservation* reservation){
        rerservations.push_back(reservation);
    }

};
