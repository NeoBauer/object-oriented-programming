#include "store.hpp"
#include "constValues.hpp"

#include <algorithm>
#include <iomanip>

Store::Store(Time* gameTime) : timeTracker_(gameTime) {
    generateGoods();
}

Response Store::buy(std::shared_ptr<Cargo> cargo, size_t amount, Player* player) {
    size_t totalPrice = cargo->getPrice() * amount;

    if (cargo->getAmount() < amount) {
        return Response::lack_of_cargo;
    }
    if (player->getAvailableSpace() < amount) {
        return Response::lack_of_space;
    }
    if (player->getMoney() < totalPrice) {
        return Response::lack_of_money;
    }

    player->purchaseCargo(cargo, totalPrice, amount);

    return Response::done;
}

Response Store::sell(std::shared_ptr<Cargo> cargo, size_t amount, Player* player) {
    if (cargo->getAmount() < amount) {
        return Response::lack_of_cargo;
    }
    *cargo -= amount;
    size_t totalPrice = cargo->getPrice() * amount;

    player->giveMoney(totalPrice);

    if (cargo->getAmount() == 0) {
        player->removeCargo(cargo);
    }
    return Response::done;
}
void Store::generateGoods() {
    cargoToSell_.clear();
    std::random_device device;
    std::mt19937 generator(device());
    randomVal itemNumber(1, 8);
    randomVal expiryDate(constValues::minExpiryDate, constValues::maxExpiryDate);
    randomVal amount(constValues::minAmount, constValues::maxAmount);

    for (size_t i = 0; i < constValues::numerOfItems; i++) {
        AddGeneratedCargo(expiryDate(generator), amount(generator), i);
    }
}

void Store::AddGeneratedCargo(size_t expiryDate, size_t amount, size_t pos) {
    switch (pos) {
    case 1:
        cargoToSell_.emplace_back(std::make_shared<Fruit>(Fruit("Bananas", amount, 35, expiryDate, 0, timeTracker_)));
        break;
    case 2:
        cargoToSell_.emplace_back(
            std::make_shared<Fruit>(Fruit("Watermelon", amount, 35, expiryDate, 0, timeTracker_)));
        break;
    case 3:
        cargoToSell_.emplace_back(std::make_shared<Alcohol>(Alcohol("Jack Daniel’s", amount, 35, 40, timeTracker_)));
        break;
    case 4:
        cargoToSell_.emplace_back(std::make_shared<Alcohol>(Alcohol("Spirit", amount, 35, 96, timeTracker_)));
        break;
    case 5:
        cargoToSell_.emplace_back(
            std::make_shared<Item>(Item("Pistol", amount, 500, static_cast<int>(Rarity::common), timeTracker_)));
        break;
    case 6:
        cargoToSell_.emplace_back(
            std::make_shared<Item>(Item("Cannon", amount, 2000, static_cast<int>(Rarity::common), timeTracker_)));
        break;
    case 7:
        cargoToSell_.emplace_back(
            std::make_shared<Item>(Item("Flag", amount, 65, static_cast<int>(Rarity::common), timeTracker_)));
        break;
    case 8:
        cargoToSell_.emplace_back(std::make_shared<Fruit>(Fruit("Apples", amount, 35, expiryDate, 0, timeTracker_)));
        break;
    default:
        std::cerr << "RNG error!\n";
        break;
    }
}

std::ostream& operator<<(std::ostream& print, const Store& store) {
    std::string trail("-", 40);
    print << "What you want to buy or sell: \n";
    print << std::setw(5) << "No.||" << std::setw(10) << " Name    ||" << std::setw(9) << " Amount ||" << std::setw(14)
          << " Sell Price ||" << std::setw(14) << " Buy Price ||"
          << "\n";

    std::for_each(store.cargoToSell_.begin(), store.cargoToSell_.end(),
                  [&print, &store, i{0}](const auto& cargo) mutable {
                      print << std::setw(2) << ++i << " ||" << std::setw(8) << cargo->getName() << " ||" << std::setw(7)
                            << cargo->getAmount() << " ||" << std::setw(11) << cargo->getPrice() << " ||"
                            << "\n";
                  });
    return print;
}
