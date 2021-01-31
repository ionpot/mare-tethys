.PHONY: build
build:
	cmake --build build

.PHONY: clean
clean:
	rm -rf build

.PHONY: init
init:
	cmake -S . -B build

.PHONY: run
run:
	cd build/tethys && ./tethys
