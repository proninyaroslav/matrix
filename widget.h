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

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "matrix.h"
namespace UI
{
class GUI;
}

class Widget1;

class Widget3 : public QWidget
{
    Q_OBJECT
private:
    UI::GUI *form3;
    Widget1 *widget1_3;
public:
    explicit Widget3(UI::GUI *form1, Widget1 *widget1, QWidget *parent = 0);
    Matrix *matrix;
    ~Widget3();
};

class Widget2 : public QWidget
{
    Q_OBJECT
private:
    UI::GUI *form2;
    Widget1 *widget1_2;
public:
    explicit Widget2(UI::GUI *form1, Widget1 *widget1, QWidget *parent = 0);
public slots:
    void b_moveClicked(void);
};

class Widget1 : public QWidget
{
    Q_OBJECT
private:
    UI::GUI *form1;
    Widget2 *widget2;
    Widget3 *widget3;
public:
    explicit Widget1(QWidget *parent = 0);
    bool result_saved;
    ~Widget1();
public slots:
    void comboSelectItem(QString item);
    void b_continueClicked(void);
    void b_countClicked(void);
    void b_exitClicked(void);
};

#endif
