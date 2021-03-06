#include "fruit.hpp"

#include <string>

Fruit::Fruit(std::string name, size_t amount, size_t basePrice, size_t expiryDate, size_t timeElapsed, Time* Publisher)
    : Cargo(name, amount, basePrice), expiryDate_(expiryDate), timeElapsed_(timeElapsed), Publisher_(Publisher) {
    this->Publisher_->addObserver(this);
}

void Fruit::nextDay() {
    this->operator--();
}

size_t Fruit::getPrice() const {
    if (timeToSpoil_) {
        return static_cast<size_t>(basePrice_ * static_cast<long double>(timeToSpoil_) / expiryDate_ );
    }
    return 0;
}

std::string Fruit::getName() const {
    return name_;
}

size_t Fruit::getAmount() const {
    return amount_;
}

size_t Fruit::getBasePrice() const {
    return basePrice_;
}

Fruit& Fruit::operator--() {
    if(timeElapsed_ != expiryDate_) {
        ++timeElapsed_;
        timeToSpoil_ = expiryDate_ - timeElapsed_;
    }
    if(timeElapsed_ == expiryDate_) {
        amount_ = 0;
        timeToSpoil_ = 0;
    }
    return *this;
}

size_t Fruit::getExpiryDate() const {
    return expiryDate_;
}

size_t Fruit::getTimeElapsed() const {
    return timeElapsed_;
}

size_t Fruit::timeToRot() const {
    return expiryDate_ - timeElapsed_;
}
