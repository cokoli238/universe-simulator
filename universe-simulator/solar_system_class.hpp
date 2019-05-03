/**
 * @copyright 2016
 * @file   solor_system_class.cpp
 * @Author Ethan Cumming(Star and Universe Class) & Christian Okoli(SpaceObject and Body Class)
 * @date   April 2016
 * @brief  Implimentation of Universe. Using SFML, Creates planets that orbit around sun object
 *       	and simulates gravitational forces
 */
#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H



#include <istream>
#include <ostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include "SFML/Graphics.hpp"

using std::string;
using std::ostream;
using std::istream;

/*
* @brief namespace for the project
*/
namespace SolarSystem {
/*
*@brief parent class for body and star class
*/
class SpaceObject: public sf::Drawable {
 public:
 	 /**
     * @brief Default  constructor for SpaceObject class
     * @param nothing.
     * @return nothing
     */
    SpaceObject();
	  /**
     * @brief  Retrieves velocity of SpaceObject .  
     * @param  nothing 
     * @return velocity_ 
     */
    sf::Vector2f getVelocity() const;
	 /**
     * @brief  sets velocity for SpaceObject  
     * @param  float vector v for coordinates   
     * @return nothing 
     */
    void setVelocity(sf::Vector2f v);
	  /**
     * @brief  Retrieves location of SpaceObject .  
     * @param  nothing 
     * @return location_ 
     */
    sf::Vector2f getLocation() const;
    /*
    @brief setter fucntion for the mass (used for unit test mainly)
    @param new mass
    */
    void setMass(double m);
    /*
    @brief setter for radius function
    @param new radius
    */
    void setRadius(double r);
     /*
    *@brief will draw a star shape
    *@param  virtua
    *@return void
    */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const; //NOLINT

 protected:
    sf::CircleShape circle_;  ///< circle shape object
    float radius_;  ///< radius of object
    sf::Vector2f location_;  ///< current position of space object
    sf::Vector2f velocity_;  ///< direction of space object
    double mass_;  ///< mass of space object
};
class Body: public SpaceObject {
 public:
 	/**
     * @brief Default Construtor for Body  
     * @param nothing  
     * @return nothing 
     */
    Body();
    /*
    *@brief getter for the sprite var
    *@return return sprite obj
    */
    sf::Sprite getSprite();
    /*
    *@brief Applies the image to the texture and the texture to the image
    *@return nothing
    */
    void fillBody();
	/**
     * @brief Moves body object for given amount of seconds
     * @param seconds the body object will move at its current velocity   
     * @return nothing 
     */
    void step(double seconds);
	/*
    *@brief converts cordinates before drawing the sprite planet
    *@param passes the window as reference
    *@return nothing
    */
    void draw(sf::RenderWindow & window); //NOLINT
     /**
     * @brief  sets location for SpaceObject  
     * @param   new coordinates as vector for Space object   
     * @return nothing 
     */
    void setLocation(sf::Vector2f l);
    /**
     * @brief overloaded extraction operator
     * @param input stream address, body object address
     * @return address of istream
     */
    friend istream & operator >> (istream & in, Body & body_obj);
	/**
     * @brief overloaded output operator
     * @param output stream address, body object address
     * @return output of ostream
     */
    friend ostream & operator << (ostream & out, Body & body_obj);
    /*
    *@brief compares two planets using there respective mass
    *@param left body object
    *@param right body object
    *@return bool
    */
    friend bool operator == (const Body& lhs, const Body& rhs);
    /*
    *@brief convert input cordinates to SFML cordinates: kind of like an offset
    *@return void
    */
    sf::Vector2f convert_cordinates();
    /*
    @brief computes the acceleration using the force and mass
    @return nothing
    */
    void update_acceleration();
    /*
    *@brief getter function for mass var
    *@return double
    */
    double getMass() const;
    /*
    *@brief setter for force
    *@param input vector
    *@return nothing
    */
    void setForce(sf::Vector2f f);
    /*
    *@brief getter function for force
    *@return the force var
    */
    sf::Vector2f getForce() const;
    /*
    *@brief setter function for acceleration
    *@param vector
    *@return nothing
    */
    void setAcceleration(sf::Vector2f a);
    /*
    *@brief getter for acceleration variable
    *@return vector
    */
    sf::Vector2f getAcceleration() const;
    /*
    *@brief handles the event of a body that can be controlled by keyboard input
    *@param referecne event type that hadles input from keyboard
    */
    void planetEvent(sf::Event & event); //NOLINT

 private:
    sf::Vector2f force_;  ///< planet force
    sf::Vector2f acceleration_;  ///< planet acceleration
    sf::Image image_;  ///< creates Image as a texture
    sf::Texture texture_;  ///< texture is placed on sprite
    sf::Sprite sprite_;  ///< sprite will be drawn on the screen.
    std::string body_name;  ///< name of planet
};
/*
*@brief class creates star object for background in Universe
*/
class Star: public SpaceObject {
 public:
    /*
    *@brief default constructor
    */
    Star();
 	/*
 	*@brief explicit constructor that inits the stars radius randomly
    *@param radius
 	*/
    explicit Star(float r);
    /*
    *@brief draws the circleshape object of the class
    *@param passes the window as reference
    */
    void draw(sf::RenderWindow & window); //NOLINT
 private:
    float radius_;  ///< radius of space object
    sf::CircleShape circle_;  ///< circle shape object
};
/*
*@brief base class for program. 
*/
class Universe {
 public:
 	/*
	*@brief default constructor
	*/
    Universe();
 	/*
	*@brief constrcutor that takes input for initializing body vector.
	*@param number of panets, screen_size, radius of universe, simulation length,
    * and seconds for step
	*/
    Universe(int num_of_planets, int screen_size, double radius_of_universe,
        double time_limit, double time_step);
    /*
    @brief contains program loop for simulations
    */
    void generate();
	/*
	*@brief takes input from file and creates object based data 
	*@param instream to read in file
	*/
    void input_data(std::istream & stream);  //NOLINT
    /*
	*@brief will print out information of planet using there overloaded extraction operator
	*@param N/A
	*@return void
	*/
    void output_data();
    /*
    @brief getter function for the planet vector
    @return vector of planets
    */
    std::vector<Body> get_planet_vector();
    /*
    *@brief getter for screen size
    *@return int
    */
    int get_screen_size() const;
    /*
    *@brief getter for the universe radius
    *@return double
    */
    double get_universe_radius_() const;
    /*
    *@brief compares a planet to all other planets inorder to calculate net_force
    *@param iterator for the vecotor of bodies
    *@retrun nothing
    */
    void update_force(const std::vector<Body*>::iterator test_planet);

 private:
    double time_limit_, time_step_;  ///< time limit and step progress
    sf::Event event_;  ///< event_ type for input (extra credit mainly)
    sf::Font font_;  ///< font loaded for the text
    sf::Text text_;  ///< text ouputed to the screen
    double universe_radius_;  ///< universe radius
    int screen_size_;  ///< screen size
    sf::RenderWindow window_;  ///< window object for the program
    std::vector<Body*> planets_;  ///< holds planet objects on screen NOLINT
  	std::vector<Star*> stars_;  ///< holds the star object on screen NOLINT
};
}  // namespace SolarSystem

#endif
