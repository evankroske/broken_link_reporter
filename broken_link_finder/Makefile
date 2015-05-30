build/broken_link_finder: src/broken_link_finder.cc
	mkdir -p build
	c++ -std=c++14 -lcurl -o build/broken_link_finder src/broken_link_finder.cc

run: build/broken_link_finder
	./build/broken_link_finder
