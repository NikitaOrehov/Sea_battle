#pragma once
#include "../FIELD/field.h"
#include "../SHIPS/ship.h"

// template <typename T>
class Player{
private:
protected:
    int hp;
    Ship* ships;
    Field _my_field;
    Field _enemy_field;
public:
    Player(){
        hp = 16;
        ships = new Ship[9];
        for (int i = 0; i < 4; i++){
            ships[i] = Ship(1);
        }
        for (int i = 4; i < 7; i++){
            ships[i] = Ship(2);
        }
        for (int i = 7; i < 9; i++){
            ships[i] = Ship(3);
        }
    }
    virtual void placement() = 0;
    virtual int attack(std::string word, Player& player) = 0;
    int check_cage(int i, int j) const {
        return _my_field.GetValue(i, j);
    }
    void ChangeField(int i, int j, int* p = new int){
        int status_cage = _my_field.GetValue(i, j);
        if (status_cage == -2){
            hp -= 1;
            for (int k = 0; k < 9; k++){
                for (int l = 0; l < ships[k].GetSize(); l++){
                    if (i == ships[k].GetRow(l) && j == ships[k].GetCol(l)){
                        ships[k].ChangeHp(p);
                        _my_field.ChangeField(i, j, 43);
                        std::cout<<" ("<<static_cast<char>(j + 16 + 48)<<i<<")"<<std::endl;
                        return;
                    }
                }
            }
            std::cout<<"error2"<<std::endl;
        }
        if (status_cage == -7){
            *p = 0;
            std::cout<<"missed ("<<static_cast<char>(j + 16 + 48)<<i<<")"<<std::endl;
        }
        if (status_cage != -2 && status_cage != -7){
            std::cout<<"error1"<<std::endl;
        }
        _my_field.ChangeField(i, j, 43);
        return;
    }
    int GetHp(){
        return hp;
    }

    void PrintInfo() const {
        _my_field.printDouble(_enemy_field);
    }
    ~Player(){
        delete [] ships;
    }
};