
# executable
all: LivestockTracker


LivestockTracker: Livestock.o Chicken.o Cow.o Goat.o Horse.o ReportPrinter.o HerdManager.o
	g++ Livestock.o Chicken.o Cow.o Goat.o Horse.o ReportPrinter.o HerdManager.o -o LivestockTracker

# Object makers
#Herdmanager
HerdManager.o: HerdManager.cpp Livestock.h Chicken.h Cow.h Goat.h Horse.h ReportPrinter.h
	g++ -c HerdManager.cpp

#Printer
ReportPrinter.o: ReportPrinter.cpp ReportPrinter.h Livestock.h Chicken.h Cow.h Goat.h Horse.h
	g++ -c ReportPrinter.cpp

#horse
Horse.o: Horse.cpp Horse.h Livestock.h
	g++ -c Horse.cpp

#goat
Goat.o: Goat.cpp Goat.h Livestock.h
	g++ -c Goat.cpp

#cow
Cow.o: Cow.cpp Cow.h Livestock.h
	g++ -c Cow.cpp

#chicken
Chicken.o: Chicken.cpp Chicken.h Livestock.h 
	g++ -c Chicken.cpp

#Livestock
Livestock.o: Livestock.cpp Livestock.h
	g++ -c Livestock.cpp

#clean function
clean:
	rm *.o LivestockTracker
