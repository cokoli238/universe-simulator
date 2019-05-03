
/**@copyright 2016
 * @file solar_system_class.hpp
 * @author Christian Okoli
 * @date 5/04/2016
 * @version  
 * @brief test file for Solar System class
 * @section This program test the coordinates
   translations, velocity calculations, step function   
 *
 */

#include "solar_system_class.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing
#define GRAVITY_VAL 6.67e-11
#define WIN_SIZE 1000
#include <boost/test/unit_test.hpp>
#include <iostream>



BOOST_AUTO_TEST_CASE(Translate_Coords) {
SolarSystem::Body planet1;
planet1.setLocation(sf::Vector2f(0, 0));
planet1.setVelocity(sf::Vector2f(2, 2));
sf::Vector2f coordinates(1.4960e+11, 0.0000e+00);
double half_win_size = (WIN_SIZE / 2);
sf::Vector2f converted_coors(((half_win_size) +
  ((1.4960e+11) / (2.50e+11) * half_win_size) ),
  (((half_win_size) - ((0.0000e+00)/ (2.50e+11) * (half_win_size) ))));
planet1.setLocation(coordinates);
planet1.setRadius(2.50e+11);
planet1.setLocation(planet1.convert_cordinates());

BOOST_CHECK(converted_coors  == planet1.getLocation());
}

BOOST_AUTO_TEST_CASE(Velocity) {
SolarSystem::Body planet1, planet2;
planet1.setLocation(sf::Vector2f(0, 0));
planet1.setVelocity(sf::Vector2f(2, 2));
planet1.setMass(100);
planet2.setLocation(sf::Vector2f(0, 0));
planet2.setVelocity(sf::Vector2f(2, 2));
planet2.setMass(100);
double seconds = 100;
sf::Vector2f old_velocity = planet1.getVelocity();
sf::Vector2f new_velocity;
new_velocity.x = old_velocity.x + seconds * (planet1.getAcceleration()).x;
new_velocity.y = old_velocity.y +  seconds * (planet1.getAcceleration()).y;
planet2.step(seconds);
BOOST_CHECK(planet2.getVelocity() == new_velocity);
}

BOOST_AUTO_TEST_CASE(Step_Function) {
SolarSystem::Body planet1, planet2;
planet1.setLocation(sf::Vector2f(0, 0));
planet1.setVelocity(sf::Vector2f(2, 2));
planet1.setMass(100);
planet2.setLocation(sf::Vector2f(0, 0));
planet2.setVelocity(sf::Vector2f(2, 2));
planet2.setMass(100);
double newPosX = (planet1.getLocation()).x + 100*(planet1.getVelocity()).x;
double newPosY = (planet1.getLocation()).y + 100*(planet1.getVelocity()).y;
planet2.setLocation(sf::Vector2f(newPosX, newPosY));
planet1.step(100);
BOOST_CHECK(planet1.getLocation() == planet2.getLocation());
}
