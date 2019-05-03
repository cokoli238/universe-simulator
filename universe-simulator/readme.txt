final project readme

Team Ethan Cumming and Christian Okoli

May 4th 2016

Ethan Cumming was responsible for the Universe and Star class. The Universe class serves as an engine for the program. It will use functions to input and output data. It also serves as first contact for generating a SFML window. The main program loop is within the generate fuction The star class inherits the sf::Drawable draw function in order to draw to screen. The amount of stars, their respective color, and radius are randomized. The Universe class is responsible for updating events for planet velocity and force via the planet vector and overloaded operators Body class operator.

Christian Okoli was responsible for the StarObject and Body class. The body class serve as a planet in the Universe. They will have a velocity, location, and mass by inheriting from the StarObject. The body class  use its draw function to convert coordinates for SFML. The step function calculates the new position and velocity in relation to the change in time. Christian was responsible for unit testing the conversion, velocity, and step function.

We plan to do the extra credit, if time permits, by implementing another planet that responds to keyboard input. The planet will use a handle events function and move based on input. The additional planet is used in the calculation of net force and acceleration loop on all other planets.