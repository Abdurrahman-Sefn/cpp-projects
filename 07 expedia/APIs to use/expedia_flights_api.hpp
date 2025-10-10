/*
 * expedia_flights_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_FLIGHTS_API_H_
#define EXPEDIA_FLIGHTS_API_H_
#include <string>
#include <vector>



class AirCanadaCustomerInfo {

};

class AirCanadaFlight {
public:
	double price;
	std::string date_time_from;
	std::string date_time_to;
};

class AirCanadaOnlineAPI {
public:
	static std::vector<AirCanadaFlight> GetFlights(std::string from, std::string from_date, std::string to, std::string to_date, int adults, int childern) {
		std::vector<AirCanadaFlight> flights;

		flights.push_back( { 200, "25-01-2022", "10-02-2022" });
		flights.push_back( { 250, "29-01-2022", "10-02-2022" });
		return flights;
	}
	static bool ReserveFlight(const AirCanadaFlight& flight, const AirCanadaCustomerInfo &info) {
		return true;
	}
};

class TurkishFlight {
public:
	double cost;
	std::string datetime_from;
	std::string datetime_to;
};

class TurkishCustomerInfo {

};

class TurkishAirlinesOnlineAPI {
public:
	void SetFromToInfo(std::string datetime_from, std::string from, std::string datetime_to, std::string to) {
	}
	void SetPassengersInfo(int infants, int childern, int adults) {
	}
	std::vector<TurkishFlight> GetAvailableFlights() const {
		std::vector<TurkishFlight> flights;

		flights.push_back( { 300, "10-01-2022", "10-02-2022" });
		flights.push_back( { 320, "12-01-2022", "10-02-2022" });
		return flights;
	}

	static bool ReserveFlight(const TurkishCustomerInfo &info, const TurkishFlight& flight) {
		return false;
	}
};

#endif /* EXPEDIA_FLIGHTS_API_H_ */
