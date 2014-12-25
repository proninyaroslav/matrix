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

#ifndef UI_H
#define UI_H

#include <QWidget>
#include <QtWidgets>
#include "widget.h"

namespace UI
{
//Класс установки элементов на виджет.
class GUI
{
private:
    QStringList combo_lst;
    int l1, c1, l2, c2;
public:
    QLabel *lb1;
    QLabel *lb2_1;
    QLabel *lb3;
    QLabel *lb4;
    QLabel *lb5;
    QLabel *lb2_2;
    QComboBox *combo;
    QPushButton *b_continue;
    QPushButton *b_cancel;
    QLineEdit *ln_line1;
    QLineEdit *ln_column1;
    QLineEdit *ln_num;
    QLineEdit *ln_line2;
    QLineEdit *ln_column2;
    QTableWidget *table1;
    QTableWidget *table2;
    QHBoxLayout *h_layout1;
    QHBoxLayout *h_layout2;
    QVBoxLayout *v_layout1;
    QPushButton *b_move;
    QPushButton *b_count;
    QTableWidget *table3;
    QPushButton *b_exit;
    QLabel *lb6;
    QCheckBox *chbx_save;
    QHBoxLayout *h_layout3;
    QHBoxLayout *h_layout4;
    QVBoxLayout *v_layout2;

    //Установка элементов на виджеты.
    void setForm1(QWidget *Widget);
    void setForm2(QWidget *Widget, Widget1 *widget1);
    void setForm3(QWidget *Widget, Widget1 *widget1, Matrix *matrix);
    //Копирование ячеек из первой таблицы во вторую.
    void moveItems(void);
    //Заполнение таблиц нулями.
    void setNull(QTableWidget *table, const int *row, const int *column);
    //Извлечение сохранённого результата для последующих вычислений.
    bool fromFile(const int *row, const int *column);
};

#endif
}
