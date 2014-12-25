/*
 Copyright (c) 2014 Yaroslav Pronin

 This file is part of Matrix.

 Matrix is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Matrix is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Matrix. If not, see <http://www.gnu.org/licenses/>. */

#ifndef MATRIX_H
#define MATRIX_H

#include <QObject>
#include <QtWidgets>

namespace UI
{
class GUI;
}

#define FIRST_ARRAY 1
#define SECOND_ARRAY 2

//Класс операций над матрицами.
class Matrix
{
private:
    int **arr1;
    int **arr2;
    //Размер строк и столбцов.
    int row;
    int column;
    //Используется при удалении 2-го массива.
    bool multiply_to_scalar;
public:
    Matrix();
    //Результирующий массив.
    int **array;
    //Копирование из таблицы в массив.
    void toArray(const QTableWidget *table, const int *l, const int *c, const int num);
    //Инициализация результирующего массива.
    void initializeArray(const int *r, const int *c);
    //Сложение.
    void add(const int *l, const int *c);
    //Вычитание.
    void subtract(const int *l, const int *c);
    //Умножение.
    void multiply(const int *l1, const int *c1, const int *l2, const int *c2);
    //Умножение на скалярное число.
    void multiplyToScalar(const int *l, const int *c, const int scalar);
    //Копирование из результирующего массива в таблицу.
    void toTable(QTableWidget *table, const int *row, const int *column);
    //Сохранение результата.
    bool toFile(UI::GUI *form);
    ~Matrix();
};

#endif
