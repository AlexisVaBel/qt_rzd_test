#include "GameBoard.h"
#include <algorithm>
#include <random>
using namespace model;

GameBoard::GameBoard(const size_t dimension, QObject* parent)
	: _boardDimension(dimension)
	, _boardSize(dimension * dimension)
	, Super{parent} {
	_rawBoard.resize(_boardSize);
	std::iota(_rawBoard.begin(), _rawBoard.end(), 1);
	_shuffle();
}

void GameBoard::_shuffle() {
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 generator(seed);

	//something validating
	std::shuffle(_rawBoard.begin(), _rawBoard.end(), generator);
}

int GameBoard::rowCount(const QModelIndex& /*parent*/) const {
	return static_cast<int>(_boardSize);
}

QVariant GameBoard::data(const QModelIndex& index, int role) const {
	if (!index.isValid() || index.row() >= _boardSize || role != Qt::DisplayRole) {
		return {};
	}
	const int rowIndex{static_cast<int>(index.row())};
	return QVariant::fromValue(_rawBoard.at(rowIndex).value);
}

namespace {
bool is_adjacent(GameBoard::Position first, GameBoard::Position second) {
	if (first == second) {
		return false;
	}

	const auto calc_distance = [](size_t pos1, size_t pos2) {
		int distance = static_cast<int>(pos1);
		distance -= static_cast<int>(pos2);
		distance = std::abs(distance);
		return distance;
	};

	bool result{false};

	if (first.row == second.row) {
		int distance = calc_distance(first.column, second.column);
		if (distance == 1) {
			result = true;
		}
	} else if (first.column == second.column) {
		int distance = calc_distance(first.row, second.row);
		if (distance == 1) {
			result = true;
		}
	}

	return result;
}
} // namespace

bool GameBoard::move(int index) {
	if (index >= static_cast<int>(_boardSize)) {
		return false;
	}
	auto position = getRowCol(index);
	auto hiddenElementIterator = std::find(_rawBoard.begin(), _rawBoard.end(), _boardSize);

	Q_ASSERT(hiddenElementIterator != _rawBoard.end());
	Position hiddenElementPosition{getRowCol(std::distance(_rawBoard.begin(), hiddenElementIterator))};

	if (!is_adjacent(position, hiddenElementPosition)) {
		return false;
	}

	std::swap(hiddenElementIterator->value, _rawBoard[index].value);
	emit dataChanged(createIndex(0, 0), createIndex(_boardSize, 0));

	return true;
}

GameBoard::Position GameBoard::getRowCol(size_t index) const {
	size_t row = index / _boardDimension;
	size_t col = index % scBoardDimension;
	return {row, col};
}

bool GameBoard::_isBoardValid() {
	int inv{0};
	for (size_t i{0}; i < _boardSize; ++i) {
		for (size_t j = i; j < _boardSize; ++j) {
			if (_rawBoard[j].value < _rawBoard[i].value && _rawBoard[i].value != _boardSize) {
				++inv;
			}
		}
	}
	const size_t start_point = 1;

	for (size_t i = 0; i < _boardSize; ++i) {
		if (_rawBoard[i].value == _boardSize) {
			inv += start_point + i / _boardDimension;
		}
	}

	return (inv % 2) == 0;
}
