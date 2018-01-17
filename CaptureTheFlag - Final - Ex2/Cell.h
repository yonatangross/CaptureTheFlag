#pragma once


class Cell
{
	unsigned row;
	unsigned col;
	int x;
	int y;
	char ch;
public:

	// CTOR/DTOR
	explicit Cell(unsigned row = 0, unsigned col = 0, char ch = ' ', int x = 0, int y = 0) :
		row(row),
		col(col),
		x(x), y(y),
		ch(ch)
	{
	}
	Cell(const Cell& other) : row(other.row),
		col(other.col),
		x(other.x),
		y(other.y),
		ch(other.ch)
	{
	}
	Cell& operator=(const Cell& other)
	{
		if (this == &other)
			return *this;
		row = other.row;
		col = other.col;
		x = other.x;
		y = other.y;
		ch = other.ch;
		return *this;
	}

	// Printing
	void draw(char ch) const;
	void draw() const;

	// Getters / Setters
	int getRow() const { return row; }
	void setRow(int row) { this->row = row; }
	int getCol() const { return col; }
	void setCol(int col) { this->col = col; }
	char getColChar() { return this->col -1 + 'A'; }
	char getCh() const { return ch; }
	void setCh(char ch) { this->ch = ch; }
	int getX() const { return x; }
	void setX(int x) { this->x = x; }
	int getY() const { return y; }
	void setY(int y) { this->y = y; }


	bool isUnIntilizedCell (){ return col == 0 && row == 0; }
};

