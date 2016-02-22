CXX=g++
FILES_WPS=main_wps.cpp TarjetaRed.cpp AccessPoint.cpp ConsoleGUI.cpp
FILES_INJECT=main_inject.cpp Injection.cpp
CXX_OPTIONS=-std=gnu++11 #-std=c++0x
LIBS=-lpcap -lncurses -lnet
EXECUTABLE=wpscan
EXECUTABLE_INJECT=wpsinject

wps:
	$(CXX) $(FILES_WPS) $(CXX_OPTIONS) $(LIBS) -o $(EXECUTABLE)

inject:
	$(CXX) $(FILES_INJECT) $(CXX_OPTIONS) $(LIBS) -o $(EXECUTABLE_INJECT)

all:
	$(CXX) $(FILES_WPS) $(CXX_OPTIONS) $(LIBS) -o $(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE) $(EXECUTABLE_INJECT)
