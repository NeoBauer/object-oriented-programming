#include "coordinates.hpp"

#include <cmath>

int constexpr DEFAULT_POSITION_X = 0;
int constexpr DEFAULT_POSITION_Y = 0;

Coordinates::Coordinates()
    : positionX_(DEFAULT_POSITION_X), positionY_(DEFAULT_POSITION_Y) {}
   
Coordinates::Coordinates(int positionX, int positionY)
    : positionX_(positionX), positionY_(positionY) {}

int Coordinates::Distance(const Coordinates& PointA, 
                          const Coordinates& PointB) {
    return static_cast<int>(std::sqrt(std::pow((PointA.positionX_ - PointB.positionX_), 2) +
                                      std::pow((PointA.positionY_ - PointB.positionY_), 2)));
}

bool Coordinates::operator==(const Coordinates& currentPosition) const {
    return positionX_ == currentPosition.positionX_ && positionY_ == currentPosition.positionY_;
}

std::ostream& operator<<(std::ostream& print, const Coordinates& coords) {
    return print << "(X:" << coords.getPositionX() << ", Y:" << coords.getPositionY() << ")";
}
