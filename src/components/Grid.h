#pragma once

template <typename Cell>
class Grid {
public:
	Grid(int width, int height) : width_(width), height_(height) {
		cells_ = new Cell[height * width];
	}
	~Grid() {
		delete[] cells_;
	}

	bool isIndexValid(int x, int y) const {
		return !((x < 0 || x >= width_) || (y < 0 || y >= height_));
	}
	
	Cell getCell(int x, int y) {
		if (!isIndexValid(x, y)) return Cell();
		return cells_[x + y * width_];
	}

	void setCell(Cell value, int x, int y) {
		if (!isIndexValid(x, y)) return;
		cells_[x + y * width_] = value;
	}
private:
	Cell* cells_;
	int width_, height_;
};

