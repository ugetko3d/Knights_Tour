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

    static constexpr int n = 8;
    const int MAX = n * n;
    const int FREE = 0;

    int board[n][n];

    bool running = false;

private slots:
    void onCellClicked(int row, int col);
    void onButtonResetClicked();
};
