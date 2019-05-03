/*
@copyright
*/
#include "solar_system_class.hpp"

#include <iostream>

#define WINDOW_SIZE 1000


int main(int argc, char* argv[]) {
    srand((unsigned)time(0));
    if (argc < 3) {
        std::cout << "Nbody [Generation-Time] [step-position]" << std::endl;
    }

    double generate_length = atoi(argv[1]);
    int generate_step = atoi(argv[2]);
    int planets;
    double universe_radius;

    std::cin >> planets;
    std::cin >> universe_radius;

    SolarSystem::Universe u(planets, WINDOW_SIZE, universe_radius,
        generate_length, generate_step);
    u.input_data(std::cin);
    u.generate();
    u.output_data();

    return 0;
}
