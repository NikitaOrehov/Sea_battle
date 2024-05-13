#pragma once
#include "../struct.h"
#include "../FIELD/field.h"

class Ship{
private:
    int _size;
    coordinates* _coor;
    bool _direction; //0 - горизонтально     1 - вертикально
    int hp;
public:
    Ship();
    Ship(int _size);
    Ship(const Ship& ship);
    ~Ship();
    void operator=(const Ship& ship);
    void ShipUp(const Field& field);
    void ShipDown(const Field& field);
    void ShipLeft(const Field& field);
    void ShipRight(const Field& field);
    void Turn(const Field& field);
    int GetSize() const;
    int GetCol(int k) const;
    int GetRow(int k) const;
    const coordinates* GetCoordinates() const ;
    int CheckPosition(const Field& field);
    void ChangeHp(int* p);
    void ChangeCoordinates(int i, int j, bool k, int l);
};