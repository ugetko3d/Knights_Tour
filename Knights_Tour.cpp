#include "Knights_Tour.h"

Knights_Tour::Knights_Tour(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	messageBox = new QMessageBox;

    onButtonResetClicked();

	connect(ui.tbl_grid, &QTableWidget::cellClicked, this, &Knights_Tour::onCellClicked);
	connect(ui.btn_reset, &QPushButton::released, this, &Knights_Tour::onButtonResetClicked);
}

Knights_Tour::~Knights_Tour()
{
	delete messageBox;
}

bool Knights_Tour::validMove(int row, int col)
{
	if (row >= 0 && row < n && col >= 0 && col < n)
		return board[row][col] == FREE;
	return false;
}

bool Knights_Tour::solveWarnsdorff(int row, int col, int move)
{
	if (move == MAX)
		return true;

	int min_deg = 9;
	int min_deg_idx = -1;
	int nx, ny, mx, my, counter;

	for (int i = 0; i < 8; i++)
	{
		nx = row + xMoves[i];
		ny = col + yMoves[i];

		if (validMove(nx, ny))
		{
			counter = 0;
			for (int j = 0; j < 8; j++)
			{
				int mx = nx + xMoves[j];
				int my = ny + yMoves[j];
				if (validMove(mx, my))
					counter++;
			}
			if (counter < min_deg && counter > 0)
			{
				min_deg = counter;
				min_deg_idx = i;
			}
		}
	}

	if (min_deg_idx == -1)
		return false;

	nx = xMoves[min_deg_idx];
	ny = yMoves[min_deg_idx];

	board[row + nx][col + ny] = move;

	ui.tbl_grid->item(row + nx, col + ny)->setBackground(Qt::blue);
	ui.tbl_grid->repaint();
	Sleep(500);

	ui.tbl_grid->item(row + nx, col + ny)->setBackground(Qt::green);
	ui.tbl_grid->repaint();

	if (solveWarnsdorff(row + nx, col + ny, (move + 1)))
		return true;
	else
	{
		board[row + nx][col + ny] = FREE;
		ui.tbl_grid->item(row + nx, col + ny)->setBackground(Qt::white);
		ui.tbl_grid->repaint();
	}

}

void Knights_Tour::onButtonResetClicked()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 0;
            if (!ui.tbl_grid->item(i, j))
                ui.tbl_grid->setItem(i, j, new QTableWidgetItem);
            ui.tbl_grid->item(i, j)->setBackground(Qt::white);
        }
    }
	ui.tbl_grid->repaint();
}

void Knights_Tour::onCellClicked(int row, int col)
{
	if (running)
		return;

	running = true;

	board[row][col] = 1;
	ui.tbl_grid->item(row, col)->setBackground(Qt::green);
	ui.tbl_grid->item(row, col)->setSelected(false);
	ui.tbl_grid->repaint();

	if (solveWarnsdorff(row, col, 2))
	{
		messageBox->setText("We found a solution!");
		messageBox->show();
	}
	else
	{
		messageBox->setText("We found no solution...");
		messageBox->show();
	}

	onButtonResetClicked();

	running = false;
	
}
