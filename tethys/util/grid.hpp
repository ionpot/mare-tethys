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

	class GridSection {
	public:
		GridSection(GridIndex start, GridIndex end);
		GridSection(GridSize, GridIndex start = {});
		void assert_valid(const GridSize& bounds) const;
		GridSection clamp(const GridSize&) const;
		GridIndex start() const;
		GridIndex end() const;
	private:
		GridIndex m_start;
		GridIndex m_end;
	};

	class GridIterator {
	public:
		GridIterator(GridIndex start, GridIndex end);
		GridIterator(const GridSection&);
		GridIterator(const GridSize&);
		bool at_new_row() const;
		bool valid() const;
		GridIndex index() const;
		void next();
		void next_row();
	private:
		GridIndex m_index;
		int m_column_offset;
		GridIndex m_end;
	};

	template<class T>
	class Grid {
	public:
		Grid(GridSize s):
			m_size {s},
			m_cells {
				std::make_unique<T[]>(s.total_cells())
			}
		{}

		GridIterator begin() const
		{ return {m_size}; }

		GridIterator begin(const GridSection& section) const
		{
			section.assert_valid(m_size);
			return {section};
		}

		T cell(GridIndex i) const
		{ return m_cells[cell_of(i)]; }

		T cell(const GridIterator& iter) const
		{ return cell(iter.index()); }

		void cell(GridIndex i, T v)
		{ m_cells[cell_of(i)] = v; }

		GridSize size() const
		{ return m_size; }

	private:
		GridSize m_size;
		std::unique_ptr<T[]> m_cells;

		int cell_of(GridIndex i) const
		{ return i.row * m_size.columns + i.column; }
	};
}
