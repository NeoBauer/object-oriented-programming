#include "alcohol.hpp"
#include "cargo.hpp"
#include "coordinates.hpp"
#include "fruit.hpp"
#include "island.hpp"
#include "item.hpp"
#include "map.hpp"
//#include "observer.hpp" not ready yet
#include "player.hpp"
#include "ship.hpp"
//#include "time.hpp" not ready yet

#include <iostream>
#include <memory>

int main() {
    Ship T(20, 100, -5);
    Ship FD(100, 50, 12, "Flying Dutchman", 1);
    //int capacity, int maxCrew, int speed, const std::string& name, int id
    //std::unique_ptr<Ship> uPtr = std::make_unique<Ship>(FD);
    //std::cout << FD.getCapacity();  
    // size_t getMaxCrew() const; 
    // size_t getSpeed() const;
    // std::string getName() const;
    // int getId() const;
    // Cargo* getCargo(size_t cargo);
    // std::vector<Cargo> getAllCargo() const;

    return 0;
}
