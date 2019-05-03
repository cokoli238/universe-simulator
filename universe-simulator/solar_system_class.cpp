/*
*@copyright Ethan
*/
#include "solar_system_class.hpp"

#define GRAVITY_VAL 6.67e-11
#define FPS 85

namespace SolarSystem {

Universe::Universe() {
// No implementation
}

Universe::Universe(int num_of_planets, int screen_size,
    double radius_of_universe, double time_limit, double time_step)
    : screen_size_(screen_size)
    , universe_radius_(radius_of_universe)
    , time_limit_(time_limit), time_step_(time_step) {
    // create the window
    // allocate space for planets
    // allocate and fill? spcae for stars
    // use random genaraton
    window_.create(sf::VideoMode(screen_size_, screen_size_), "Universe");
    window_.setFramerateLimit(FPS);
    if (!font_.loadFromFile("Walkway_Bold.ttf"))
        std::cout << "font did not load properly" << std::endl;
    text_.setFont(font_);
    text_.setColor(sf::Color::White);
    text_.setCharacterSize(18);
    // between 100 and half of screen size amount of stars
    int num_of_stars = rand() % screen_size/2 + 100; //NOLINT because rand()
    stars_.reserve(num_of_stars);
    for (int i = 0; i < num_of_stars; i++) {
        float rand_radius = ((float)(rand() % 50))/100; //NOLINT because rand()
        stars_.push_back(new Star(rand_radius));
    }
    // reserve and create based on number of planets
    planets_.reserve(num_of_planets);
    for (int t = 0; t < num_of_planets; t++) {
        planets_.push_back(new Body);
    }
}

void Universe::generate() {
    int total_time = time_limit_;
    int current_time = 0;
    std::ostringstream out_stream;
    while (window_.isOpen()) {
        while (window_.pollEvent(event_)) {
            if (event_.type == sf::Event::Closed)
                window_.close();
            if (event_.key.code == sf::Keyboard::Escape)
                window_.close();
        }
        if (current_time < total_time) {
            window_.clear();
            // draws all the stars in the vector
            std::vector<Star*>::iterator star_itr = stars_.begin();
            while (star_itr != stars_.end()) {
                (*star_itr)->draw(window_);
                star_itr++;
            }
            // updates the movement of planets in the vector
            std::vector<Body*>::iterator planet_itr = planets_.begin();
            while (planet_itr != planets_.end()) {
                update_force(planet_itr);
                (*planet_itr) -> update_acceleration();
                (*planet_itr) -> step(time_step_);
                planet_itr++;
            }
            // draws all the planets in the vector
            std::vector<Body*>::iterator draw_itr = planets_.begin();
            while (draw_itr != planets_.end()) {
                (*draw_itr) -> draw(window_);
                draw_itr++;
            }

            out_stream.str("");  // emptys the past stream
            out_stream.clear();  // clears the data
            out_stream << current_time;  // string stream prints out time
            text_.setString(out_stream.str());
            window_.draw(text_);
            // (iter)-> handleEvents(sf )
            current_time += time_step_;
            window_.display();
        }
    }
}

void Universe::input_data(std::istream & stream) {
    // goes throught vector of bodies
    // uses extractin operator in body
    for (int i = 0; i < planets_.size(); i++) {
        stream >> *planets_[i];
    }
    std::cout << planets_.size() << std::endl;
}

void Universe::output_data() {
    // use body extraction operator to print position and velocity
    for (int i = 0; i < planets_.size(); i++) {
        std::cout << *planets_[i];
    }
}

sf::Vector2f Body::convert_cordinates() {
    double distance_per_pixel = 2.50e+11/(1000/2.0);
    double x_pixel, y_pixel;

    x_pixel = (1000/2.0) + (location_.x/distance_per_pixel);
    y_pixel = (1000/2.0) - (location_.y/distance_per_pixel);
    // std::cout << x_pixel << ":" << y_pixel << std::endl;

    return sf::Vector2f(x_pixel, y_pixel);
}

void Universe::update_force(const std::vector<Body*>::iterator test_planet) {
    double change_in_x_pos, change_in_y_pos, radius_squared;
    std::vector<Body*>::iterator compare_planet = planets_.begin(); //NOLINT
    double test_mass = (*test_planet) -> getMass();
    sf::Vector2f net_force = sf::Vector2f(0, 0);
    while (compare_planet != planets_.end()) {
        // if planets are the same end forces
        if (test_planet != compare_planet) {
            double compare_mass = (*compare_planet) -> getMass();
            // calculate detla x and delta y
            change_in_x_pos = (((*compare_planet) -> getLocation()).x)
                - (((*test_planet) -> getLocation()).x);
            change_in_y_pos = (((*compare_planet) -> getLocation()).y)
                - (((*test_planet) -> getLocation()).y);
            radius_squared = (change_in_x_pos * change_in_x_pos)
             + (change_in_y_pos * change_in_y_pos);

            double radius = sqrt(radius_squared);

            double force_distance = (GRAVITY_VAL *
                (test_mass * compare_mass)) / radius_squared;

            net_force.x += force_distance * (change_in_x_pos/radius);
            net_force.y += force_distance * (change_in_y_pos/radius);
        }
        compare_planet++;
    }
    (*test_planet) -> setForce(net_force);
}

void SpaceObject::draw(sf::RenderTarget &target,
    sf::RenderStates states) const {
}

Star::Star() {
// No implementation
}

Star::Star(float r):radius_(r) {
    circle_.setRadius(radius_);
    circle_.setOutlineColor(sf::Color((rand()%64)+192, //NOLINT
    (rand()%64)+192, rand()%256, 255)); //NOLINT
    circle_.setOutlineThickness(1);
    circle_.setPosition(rand() % 1000, rand() % 1000); //NOLINT
}

void Star::draw(sf::RenderWindow & window) {
    window.draw(circle_);
}

SpaceObject::SpaceObject() {
    // No implementation
}


void SpaceObject::setVelocity(sf::Vector2f v) {
    velocity_ = v;
}

sf::Vector2f SpaceObject::getVelocity() const {
    return velocity_;
}

sf::Vector2f SpaceObject::getLocation() const {
    return location_;
}

void Body::setLocation(sf::Vector2f l) {
    location_ = l;
}

void Body::update_acceleration() {
    acceleration_.x = force_.x/ mass_;
    acceleration_.y = force_.y/ mass_;
}

double Body::getMass() const {
    return mass_;
}

void SpaceObject::setMass(double m) {
    mass_ = m;
}

void SpaceObject::setRadius(double r) {
    radius_ = r;
}

sf::Vector2f Body::getForce() const {
    return force_;
}

void Body::setForce(sf::Vector2f f) {
    force_ = f;
}

sf::Vector2f Body::getAcceleration() const {
    return acceleration_;
}

void Body::setAcceleration(sf::Vector2f a) {
    acceleration_ = a;
}

void Body::planetEvent(sf::Event & event) {
}

bool operator == (const Body& lhs, const Body& rhs) {
    if (lhs.mass_ == rhs.mass_)
        return true;
    else
        return false;
}


istream & operator >> (istream & in, Body & body_obj) {
    in >> body_obj.location_.x >> body_obj.location_.y
       >> body_obj.velocity_.x >> body_obj.velocity_.y
       >> body_obj.mass_ >> body_obj.body_name;
     body_obj.fillBody();
     return in;
}

ostream & operator << (ostream & out, Body & body_obj) {
    out << body_obj.location_.x << " ";
    out << body_obj.location_.y << " ";
    out << body_obj.velocity_.x << " ";
    out << body_obj.velocity_.y << " ";
    out << body_obj.mass_ << " ";
    out << body_obj.body_name << std::endl;

    return out;
}

sf::Sprite Body::getSprite() {
  return sprite_;
}

void Body::fillBody() {
    image_.loadFromFile(body_name.c_str());
    texture_.loadFromImage(image_);
    sprite_.setTexture(texture_);
}

Body::Body() {
}

void Body::step(double seconds) {
  sf::Vector2f new_velocity, old_velocity, new_pos, old_pos;
  old_pos = location_;
  old_velocity = velocity_;

  new_velocity.x = old_velocity.x + seconds * acceleration_.x;
  new_velocity.y = old_velocity.y +  seconds * acceleration_.y;

  new_pos.x = old_pos.x + seconds * new_velocity.x;
  new_pos.y = old_pos.y + seconds * new_velocity.y;

  location_ = new_pos;
  velocity_ = new_velocity;
}

void Body::draw(sf::RenderWindow & window) {
    sprite_.setPosition(convert_cordinates());
    window.draw(sprite_);
}

int Universe::get_screen_size() const {
    return screen_size_;
}

double Universe::get_universe_radius_() const {
    return universe_radius_;
}



}  // namespace SolarSystem
