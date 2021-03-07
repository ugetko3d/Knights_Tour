#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_Knights_Tour.h"

#include <Windows.h>

class Knights_Tour : public QMainWindow
{
    Q_OBJECT

public:
    Knights_Tour(QWidget *parent = Q_NULLPTR);
    ~Knights_Tour();

private:
    Ui::Knights_TourClass ui;

    QMessageBox* messageBox;

    bool validMove(int row, int col);
    bool solveWarnsdorff(int row, int col, int move);

    int xMoves[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
    int yMoves[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

    const int MAX = 1600;
    const int FREE = 0;

    int board[40][40];

    bool running = false;

private slots:
    void onCellClicked(int row, int col);
    void onButtonResetClicked();
};
