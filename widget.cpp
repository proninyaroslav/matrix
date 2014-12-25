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

#include "widget.h"
#include "ui.h"

Widget3::Widget3(UI::GUI *form1, Widget1 *widget1, QWidget *parent) : QWidget(parent)
{
    //Пр нажатии системной кнопки "Закрыть" вызвается деструктор виджета.
    setAttribute(Qt::WA_DeleteOnClose);
    //Необходимо для использования элементов родительского окна.
    form3 = form1;
    widget1_3 = widget1;
    matrix = new Matrix;
    //Установка собственных элементов.
    form3->setForm3(this, widget1_3, matrix);
}

Widget2::Widget2(UI::GUI *form1, Widget1 *widget1, QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    form2 = form1;
    widget1_2 = widget1;
    form2->setForm2(this, widget1_2);
}

Widget1::Widget1(QWidget *parent) : QWidget(parent), form1(new UI::GUI)
{
    result_saved = false;
    form1->setForm1(this);
}

Widget1::~Widget1()
{
    //Если предыдущее вычисление было сохранено - удаляется временный файл.
    if (result_saved)
    {
        QFile file("result.dat");
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            file.remove();
            file.close();
        }
    }
    delete form1;
}

Widget3::~Widget3()
{
    //Если предыдущее вычисление было сохранено - удаляется временный файл.
    if (widget1_3->result_saved)
    {
        //Поля ввода опять становятся доступными для редактирования.
        form3->ln_line1->setEnabled(true);
        form3->ln_column1->setEnabled(true);
        widget1_3->result_saved = false;
        QFile file("result.dat");
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            file.remove();
            file.close();
        }
    }
    //Если чекбокс установлен - сохранение результата.
    if (form3->chbx_save->isChecked())
    {
        if(!matrix->toFile(form3))
            QMessageBox::critical(this, "Matrix", "Не удалось сохранить результат.", QMessageBox::Ok);
        //Установка флага сохранения результата.
        widget1_3->result_saved = true;
    }
    delete matrix;
}

void Widget1::comboSelectItem(QString item)
{
    //Сброс настроек к значениям по умолчанию.
    form1->lb1->setText("Размер матриц");
    form1->lb1->setEnabled(true);
    form1->lb2_1->setEnabled(true);
    form1->ln_line2->hide();
    form1->ln_column2->hide();
    form1->lb2_2->hide();
    form1->lb5->hide();
    form1->lb4->setEnabled(false);
    form1->ln_num->clear();
    form1->ln_num->setEnabled(false);
    //Если результат предыдущего вычисления не сохранён - поля доступны для редактирования.
    if (!result_saved)
    {
        form1->ln_line1->setEnabled(true);
        form1->ln_column1->setEnabled(true);
    }

    if (item == "Умножение")
    {
        form1->lb5->show();
        form1->ln_line2->show();
        form1->ln_column2->show();
        form1->lb2_2->show();
    }
    else if (item == "Умножение на скалярное число")
    {
        form1->lb1->setText("Размер матрицы");
        form1->lb4->setEnabled(true);
        form1->ln_num->setEnabled(true);
    }
}

void Widget1::b_continueClicked()
{
    //Проверка на корректность введённых данных.
    if (form1->combo->currentIndex() > -1 && (form1->ln_line1->text().toInt() && form1->ln_column1->text().toInt()))
    {
        if (form1->combo->currentText() == "Умножение на скалярное число")
        {
            if (!form1->ln_num->text().toInt())
            {
                QMessageBox::warning(this, "Matrix", "Проверьте корректность заполнения всех полей и повторите попытку.", QMessageBox::Ok);
                return;
            }
        }
        else if (form1->combo->currentText() == "Умножение")
        {
            //Проверка на корректность введённых данных.
            if (!(form1->ln_line2->text().toInt() && form1->ln_column2->text().toInt()))
            {
                QMessageBox::warning(this, "Matrix", "Проверьте корректность заполнения всех полей и повторите попытку.", QMessageBox::Ok);
                return;
            }
            if (form1->ln_column1->text().toInt() != form1->ln_line2->text().toInt())
            {
                QMessageBox::critical(this, "Matrix", "Количество столбцов первой матрицы должно совпадать с количеством строк второй.", QMessageBox::Ok);
                return;
            }
        }
        widget2 = new Widget2(form1, this);
        widget2->show();
        return;
    }
    QMessageBox::warning(this, "Matrix", "Проверьте корректность заполнения всех полей и повторите попытку.", QMessageBox::Ok);
}

void Widget1::b_countClicked()
{
    widget3 = new Widget3(form1, this);
    widget3->show();
    widget2->close();
}

void Widget2::b_moveClicked()
{
    //Копирует значения из первой матрицы во вторую.
    form2->moveItems();
}

void Widget1::b_exitClicked()
{
    widget3->close();
}
