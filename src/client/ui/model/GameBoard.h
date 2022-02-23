#pragma once
#include <QAbstractListModel>

#include <QSize>
#include <vector>

namespace model {
namespace {
	constexpr size_t scBoardDimension = 4;
}
class GameBoard : public QAbstractListModel {
	Q_OBJECT
	using Self = GameBoard;
	using Super = QAbstractListModel;

	Q_PROPERTY(int dimension READ dimension CONSTANT)
	Q_PROPERTY(int hiddenElementValue READ hiddenElementValue CONSTANT)

public:
	explicit GameBoard(const size_t dimension = scBoardDimension, QObject* parent = nullptr);

	struct Tile {
		size_t value{};
		Tile& operator=(const size_t newValue) {
			value = newValue;
			return *this;
		}
		bool operator==(const size_t other) {
			return other == value;
		}
	};

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	int dimension() const {
		return static_cast<int>(_boardDimension);
	}
	int hiddenElementValue() const {
		return static_cast<int>(_boardSize);
	}

	Q_INVOKABLE bool move(int index);
	struct Positions {
		size_t row;
		size_t column;
		bool operator==(const Positions other) {
			return (row == other.row && column == other.column);
		}
	};

	using Position = Positions;

	Position getRowCol(size_t index) const;

private:
	void _shuffle();
	bool _isBoardValid();

	std::vector<Tile> _rawBoard;
	const size_t _boardDimension;
	const size_t _boardSize;
};
} // namespace model
