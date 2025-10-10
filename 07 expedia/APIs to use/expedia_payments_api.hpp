/*
 * expedia_payments_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_PAYMENTS_API_H_
#define EXPEDIA_PAYMENTS_API_H_



#include <nlohmann/json.hpp>
using json = nlohmann::json;


class PayPalCreditCard {
public:
	std::string name;
	std::string address;
	std::string id;
	std::string expiry_date;
	int ccv;
};

class PayPalOnlinePaymentAPI {
public:
	void SetCardInfo(const PayPalCreditCard* const card) {
	}
	bool MakePayment(double money) {
		return true;
	}
};

class StripeUserInfo {
public:
	std::string name;
	std::string address;
};

class StripeCardInfo {
public:
	std::string id;
	std::string expiry_date;
};

class StripePaymentAPI {
public:
	bool static WithDrawMoney(StripeUserInfo user, StripeCardInfo card, double money) {
		return true;
	}
};

class SquarePaymentAPI {
public:
	bool static WithDrawMoney(std::string JsonQuery) {
		//cout << JsonQuery << "\n";
		json obj = json::parse(JsonQuery);
		return true;
	}
};


#endif /* EXPEDIA_PAYMENTS_API_H_ */
