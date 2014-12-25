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

#include "matrix.h"
#include "widget.h"
#include "ui.h"

Matrix::Matrix()
{
    multiply_to_scalar = false;
}

void Matrix::toArray(const QTableWidget *table, const int *l, const int *c, const int num)
{
    //Определяет, какой из двух массивов заполнять.
    if (num == FIRST_ARRAY)
    {
        arr1 = new int*[*l];
        for (int i = 0; i < *l; i++)
            arr1[i] = new int[*c];

        for (int i = 0; i < *l; i++)
            for (int j = 0; j < *c; j++)
                arr1[i][j] = table->item(i, j)->text().toInt();
    }
    else if (num == SECOND_ARRAY)
    {
        arr2 = new int*[*l];
        for (int i = 0; i < *l; i++)
            arr2[i] = new int[*c];

        for (int i = 0; i < *l; i++)
            for (int j = 0; j < *c; j++)
                arr2[i][j] = table->item(i, j)->text().toInt();
    }
}

void Matrix::add(const int *l, const int *c)
{
    initializeArray(l, c);

    for (int i = 0; i < *l; i++)
        for (int j = 0; j < *c; j++)
            array[i][j] = arr1[i][j] + arr2[i][j];

}

void Matrix::subtract(const int *l, const int *c)
{
    initializeArray(l, c);

    for (int i = 0; i < *l; i++)
        for (int j = 0; j < *c; j++)
            array[i][j] = arr1[i][j] - arr2[i][j];
}

void Matrix::multiply(const int *l1, const int *c1, const int *l2, const int *c2)
{
    /*Так как c1 и l2 имеют одинаковое значение (столбец 1-го и строка 2-го массива),
    используется только одна переменная.*/
    initializeArray(l1, c2);

    for (int i = 0; i < *l1; i++)
        for (int j = 0; j < *c2; j++)
        {
            array[i][j] = 0;
            for (int m = 0; m < *l2; m++)
                array[i][j] += arr1[i][m] * arr2[m][j];
        }
}

void Matrix::multiplyToScalar(const int *l, const int *c, const int scalar)
{
    initializeArray(l, c);

    for (int i = 0; i < *l; i++)
        for (int j = 0; j < *c; j++)
            array[i][j] = arr1[i][j] * scalar;

    //Второй массив не использовался.
    multiply_to_scalar = true;
}

void Matrix::toTable(QTableWidget *table, const int *row, const int *column)
{
    QTableWidgetItem *null;
    for (int i = 0; i < *row; i++)
        for (int j = 0; j < *column; j++)
        {
            null = new QTableWidgetItem(QString("%1").arg(array[i][j]));
            table->setItem(i, j, null);
        }
}

void Matrix::initializeArray(const int *r, const int *c)
{
    array = new int*[*r];
    for (int i = 0; i < *r; i++)
        array[i] = new int[*c];
    //Сохраняет количество строк и столбцов для сохранения результата в файл.
    row = *r;
    column = *c;
}

bool Matrix::toFile(UI::GUI *form)
{
    QFile file("result.dat");
    if(!file.open(QFile::WriteOnly | QFile::Text))
        return false;
    else
    {
        QTextStream bufer(&file);
        /*Устанавливает значения строк и столбцов результирующего массива и запрещает их изменять,
        пока сохранённый результат не будет использован.*/
        form->ln_line1->setText(QString("%1").arg(row));
        form->ln_column1->setText(QString("%1").arg(column));
        form->ln_line1->setEnabled(false);
        form->ln_column1->setEnabled(false);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
            {
                //Чтобы не зациклить чтение файла не ставит в конце пробел.
                if (i == (row - 1) && j == (column - 1))
                    bufer << array[i][j];
                else
                    bufer << array[i][j] << " ";
            }
        file.flush();
        file.close();
        return true;
    }
}

Matrix::~Matrix()
{
    delete array;
    //Если второй массив не использовался - не удаляется.
    if (!multiply_to_scalar)
        delete arr2;
    delete arr1;
}
