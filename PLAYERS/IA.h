#pragma once
#include <iostream>
#include "player.h"
#include <random>
#include <time.h>

class IA: public Player{
private:
    coordinates _coor;
    int count_hits = 0;
public:
    int _memory = 0;
    void placement() override {
        for (int k = 0; k < 9; k++){
            while(true){
                srand(time(nullptr));
                int random_row = 1 + rand() % 10;
                int random_col = 1 + rand() % 10;
                bool direction = rand() % 2;
                if (_my_field.GetValue(random_row, random_col) != -7){
                    continue;
                }
                if (ships[k].GetSize() == 1){
                    _my_field.ChangeField(random_row, random_col, -2);
                    ships[k].ChangeCoordinates(random_row, random_col, direction, 0);
                    break;
                }
                else if(ships[k].GetSize() == 2){
                    if (direction == 0){
                        if (_my_field.GetValue(random_row, random_col - 1) == -7){
                            _my_field.ChangeField(random_row, random_col - 1, -2);
                            _my_field.ChangeField(random_row, random_col, -2);
                            ships[k].ChangeCoordinates(random_row, random_col - 1, direction, 1);
                            ships[k].ChangeCoordinates(random_row, random_col, direction, 0);
                            break;
                        }
                        else if (random_col != 10){
                            if(_my_field.GetValue(random_row, random_col + 1) == -7){
                                _my_field.ChangeField(random_row, random_col + 1, -2);
                                _my_field.ChangeField(random_row, random_col, -2);
                                ships[k].ChangeCoordinates(random_row, random_col + 1, direction, 1);
                                ships[k].ChangeCoordinates(random_row, random_col, direction, 0);
                                break;
                            }
                        }
                    }
                    else{
                        if (random_row != 10){
                            if (_my_field.GetValue(random_row + 1, random_col) == -7){
                                _my_field.ChangeField(random_row + 1, random_col, -2);
                                 _my_field.ChangeField(random_row, random_col, -2);
                                ships[k].ChangeCoordinates(random_row + 1, random_col, direction, 1);
                                ships[k].ChangeCoordinates(random_row, random_col, direction, 0);
                                break;
                            }
                        }
                        else if (_my_field.GetValue(random_row - 1, random_col) == -7){
                            _my_field.ChangeField(random_row - 1, random_col, -2);
                            _my_field.ChangeField(random_row, random_col, -2);
                            ships[k].ChangeCoordinates(random_row - 1, random_col, direction, 1);
                            ships[k].ChangeCoordinates(random_row, random_col, direction, 0);
                            break;
                        }
                    }
                }
                else{
                    if (direction == 0){
                        if (random_col != 10){
                            if (_my_field.GetValue(random_row, random_col - 1) == -7 && _my_field.GetValue(random_row, random_col + 1) == -7){
                                _my_field.ChangeField(random_row, random_col - 1, -2);
                                _my_field.ChangeField(random_row, random_col + 1, -2);
                                _my_field.ChangeField(random_row, random_col, -2);
                                ships[k].ChangeCoordinates(random_row, random_col - 1, direction, 2);
                                ships[k].ChangeCoordinates(random_row, random_col + 1, direction, 1);
                                ships[k].ChangeCoordinates(random_row, random_col, direction, 0);
                                break;
                            }
                        }
                    }
                    else{
                        if (random_row != 10){
                            if (_my_field.GetValue(random_row + 1, random_col) == -7 && _my_field.GetValue(random_row - 1, random_col) == -7){
                                _my_field.ChangeField(random_row + 1, random_col, -2);
                                _my_field.ChangeField(random_row - 1, random_col, -2);
                                _my_field.ChangeField(random_row, random_col, -2);
                                ships[k].ChangeCoordinates(random_row + 1, random_col, direction, 2);
                                ships[k].ChangeCoordinates(random_row - 1, random_col, direction, 1);
                                ships[k].ChangeCoordinates(random_row, random_col, direction, 0);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    int attack(std::string word, Player& player) override{
        srand(time(nullptr));
        if (count_hits >= 100 && _memory != -1){
            count_hits += 1;
            while(true){
                int random_rows = 1 + rand() % 10;
                for (int j = 1; j < 11; j++){
                    if (_enemy_field.GetValue(random_rows, j) != 43){
                        int status_cage = player.check_cage(random_rows, j);
                        _enemy_field.ChangeField(random_rows, j, 43);
                        player.ChangeField(random_rows, j, &_memory);
                            if (status_cage == -2 && _memory == -1){
                                _coor.row = random_rows;
                                _coor.col = j;
                                return 1;
                            }
                        return 0;
                    }
                }
            }
        }
        else if (_memory == -1){
            int status_cage1 = 0;
            int status_cage2 = 0;
            int i = _coor.row;
            int j = _coor.col;
            if (i != 10){
                status_cage1 = _enemy_field.GetValue(i + 1, j);
            }
            if (j != 10){
                status_cage2 = _enemy_field.GetValue(i, j + 1);
            }
            if (status_cage1 != 43 && status_cage1 != 0){
                int status_cage = player.check_cage(i + 1, j);
                _enemy_field.ChangeField(i + 1, j, 43);
                count_hits += 1;
                player.ChangeField(i + 1, j, &_memory);
                if (status_cage == -2 && _memory == -1){
                    _coor.row = i + 1;
                        _coor.col = j;
                    return 1;
                }
                if (status_cage == -2 && _memory == 1){
                    _memory = 0;
                    return 1;
                }
                if (status_cage == -2){
                    return 1;
                }
                _memory = -1;
                return 0;
            }
            else if (_enemy_field.GetValue(i - 1, j) == -2 || _enemy_field.GetValue(i - 1, j) == -7){
                int status_cage = player.check_cage(i - 1, j);
                _enemy_field.ChangeField(i - 1, j, 43);
                player.ChangeField(i - 1, j, &_memory);
                if (status_cage == -2 && _memory == -1){
                    _coor.row = i - 1;
                    _coor.col = j;
                    return 1;
                }
                if (status_cage == -2 && _memory == 1){
                    _memory = 0;
                    return 1;
                }
                if (status_cage == -2){
                    return 1;
                }
                _memory = -1;
                return 0;
            }
            else if (status_cage2 != 43 && status_cage2 != 0){
                int status_cage = player.check_cage(i, j  +1);
                _enemy_field.ChangeField(i, j + 1, 43);
                player.ChangeField(i, j + 1, &_memory);
                if (status_cage == -2 && _memory == -1){
                    _coor.row = i;
                    _coor.col = j + 1;
                    return 1;
                }
                if (status_cage == -2 && _memory == 1){
                    _memory = 0;
                    return 1;
                }
                if (status_cage == -2){
                    return 1;
                }
                _memory = -1;
                return 0;
            }
            else if (_enemy_field.GetValue(i, j - 1) == -2 || _enemy_field.GetValue(i, j - 1) == -7){
                int status_cage = player.check_cage(i, j - 1);
                _enemy_field.ChangeField(i, j - 1, 43);
                player.ChangeField(i, j - 1, &_memory);
                if (status_cage == -2 && _memory == -1){
                    _coor.row = i;
                    _coor.col = j - 1;
                    return 1;
                }
                if (status_cage == -2 && _memory == 1){
                    _memory = 0;
                    return 1;
                }
                if (status_cage == -2){
                    return 1;
                }
                _memory = -1;
                return 0;
            }
            std::cout<<"error"<<std::endl;
            return 0;
        }
        else{
            count_hits += 1;
            while(true){
                srand(time(nullptr));
                int random_row = 1 + rand() % 10;
                int random_col = 1 + rand() % 10;
                if (_enemy_field.GetValue(random_row, random_col) == 43){
                    continue;
                }
                int status_cage = player.check_cage(random_row, random_col);
                _enemy_field.ChangeField(random_row, random_col, 43);
                player.ChangeField(random_row, random_col, &_memory);
                if (status_cage == -2 && _memory == -1){
                    _coor.row = random_row;
                    _coor.col = random_col;
                    return 1;
                }
                if (_memory == 1){
                    return 1;
                }
                return 0;
            }
        }
        return 0;
    }
};