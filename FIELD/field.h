#pragma once
#include <iostream>
#include "../struct.h"

class Field{
private:
    char** _field;
public:
    const int size = 11;
    Field();
    ~Field();
    void print() const;
    void print(const coordinates* ships, int Long) const ;
    void printDouble(const Field& field) const ;
    void ChangeField(int i, int j, char k);
    int GetValue(int i, int j) const;
};