#pragma once

#include <memory>
#include <string>

namespace tethys::util {
	struct GridIndex {
		int row;
		int column;
		void assert_valid() const;
		GridIndex operator+(const GridIndex&) const;
		static GridIndex min(GridIndex, GridIndex);
	};

	struct GridSize {
		int rows;
		int columns;
		void assert_valid() const;
		void assert_valid(GridIndex) const;
		void assert_valid(GridSize) const;
		GridIndex clamp(GridIndex) const;
		GridSize clamp(GridSize) const;
		GridIndex to_index() const;
		int total_cells() const;
		std::string to_str() const;
	};

	class GridIterator {
	public:
		GridIterator(GridIndex start, GridIndex end);
		bool valid() const;
		GridIndex index() const;
		void next();
	private:
		GridIndex m_index;
		const int m_column_offset;
		const GridIndex m_end;
	};

	template<class T>
	class Grid {
	public:
		const GridSize size;

		Grid(GridSize s):
			size {s},
			 m_cells {
				 std::make_unique<T[]>(s.total_cells())
			 }
		{}

		GridIterator begin(GridIndex start, GridIndex end) const
		{
			size.assert_valid(start);
			size.assert_valid(end);
			return {start, end};
		}

		T cell(GridIndex i) const
		{ return m_cells[cell_of(i)]; }

		T cell(const GridIterator& iter) const
		{ return cell(iter.index()); }

		void cell(GridIndex i, T v)
		{ m_cells[cell_of(i)] = v; }

	private:
		std::unique_ptr<T[]> m_cells;

		int cell_of(GridIndex i) const
		{ return i.row * size.columns + i.column; }
	};
}