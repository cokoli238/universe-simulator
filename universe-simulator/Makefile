all: main boost

main: solar_system_class.o solar_system_main.o 
	g++ -g solar_system_class.o solar_system_main.o -o Universe -L /usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

boost: solar_system_class.o solar_system_test.o 
	g++ -g solar_system_class.o solar_system_test.o -o UniverseTest -L /usr/local/lib -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system 

solar_system_class.o: solar_system_class.cpp
	g++ -g  -c solar_system_class.cpp -o solar_system_class.o -I /usr/local/include

solar_system_main.o: solar_system_main.cpp
	g++ -g -c solar_system_main.cpp -o solar_system_main.o -I /usr/local/include

solar_system_test.o: solar_system_test.cpp 
		g++ -g  -c solar_system_test.cpp -o solar_system_test.o -I /usr/local/include

clean:
	rm -rf *.o *~ Universe