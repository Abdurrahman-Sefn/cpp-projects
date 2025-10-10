#include "IReservation.hpp"
#include <iostream>

OurHiltonRoom::OurHiltonRoom(const HiltonRoom& room) : room(room){}
OurMarriotRoom::OurMarriotRoom(const MarriottFoundRoom& room) : room(room){}
int OurMarriotRoom::get_total_nights() const {
    return 2;
}
int OurHiltonRoom::get_total_nights() const {
    return 5;
}
double OurHiltonRoom::reservation_cost() const{
    return room.price_per_night * get_total_nights();
}

void OurHiltonRoom::print() const{
    std::cout << "Hilton Room: " << room.room_type << ", Price: $" << room.price_per_night << std::endl;
}
OurHiltonRoom::~OurHiltonRoom(){}

double OurMarriotRoom::reservation_cost() const {
    return room.price_per_night * get_total_nights();
}
void OurMarriotRoom::print() const {
    std::cout << "Marriott Room: " << room.room_type << ", Price: $" << room.price_per_night << std::endl;
}
OurMarriotRoom::~OurMarriotRoom() {}
OurAirCanadaFlight::~OurAirCanadaFlight(){}
IFlightService::~IFlightService(){}
std::vector<IRoomReservation*> OurHiltonHotelService::search_rooms(std::string country, std::string city, 
                                                            std::string from_date, std::string to_date, 
                                                            int adults, int children, int needed_rooms)
{
    std::vector<IRoomReservation*> room_reservations;
    
    std::vector<HiltonRoom> rooms = HiltonHotelAPI::SearchRooms(country, city, from_date, to_date, adults, children, needed_rooms);
    
    for (const auto& room : rooms) {
        room_reservations.push_back(new OurHiltonRoom(room));
    }
    
    return room_reservations;
}

std::vector<IRoomReservation*> OurMarriotHotelService::search_rooms(std::string country, std::string city, 
                                                            std::string from_date, std::string to_date, 
                                                            int adults, int children, int needed_rooms) 
{
    std::vector<IRoomReservation*> room_reservations;
    std::vector<MarriottFoundRoom> rooms = MarriottHotelAPI::FindRooms(from_date, to_date, country, city, needed_rooms, adults, children);    
    for (const auto& room : rooms) {
        room_reservations.push_back(new OurMarriotRoom(room));
    }
    
    return room_reservations;
}

///////////////////////

double OurAirCanadaFlight::reservation_cost() const {
    return flight.price * (adults_count + children_count);
}

void OurAirCanadaFlight::print() const {
    std::cout << "Air Canada Flight: Price $" << flight.price << "/ticket. From: " << flight.date_time_from << std::endl;
}


double OurTurkishFlight::reservation_cost() const {
    return flight.cost * (adults_count + children_count);
}

void OurTurkishFlight::print() const {
    std::cout << "Turkish Airlines Flight: Cost $" << flight.cost << "/ticket. From: " << flight.datetime_from << std::endl;
}

OurTurkishFlight::~OurTurkishFlight() {}

std::vector<IFlightReservation*> OurAirCanadaFlightService::search_flights(std::string from, std::string from_date, 
                                                                       std::string to, std::string to_date, 
                                                                       int adults, int children)
{
    std::vector<IFlightReservation*> flight_reservations;
    std::vector<AirCanadaFlight> flights = AirCanadaOnlineAPI::GetFlights(from, from_date, to, to_date, adults, children);
    for (const auto& flight : flights) {
        flight_reservations.push_back(new OurAirCanadaFlight(flight, adults, children));
    }
    return flight_reservations;
}

std::vector<IFlightReservation*> OurTurkishFlightService::search_flights(std::string from, std::string from_date, 
                                                                       std::string to, std::string to_date, 
                                                                       int adults, int children)
{
    std::vector<IFlightReservation*> flight_reservations;
    api.SetFromToInfo(from_date, from, to_date, to);
    api.SetPassengersInfo(0, children, adults); 
    std::vector<TurkishFlight> flights = api.GetAvailableFlights();
    for (const auto& flight : flights) {
        flight_reservations.push_back(new OurTurkishFlight(flight, adults, children));
    }
    return flight_reservations;
}
