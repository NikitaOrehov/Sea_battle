#include "field.h"

Field::Field(){
    _field = new char*[size];
    for (int i = 0 ; i < size; i++){
        _field[i] = new char[size];
    }
    for (int i = 1; i < size; i++){
        _field[i][0] = 48 + i;
        _field[0][i] = 64 + i;
    }
    for (int i = 1; i < size; i++){
        for (int j = 1; j < size; j++){
            _field[i][j] = -7;
        }
    }
    _field[0][0] = 32;
    _field[size - 1][0] = 48;
}

Field::~Field(){
    for (int i = 0; i < 11; i++){
        delete _field[i];
    }
    delete [] _field;
}
//-7 - пусто
//-2 - корабль
//43 - выстрел

void Field::print() const {
    for (int i = 0; i < size; i++){
        if (i == size - 1){
            std::cout<<"1";
        }
        else{
            std::cout<<" ";
        }
        for (int j = 0; j < size; j++){
            std::cout<<_field[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void Field::print(const coordinates* ships, int Long) const {
    for (int i = 0; i < size; i++){
        if (i == size - 1){
            std::cout<<"1";
        }
        else{
            std::cout<<" ";
        }
        for (int j = 0; j < size; j++){
            int x = 0;
            for (int k = 0; k < Long; k++){
                if (i == ships[k].row && j == ships[k].col){
                    std::cout<<static_cast<char>(254)<<" ";
                    x = -1;
                    break;
                }
            }
            if (x == 0){
                std::cout<<_field[i][j]<<" ";
            }
        }
        std::cout<<std::endl;
    }
}

void Field::ChangeField(int i, int j, char k){
    _field[i][j] = k;
}

int Field::GetValue(int i, int j) const {
    char answer = _field[i][j];
    int answer1 = _field[i][j];
    return _field[i][j];
}

void Field::printDouble(const Field& field) const {
    std::cout<<"my field"<<"\t\t\t\t"<<"enemy_field"<<std::endl;
    for (int i = 0; i < 11; i++){
        if (i == size - 1){
            std::cout<<"1";
        }
        else{
            std::cout<<" ";
        }
        for (int j = 0; j < 11; j++){
            std::cout<<_field[i][j]<<" ";
        }
        std::cout<<"\t\t\t";
        if (i == size - 1){
            std::cout<<"1";
        }
        else{
            std::cout<<" ";
        }
        for (int j = 0; j < 11; j++){
            std::cout<<field._field[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}