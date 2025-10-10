#pragma once
#include "../APIs to use/expedia_hotels_api.hpp"
#include "../APIs to use/expedia_flights_api.hpp"

class Printable
{
public:
    virtual void print() const = 0;
    virtual ~Printable(){}
};

class IRerservation : public Printable
{
public:
    virtual double reservation_cost() const = 0;
    virtual ~IRerservation(){}
};
class IFlightReservation : public IRerservation{};
class IRoomReservation : public IRerservation{
public:
    virtual int get_total_nights() const = 0;
};


class OurHiltonRoom : public IRoomReservation
{
    HiltonRoom room;
public:
    OurHiltonRoom(const HiltonRoom& room);
    virtual int get_total_nights() const override;
    virtual double reservation_cost() const override;
    virtual void print() const override;
    virtual ~OurHiltonRoom();
};

class OurMarriotRoom : public IRoomReservation
{
    MarriottFoundRoom room;
public:
    OurMarriotRoom(const MarriottFoundRoom& room);
    virtual int get_total_nights() const override;
    virtual double reservation_cost() const override;
    virtual void print() const override;
    virtual ~OurMarriotRoom();
};

class IHotelService
{
public:
    virtual std::vector<IRoomReservation*> search_rooms(std::string country, std::string city, 
                                                std::string from_date, std::string to_date, 
                                                int adults, int children, int needed_rooms) = 0; 
};

class OurMarriotHotelService : public IHotelService
{
    MarriottHotelAPI service;
public:
    virtual std::vector<IRoomReservation*> search_rooms(std::string country, std::string city, 
                                                std::string from_date, std::string to_date, 
                                                int adults, int children, int needed_rooms) override; 
};

class OurHiltonHotelService : public IHotelService
{
    HiltonHotelAPI service;
public:
    virtual std::vector<IRoomReservation*> search_rooms(std::string country, std::string city, 
                                                std::string from_date, std::string to_date, 
                                                int adults, int children, int needed_rooms) override; 
};

class OurAirCanadaFlight : public IFlightReservation
{
private:
    AirCanadaFlight flight; 
    int adults_count;
    int children_count;
public:
    OurAirCanadaFlight(const AirCanadaFlight& flight, int adults, int children) : flight(flight), adults_count(adults), children_count(children) {}

    virtual double reservation_cost() const override;
    virtual void print() const override;
    virtual ~OurAirCanadaFlight();
};

class OurTurkishFlight : public IFlightReservation
{
private:
    TurkishFlight flight;
    int adults_count;
    int children_count;
public:
    OurTurkishFlight(const TurkishFlight& flight, int adults, int children) : flight(flight), adults_count(adults), children_count(children) {}

    virtual double reservation_cost() const override;
    virtual void print() const override;
    virtual ~OurTurkishFlight();
};

class IFlightService
{
public:
    virtual std::vector<IFlightReservation*> search_flights(std::string from, std::string from_date, 
                                                           std::string to, std::string to_date, 
                                                           int adults, int children) = 0;
    virtual ~IFlightService();
};

class OurAirCanadaFlightService : public IFlightService
{
public:
    virtual std::vector<IFlightReservation*> search_flights(std::string from, std::string from_date, 
                                                           std::string to, std::string to_date, 
                                                           int adults, int children) override;
};

class OurTurkishFlightService : public IFlightService
{
private:
    TurkishAirlinesOnlineAPI api; 
public:
    virtual std::vector<IFlightReservation*> search_flights(std::string from, std::string from_date, 
                                                           std::string to, std::string to_date, 
                                                           int adults, int children) override;
};