#pragma once
#include "player.h"
#include "windows.h"
#include <string>

class Human: public Player{
public:
void placement() override {
    int check = 0;
    for (int i = 0; i < 9; i++){
        std::string error;
        while(true){
            _my_field.print(ships[i].GetCoordinates(), ships[i].GetSize());
            char answer = '0';
            answer = getchar();
            system("cls");
            switch (answer){
                case 119: 
                    try{
                        ships[i].ShipUp(_my_field);
                    }
                    catch(const char* messege){
                        error = messege;
                    }
                    break;
                case 115:
                    try{
                        ships[i].ShipDown(_my_field);
                    }
                    catch(const char* messege){
                        error = messege;
                    }
                    break;
                case 100:
                    try{
                        ships[i].ShipRight(_my_field);
                    }
                    catch(const char* messege){
                        error = messege;
                    }
                    break;
                case 97:
                    try{
                        ships[i].ShipLeft(_my_field);
                    }
                    catch(const char* messege){
                        error = messege;
                    }
                    break;
                case 101:
                    try{
                        ships[i].Turn(_my_field);
                    }
                    catch(const char* messege){
                        error = messege;
                    }
                    break;
                default: break;
            }
            if (answer == 32){
                check = ships[i].CheckPosition(_my_field);
                if (check == 0){
                    for (int k = 0; k < ships[i].GetSize(); k++){
                        _my_field.ChangeField(ships[i].GetRow(k), ships[i].GetCol(k), static_cast<char>(-2));
                    }
                    break;
                }
                else{
                    std::cout<<"The cage is occupied"<<std::endl;
                }
            }
        }

    }

}
//65-74 
//65 -49 = 16
    int attack(std::string word, Player& player) override {
        int j = word[0];
        int i = word[1];
        int k = word[2];
        try{
            if (j > 74 && j < 65){
                throw 1;
            }
            if (word.length() <= 2 && i > 57 && i < 49){
                throw 1;
            }
            if (word.length() > 3){
                throw 1;
            }
            if (word.length() == 3 && (i != 49 || k != 48)){
                throw 1;
            }
        }
        catch(int x){
            throw "incorrect input";
        }
        j = j - 16 - 48;
        i -= 48;
        int status_cage = 0;
        if (word.length() == 3){
            status_cage = player.check_cage(10, j);
        }
        else{
            status_cage = player.check_cage(i, j);
        }
        try{
            if (status_cage == 43){
                throw 1;
            }
        }
        catch(int x){
            throw "Error. You've already shot at this cage.";
        }
        if (word.length() == 2){
            player.ChangeField(i, j);
            if (status_cage == -7){
                _enemy_field.ChangeField(i, j, 43);
                return 0;
            }
            else{
                _enemy_field.ChangeField(i, j, -2);
                return 1;
            }
        }
        else{
            player.ChangeField(10, j);
            if (status_cage == -7){
                _enemy_field.ChangeField(10, j, 43);
                return 0;
            }
            else{
                _enemy_field.ChangeField(10, j, -2);
                return 1;
            }
        }
    }
};