build:
	ino build

test:
	mkdir -p .build
	g++ -o .build/run_all spec/run_all.cpp -lcppunit
	./.build/run_all

clean:
	rm -f .build/run_all
	ino clean

upload: build
	./upload.sh

all: build test upload
