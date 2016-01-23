//
// Created by Cory Forward on 1/23/16.
//

#ifndef QWAK_LOCATION_H
#define QWAK_LOCATION_H


class location {
    int l_col;
    int l_row;

public:
    location(int current_column, int current_row) \
    : l_col(current_column), l_row(current_row) { }

    int getColumn() { return this->l_col; }
    int getRow() { return this->l_row; }
};


#endif //QWAK_LOCATION_H
