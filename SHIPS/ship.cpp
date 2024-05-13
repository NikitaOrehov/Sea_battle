#include "ship.h"
#include <iostream>

Ship::Ship(int size){
    hp = size;
    _size = size;
    _coor = new coordinates[_size];
    for (int i = 0; i < _size; i++){
        _coor[i].row = 1;
        _coor[i].col = 1 + i;
    }
    _direction = 0;
}

Ship::Ship(){
    _size = 3;
    hp = _size;
    _coor = new coordinates[_size];
    _coor[0].col = 1;
    _coor[0].row = 1;
    _coor[1].row = 1;
    _coor[1].col = 2;
    _coor[2].row = 1;
    _coor[2].col = 3;
    _direction = 0;
}

Ship::Ship(const Ship& ship){
    _size = ship._size;
    hp = _size;
    _direction = ship._direction;
    _coor = new coordinates[_size];
    for (int i = 0; i < _size; i++){
        _coor[i].col = _coor[i].col;
        _coor[i].row = _coor[i].row;
    }
}

void Ship::operator=(const Ship& ship){
    _size = ship._size;
    hp = ship.hp;
    _direction = ship._direction;
    for (int i = 0; i < _size; i++){
        _coor[i].col = ship._coor[i].col;
        _coor[i].row = ship._coor[i].row;
    }
}

void Ship::ShipUp(const Field& field){
    for (int i = 0; i < _size; i++){
        if (_coor[i].row - 1 == 0){
            throw "You can't do that";
        }
    }
    for (int i = 0; i < _size; i++){
        _coor[i].row -= 1;

    }
}

void Ship::ShipDown(const Field& field){
    for (int i = 0; i < _size; i++){
        if (_coor[i].row + 1 == 11){
            throw "You can't do that";
        }
    }
    for (int i = 0; i < _size; i++){
        _coor[i].row += 1;
    }
}

void Ship::ShipLeft(const Field& field){
    for (int i = 0; i < _size; i++){
        if (_coor[i].col - 1 == 0){
            throw "You can't do that";
        }
    }
    for (int i = 0; i < _size; i++){
        _coor[i].col -= 1;
    }
}

void Ship::ShipRight(const Field& field){
    for (int i = 0; i < _size; i++){
        if (_coor[i].col + 1 == 11){
            throw "You can't do that";
        }
    }
    for (int i = 0; i < _size; i++){
        _coor[i].col += 1;
    }
}

void Ship::Turn(const Field& field){
    if (_size == 1){
        return;
    }
    if (_size == 2 && _direction == 0){
        if (_coor[0].col < _coor[1].col){
            if (_coor[1].row - 1 != 0){
                _coor[1].col -= 1;
                _coor[1].row -= 1;
                
            }
            else{
                _coor[1].col -= 1;
                _coor[1].row += 1;
            }
        }
        else{
            if (_coor[0].row - 1 != 0){
                _coor[0].col -= 1;
                _coor[0].row -= 1;
            }
            else{
                _coor[0].col -= 1;
                _coor[0].row += 1;
            }           
        }
        _direction = 1;
        return;
    }
    if (_size == 2 && _direction == 1){
        if (_coor[0].row < _coor[1].row){
            if (_coor[0].col + 1 != 11){
                _coor[0].col += 1;
                _coor[0].row += 1;
            }
            else{
                _coor[0].col -= 1;
                _coor[0].row += 1;
            }
        }
        else{
            if (_coor[1].col + 1 != 11){
                _coor[1].col += 1;
                _coor[1].row += 1;
            }
            else{
                _coor[1].col -= 1;
                _coor[1].row += 1;
            }
        }
        _direction = 0;
        return;
    }
    if (_size == 3 && _direction == 0){
        if (_coor[0].row - 1 != 0 && _coor[2].row + 1 != 11 && _coor[0].row + 1 != 11 && _coor[2].row - 1 != 0){
            _coor[0].row -= 1;
            _coor[0].col += 1;
            _coor[2].row += 1;
            _coor[2].col -= 1;
            _direction = 1;
        }
        else{
            throw "You can't do that";
        }
        return;
    }
    if (_size == 3 && _direction == 1){
        if (_coor[0].col - 1 != 0 && _coor[2].col + 1 != 11 && _coor[2].col - 1 != 0 && _coor[0].col + 1 != 11){
            _coor[0].col -= 1;
            _coor[0].row += 1;
            _coor[2].col += 1;
            _coor[2].row -= 1;
            _direction = 0;
        }
        else{
            throw "You can't do that";
        }
        return;
    }
}

int Ship::GetSize() const {
    return _size;
}

int Ship::GetCol(int k) const {
    return _coor[k].col;
}

int Ship::GetRow(int k) const {
    return _coor[k].row;
}

const coordinates* Ship::GetCoordinates() const {
    return _coor;
}

int Ship::CheckPosition(const Field& field){
    for (int k = 0; k < _size; k++){
        int i = _coor[k].row;
        int j = _coor[k].col;
        int answer = field.GetValue(i, j);
        if (answer == -2){
            return 1;
        }
    }
    return 0;
}

void Ship::ChangeHp(int* p){
    hp-=1;
    if (hp == 0){
        std::cout<<"kill";
        *p = 1;
        return;
    }
    else{
        std::cout<<"hit";
        *p = -1;
        return;
    }
    std::cout<<"error3"<<std::endl;
}

void Ship::ChangeCoordinates(int i, int j, bool k, int l){
    _coor[l].row = i;
    _coor[l].col = j;
    _direction = k; 
}

Ship::~Ship(){
    delete [] _coor;
}