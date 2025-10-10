#pragma once
#include "../APIs to use/expedia_payments_api.hpp"
#include <string>
class IPayment
{
public:
    virtual void SetCardInfo(const std::string &id, const std::string &expiry_date, int _cv) = 0;
    virtual void SetUserInfo(const std::string &name, const std::string &address) = 0;
    virtual bool MakePayment(double money) = 0;
    virtual ~IPayment(){}
};

class PayPalPayment: public IPayment {
private:
	PayPalOnlinePaymentAPI paypal;
	PayPalCreditCard card;
public:
	virtual void SetUserInfo(const std::string &name, const std::string &address) override;
	virtual void SetCardInfo(const std::string &id, const std::string &expiry_date, int ccv) override;
	virtual bool MakePayment(double money) override;
};

class StripePayment: public IPayment {
private:
	StripeCardInfo card;
	StripeUserInfo user;
public:
	virtual void SetUserInfo(const std::string &name, const std::string &address) override;
	virtual void SetCardInfo(const std::string &id, const std::string &expiry_date, int ccv_) override;
	virtual bool MakePayment(double money) override;
};

class SquarePayment: public IPayment {
private:
	std::string name;
	std::string address;
	std::string id;
	std::string expiry_date;
	int ccv;
public:
	virtual void SetUserInfo(const std::string &name_, const std::string &address_) override;
	virtual void SetCardInfo(const std::string &id_, const std::string &expiry_date_, int ccv_) override;
	virtual bool MakePayment(double money) override;
};