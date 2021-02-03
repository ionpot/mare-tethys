#ifndef TETHYS_MACROS_HPP
#define TETHYS_MACROS_HPP

// use default move-constructor and move-assignment
#define TETHYS_DEFAULT_MOVE(T)\
	T(T&&) = default;\
	T& operator=(T&&) = default;

// disable copy-constructor and copy-assignment
#define TETHYS_NO_COPY(T)\
	T(const T&) = delete;\
	T& operator=(const T&) = delete;

#endif
