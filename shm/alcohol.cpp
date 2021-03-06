#include "alcohol.hpp"

#include <string>

constexpr size_t maxPower{96};

// Override from Cargo
Alcohol::Alcohol(std::string name, size_t amount, size_t basePrice, size_t power, Time* Publisher)
    : Cargo(name, amount, basePrice), power_(power), Publisher_(Publisher) {
    this->Publisher_->addObserver(this);
}

void Alcohol::nextDay(){
    if(power_ > 0){
        --power_;
    }
}
    

size_t Alcohol::getPrice() const {
    return basePrice_ * (power_ / maxPower);
}

std::string Alcohol::getName() const {
    return name_;
}

size_t Alcohol::getAmount() const {
    return amount_;
}

size_t Alcohol::getBasePrice() const {
    return basePrice_;
}

size_t Alcohol::getPower() const {
    return power_;
}
