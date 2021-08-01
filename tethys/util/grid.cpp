#include "grid.hpp"

#include "int.hpp"

#include <algorithm>
#include <string>

namespace tethys::util {
	// grid index
	void
	GridIndex::assert_valid() const
	{
		TETHYS_INT_NATURAL(row);
		TETHYS_INT_NATURAL(column);
	}

	GridIndex
	GridIndex::operator+(const GridIndex& i) const
	{
		return {row + i.row, column + i.column};
	}

	GridIndex
	GridIndex::min(GridIndex a, GridIndex b)
	{
		return {
			std::min(a.row, b.row),
			std::min(a.column, b.column)
		};
	}

	// grid size
	void
	GridSize::assert_valid() const
	{
		TETHYS_INT_POSITIVE(rows);
		TETHYS_INT_POSITIVE(columns);
	}

	void
	GridSize::assert_valid(GridSize size) const
	{
		size.assert_valid();
		TETHYS_INT_WITHIN(size.rows, rows);
		TETHYS_INT_WITHIN(size.columns, columns);
	}

	void
	GridSize::assert_valid(GridIndex i) const
	{
		TETHYS_INT_INDEX(i.row, rows);
		TETHYS_INT_INDEX(i.column, columns);
	}

	GridIndex
	GridSize::clamp(GridIndex i) const
	{
		return GridIndex::min(to_index(), i);
	}

	GridSize
	GridSize::clamp(GridSize size) const
	{
		if (rows < size.rows)
			size.rows = rows;
		if (columns < size.columns)
			size.columns = columns;
		return size;
	}

	GridIndex
	GridSize::to_index() const
	{
		return {rows - 1, columns - 1};
	}

	int
	GridSize::total_cells() const
	{
		return rows * columns;
	}

	std::string
	GridSize::to_str() const
	{
		return std::to_string(rows) + " rows, "
			+ std::to_string(columns) + " columns";
	}

	// grid iterator
	GridIterator::GridIterator(
			GridIndex start,
			GridIndex end):
		m_index {start},
		m_column_offset {start.column},
		m_end {end}
	{}

	bool
	GridIterator::at_new_row() const
	{
		return m_index.column == m_column_offset;
	}

	bool
	GridIterator::valid() const
	{
		return m_index.row <= m_end.row;
	}

	GridIndex
	GridIterator::index() const
	{
		return m_index;
	}

	void
	GridIterator::next()
	{
		if (m_index.column < m_end.column)
			++m_index.column;
		else
			next_row();
	}

	void
	GridIterator::next_row()
	{
		m_index.column = m_column_offset;
		++m_index.row;
	}
}
