#MAKEFILE FOR OS PROJECT
#Authored by Joseph Walewski & Clayton Carter
#TO RUN, type "make" while in the SRC directory

.PHONY: default
CFLAGS = -g -Wall -Wextra -pedantic -Werror -target x86_64-apple-darwin20.3.0

default: clean
	g++ *.cpp *.h -Wall -std=c++17 -stdlib=libc++ && ./a.out

clean:
	rm -f ./*.out ./*.exe