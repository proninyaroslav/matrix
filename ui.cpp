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

#include "ui.h"
#include "matrix.h"

void UI::GUI::setForm1(QWidget *Widget)
{
    lb1 = new QLabel(Widget);
    lb1->setGeometry(QRect(20, 90, 111, 16));
    lb1->setText("Размер матриц");
    lb1->setEnabled(false);
    lb2_1 = new QLabel(Widget);
    lb2_1->setGeometry(QRect(71, 110, 16, 16));
    lb2_1->setText("x");
    lb2_1->setEnabled(false);
    lb3 = new QLabel(Widget);
    lb3->setGeometry(QRect(20, 30, 71, 16));
    lb3->setText("Операция");
    lb4 = new QLabel(Widget);
    lb4->setGeometry(QRect(20, 160, 131, 16));
    lb4->setText("Скалярное число:");
    lb4->setEnabled(false);
    lb5 = new QLabel(Widget);
    lb5->setGeometry(QRect(138, 118, 16, 16));
    lb5->setText(",");
    lb5->hide();
    lb2_2 = new QLabel(Widget);
    lb2_2->setGeometry(QRect(201, 110, 16, 16));
    lb2_2->setText("x");
    lb2_2->hide();

    combo = new QComboBox(Widget);
    combo->setGeometry(QRect(20, 50, 111, 26));
    combo_lst << "Сложение" << "Вычитание" << "Умножение" << "Умножение на скалярное число";
    combo->addItems(combo_lst);
    //По умолчанию не выбран ни один элемент из списка.
    combo->setCurrentIndex(-1);

    b_continue = new QPushButton(Widget);
    b_continue->setGeometry(QRect(200, 210, 114, 32));
    b_continue->setText("Далее");
    b_cancel = new QPushButton(Widget);
    b_cancel->setGeometry(QRect(20, 210, 114, 32));
    b_cancel->setText("Отмена");

    //ввод значения строк и стобцов для первой и второй матрицы.
    ln_line1 = new QLineEdit(Widget);
    ln_line1->setGeometry(QRect(20, 110, 39, 21));
    ln_line1->setEnabled(false);
    ln_column1 = new QLineEdit(Widget);
    ln_column1->setGeometry(QRect(90, 110, 39, 21));
    ln_column1->setEnabled(false);
    // ln_num - поле ввода для скалярного числа.
    ln_num = new QLineEdit(Widget);
    ln_num->setGeometry(QRect(140, 159, 51, 21));
    ln_num->setEnabled(false);
    ln_line2 = new QLineEdit(Widget);
    ln_line2->setGeometry(QRect(150, 110, 39, 21));
    ln_line2->hide();
    ln_column2 = new QLineEdit(Widget);
    ln_column2->setGeometry(QRect(220, 110, 39, 21));
    ln_column2->hide();

    QWidget::setTabOrder(combo, ln_line1);
    QWidget::setTabOrder(ln_line1, ln_column1);
    QWidget::setTabOrder(ln_column1, ln_num);
    QWidget::setTabOrder(ln_num, ln_line2);
    QWidget::setTabOrder(ln_line2, ln_column2);
    QWidget::setTabOrder(ln_column2, b_continue);
    QWidget::setTabOrder(b_continue, b_cancel);

    QObject::connect(b_cancel, SIGNAL(clicked()), Widget, SLOT(close()));
    QObject::connect(combo, SIGNAL(activated(QString)), Widget, SLOT(comboSelectItem(QString)));
    QObject::connect(b_continue, SIGNAL(clicked()), Widget, SLOT(b_continueClicked()));

    Widget->setWindowTitle("Matrix");
    Widget->resize(331, 262);
    //Фиксированный размер окна.
    Widget->setMinimumSize(QSize(331, 262));
    Widget->setMaximumSize(QSize(331, 262));
}

void UI::GUI::setForm2(QWidget *Widget, Widget1 *widget1)
{
    //Извлечение данных из QLineEdit.
    l1 = ln_line1->text().toInt();
    c1 = ln_column1->text().toInt();

    table1 = new QTableWidget(Widget);
    table1->setRowCount(l1);
    table1->setColumnCount(c1);
    table1->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
    table1->horizontalHeader()->setDefaultSectionSize(40);
    table1->verticalHeader()->setDefaultSectionSize(40);
    //Скрывает шапки строк и столбцов.
    table1->verticalHeader()->setVisible(false);
    table1->horizontalHeader()->setVisible(false);
    //Попытка извлечь сохранённый результат вычислений.
    if (widget1->result_saved)
    {
        if (!fromFile(&l1, &c1))
            QMessageBox::critical(widget1, "Matrix", "Не удалось извлечь сохранённые данные.", QMessageBox::Ok);
    }
    else
        //Если не было сохранённого результата, заполняет таблицу нулями
        setNull(table1, &l1, &c1);

    h_layout1 = new QHBoxLayout();
    h_layout1->addWidget(table1);

    if (combo->currentText() != "Умножение на скалярное число")
    {
        //Кнопка для копирования значений из первой таблицы во вторую.
        b_move = new QPushButton(Widget);
        b_move->setMaximumSize(QSize(30, 25));
        QIcon move_icon;
        move_icon.addFile(QStringLiteral(":/res/Back_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        b_move->setIcon(move_icon);
        h_layout1->addWidget(b_move);
    }


    if (combo->currentText() == "Сложение" || combo->currentText() == "Вычитание")
    {
        table2 = new QTableWidget;
        table2->setRowCount(l1);
        table2->setColumnCount(c1);
        table2->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        table2->horizontalHeader()->setDefaultSectionSize(40);
        table2->verticalHeader()->setDefaultSectionSize(40);
        table2->verticalHeader()->setVisible(false);
        table2->horizontalHeader()->setVisible(false);
        setNull(table2, &l1, &c1);

        h_layout1->addWidget(table2);
        h_layout1->setSpacing(20);
    }
    else if(combo->currentText() == "Умножение")
    {
        l2 = ln_line2->text().toInt();
        c2 = ln_column2->text().toInt();

        table2 = new QTableWidget(Widget);
        table2->setRowCount(l2);
        table2->setColumnCount(c2);
        table2->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        table2->horizontalHeader()->setDefaultSectionSize(40);
        table2->verticalHeader()->setDefaultSectionSize(40);
        table2->verticalHeader()->setVisible(false);
        table2->horizontalHeader()->setVisible(false);
        setNull(table2, &l2, &c2);

        /*Делает кнопку копирования значений активной только тогда,
        когда строки или столбцы матриц равны.*/
        if (table1->rowCount() != table2->rowCount() || table1->columnCount() != table2->columnCount())
            b_move->setEnabled(false);

        h_layout1->addWidget(table2);
        h_layout1->setSpacing(20);
    }
    b_count = new QPushButton(Widget);
    b_count->setText("Посчитать");
    b_count->setMaximumSize(QSize(114, 32));
    h_layout2 = new QHBoxLayout;
    h_layout2->addWidget(b_count);
    v_layout1 = new QVBoxLayout(Widget);
    v_layout1->addLayout(h_layout1);
    v_layout1->addLayout(h_layout2);

    if (combo->currentText() != "Умножение на скалярное число")
    {
        QObject::connect(b_move, SIGNAL(clicked()), Widget, SLOT(b_moveClicked()));
    }
    QObject::connect(b_count, SIGNAL(clicked()), widget1, SLOT(b_countClicked()));

    if (combo->currentText() == "Умножение на скалярное число")
        Widget->resize(550, 500);
    else
        Widget->resize(1000, 500);

    Widget->setLayout(v_layout1);
    Widget->setWindowTitle("Matrix");

}

void UI::GUI::setForm3(QWidget *Widget, Widget1 *widget1, Matrix *matrix)
{
    matrix->toArray(table1, &l1, &c1, FIRST_ARRAY);
    if (combo->currentText() == "Сложение" || combo->currentText() == "Вычитание")
    {
        matrix->toArray(table2, &l1, &c1, SECOND_ARRAY);
        if (combo->currentText() == "Сложение")
            matrix->add(&l1, &c1);
        else
            matrix->subtract(&l1, &c1);
    }
    else if (combo->currentText() == "Умножение")
    {
        matrix->toArray(table2, &l2, &c2, SECOND_ARRAY);
        matrix->multiply(&l1, &c1, &l2, &c2);
    }
    else if (combo->currentText() == "Умножение на скалярное число")
        matrix->multiplyToScalar(&l1, &c1, ln_num->text().toInt());

    table3 = new QTableWidget(Widget);
    if (combo->currentText() != "Умножение")
    {
        table3->setRowCount(l1);
        table3->setColumnCount(c1);
    }
    else
    {
        table3->setRowCount(l1);
        table3->setColumnCount(c2);
    }
    table3->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
    table3->horizontalHeader()->setDefaultSectionSize(40);
    table3->verticalHeader()->setDefaultSectionSize(40);
    table3->verticalHeader()->setVisible(false);
    table3->horizontalHeader()->setVisible(false);
    //Копирование результата в таблицу.
    if (combo->currentText() != "Умножение")
        matrix->toTable(table3, &l1, &c1);
    else
        matrix->toTable(table3, &l1, &c2);

    h_layout3 = new QHBoxLayout();
    h_layout3->addWidget(table3);
    h_layout3->setSpacing(20);

    b_exit = new QPushButton(Widget);
    b_exit->setText("Выход");
    b_exit->setMaximumSize(QSize(114, 32));

    lb6 = new QLabel(Widget);
    lb6->setText("Сохранить результат для следующего вычисления");

    chbx_save = new QCheckBox(Widget);

    h_layout4 = new QHBoxLayout();
    h_layout4->addWidget(chbx_save);
    h_layout4->addWidget(lb6);
    h_layout4->addWidget(b_exit);
    h_layout4->setSpacing(20);
    v_layout2 = new QVBoxLayout(Widget);
    v_layout2->addLayout(h_layout3);
    v_layout2->addLayout(h_layout4);

    QObject::connect(b_exit, SIGNAL(clicked()), widget1, SLOT(b_exitClicked()));

    Widget->resize(500, 500);
    Widget->setLayout(v_layout2);
    Widget->setWindowTitle("Matrix");
}

void UI::GUI::moveItems()
{
    QTableWidgetItem *data;
    for (int i = 0; i < l1; i++)
        for (int j = 0; j < c1; j++)
        {
            data = new QTableWidgetItem(table1->item(i, j)->text());
            table2->setItem(i, j, data);
        }
}

void UI::GUI::setNull(QTableWidget *table, const int *row, const int *column)
{
    QTableWidgetItem *null;
    for (int i = 0; i < *row; i++)
        for (int j = 0; j < *column; j++)
        {
            null = new QTableWidgetItem(QString("0"));
            table->setItem(i, j, null);
        }
}

bool UI::GUI::fromFile(const int *row, const int *column)
{
    QFile file("result.dat");
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    else
    {
        QTableWidgetItem *null;
        while (!file.atEnd())
            for (int i = 0; i < *row; i++)
                for (int j = 0; j < *column; j++)
                {
                    char c;
                    //Посимвольно считывает строку.
                    file.getChar(&c);
                    //Пропускает пробелы.
                    if(c == ' ')
                    {
                        file.getChar(&c);
                    }
                        null = new QTableWidgetItem(QString(c));
                        table1->setItem(i, j, null);
                }
        file.close();
        return true;
    }
}
