#MAKEFILE FOR OS PROJECT
#TO RUN, USE type "make mac" or "make windows", and if you want to get rid of old compiled files run "make clean"

mac:
    g++ *.cpp *.h -Wall && ./a.out
windows:
    g++ *.cpp *.h -Wall && ./a.exe

clean:
    rm -f ./*.out ./*.exe