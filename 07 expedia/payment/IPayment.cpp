#include "IPayment.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;



void PayPalPayment::SetUserInfo(const std::string &name, const std::string &address){
	card.name = name;
	card.address = address;
}
void PayPalPayment::SetCardInfo(const std::string &id, const std::string &expiry_date, int ccv){
	card.id = id;
	card.expiry_date = expiry_date;
	card.ccv = ccv;
}
bool PayPalPayment::MakePayment(double money){
	paypal.SetCardInfo(&card);
	return paypal.MakePayment(money);
}


void StripePayment::SetUserInfo(const std::string &name, const std::string &address){
	user.name = name;
	user.address = address;
}
void StripePayment::SetCardInfo(const std::string &id, const std::string &expiry_date, int ccv_){
	card.id = id;
	card.expiry_date = expiry_date;
}
bool StripePayment::MakePayment(double money){
	return StripePaymentAPI::WithDrawMoney(user, card, money);
}



void SquarePayment::SetUserInfo(const std::string &name_, const std::string &address_){
	name = name_;
	address = address_;
}
void SquarePayment::SetCardInfo(const std::string &id_, const std::string &expiry_date_, int ccv_){
	id = id_;
	expiry_date = expiry_date_;
	ccv = ccv_;
}
bool SquarePayment::MakePayment(double money){
	// This now similar to Adapter pattern. We change format of interface to match another interface
	json obj;
	obj["user_info"] = json::array({name, address});
	obj["card_info"]["ID"] = id;
	obj["card_info"]["DATE"] = expiry_date;
	obj["card_info"]["CCV"] = ccv;
	obj["money"] = money;

	std::stringstream oss;
	oss << obj;
	std::string json_query = oss.str();

	return SquarePaymentAPI::WithDrawMoney(json_query);
}

