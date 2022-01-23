#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include <vector>
class abstract_command
{
public:
    virtual void execute() = 0;
};
class change_color : public abstract_command
{
    sf::Color color_;
    sf::Shape *object_;

public:
    change_color(sf::Color color, sf::Shape *object) : color_(color), object_(object) {}
    void execute() { object_->setFillColor(color_); }
};

class Button
{
    sf::RectangleShape rect_;
    abstract_command *cmd_;

public:
    Button(abstract_command *cmd, int x, int y) : cmd_(cmd)
    {
        rect_.setSize(sf::Vector2f(50, 30));
        rect_.setPosition(x, y);
        rect_.setFillColor(sf::Color::Red);
    }
    sf::RectangleShape &get_object() { return rect_; }
    bool isClicked(float x, float y)
    {
        if (rect_.getGlobalBounds().intersects(sf::Rect<float>(x, y, 0.1, 0.1)))
            cmd_->execute();
    }
};

class GraphicalObject : public sf::Sprite
{
    sf::Texture texture_;
    bool colidable_;

public:
    GraphicalObject(std::string texture_file,
                    sf::IntRect rect,
                    int x = 0,
                    int y = 0,
                    float scale = 1,
                    bool repeated = false,
                    bool colidable = true)
        : colidable_(colidable)
    {
        if (!texture_.loadFromFile(texture_file)) {
            std::cerr << "Could not load texture" << std::endl;
            return;
        }
        setTexture(texture_);
        texture_.setRepeated(repeated);
        setTextureRect(rect);
        setScale(scale, scale);
        setPosition(x, y);
    }
    GraphicalObject(std::string texture_file,
                    int x = 0,
                    int y = 0,
                    float scale = 1,
                    bool repeated = false,
                    bool colidable = true)
        : colidable_(colidable)
    {
        if (!texture_.loadFromFile(texture_file)) {
            std::cerr << "Could not load texture" << std::endl;
            return;
        }
        setTexture(texture_);
        texture_.setRepeated(repeated);
        setScale(scale, scale);
        setPosition(x, y);
    }
    bool is_colidable() { return colidable_; }
    //
};
class Bonus : public GraphicalObject
{
    int value_;

public:
    Bonus(std::string texture_file,
          int x = 0,
          int y = 0,
          float scale = 1,
          bool repeated = false,
          bool colidable = true)
        : value_(10), GraphicalObject(texture_file, x, y, scale, repeated, colidable)
    {}
    int getBonus() { return value_; }
};
class MazeAbstract
{
protected:
    std::vector<GraphicalObject *> objects_;
    GraphicalObject *guy_;
    int score_;

public:
    virtual void draw(sf::RenderWindow *window)
    {
        for (auto &el : objects_) {
            window->draw(*el);
        }
    }
    virtual void move_player(int x, int y)
    {
        guy_->move(x, y);
        if (check_colisions()) {
            guy_->move(-x, -y);
        }
    }
    virtual bool check_colisions()
    {
        sf::FloatRect guy_bb = guy_->getGlobalBounds();
        for (auto itr = objects_.begin(); itr != objects_.end();) {
            if (*itr != guy_) {
                if ((*itr)->is_colidable())
                    if ((*itr)->getGlobalBounds().intersects(guy_bb) == true) {
                        Bonus *bonus = dynamic_cast<Bonus *>(*itr);
                        if (bonus != nullptr) {
                            int val = bonus->getBonus();
                            itr = objects_.erase(itr);
                            score_ += val;

                            std::cout << "BONUS " << val << "total score: " << score_ << std::endl;

                            delete bonus;
                            continue;
                        }
                        return true;
                    }
            }
            itr++;
        }
        return false;
    }
};

class Maze : public MazeAbstract
{
public:
    Maze()
    {
        objects_.emplace_back(new GraphicalObject(
            "../tex/grass.png", sf::IntRect(0, 0, 800, 600), 0, 0, 1, true, false));
        objects_.emplace_back(
            new GraphicalObject("../tex/wall.png", sf::IntRect(0, 0, 40, 400), 100, 100, 0.3, true));
        objects_.emplace_back(
            new GraphicalObject("../tex/wall.png", sf::IntRect(0, 0, 40, 400), 300, 200, 0.3, true));
        guy_ = new GraphicalObject("../tex/guy.png");
        for (int i = 0; i < 10; i++) {
            objects_.emplace_back(new Bonus("../tex/star.png", rand() % 800, rand() % 600, 0.03));
        }
        objects_.emplace_back(guy_);
    }
};

class Scene
{
    sf::RenderWindow *window_;
    MazeAbstract *maze_;
    std::vector<Button> buttons_;
    sf::RectangleShape rect_;

public:
    Scene(sf::VideoMode window_size) : window_(new sf::RenderWindow(window_size, "My window"))
    {
        //        window_ = new sf::RenderWindow(window_size, "My window");
        rect_.setFillColor(sf::Color::Red);
        rect_.setSize(sf::Vector2f(20, 20));
        rect_.setPosition(200, 200);

        buttons_.emplace_back(new change_color(sf::Color::Green, &rect_), 300, 300);
        buttons_.emplace_back(new change_color(sf::Color::Blue, &rect_), 370, 300);
    }
    void setMaze(MazeAbstract *maze) { maze_ = maze; }
    virtual MazeAbstract *create(int level)
    {
        switch (level) {
        case 0:
            return new Maze();
            //        case 1:
            //            return Maze(....);
            //        case 2:
            //            return MazePlus(....);
        }
    }
    void window_loop()
    {
        while (window_->isOpen()) {
            // check all the window's events that were triggered since the last iteration of the loop
            events_handlig();

            draw();
        }
    }
    void draw()
    {
        window_->clear(sf::Color::Black);
        // draw everything here...
        maze_->draw(window_);
        for (auto &bt : buttons_) {
            window_->draw(bt.get_object());
        }
        window_->draw(rect_);
        // end the current frame
        window_->display();
    }
    void events_handlig()
    {
        sf::Event event;
        while (window_->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window_->close();
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    //                    guy_->setTextureRect(sf::IntRect(10, 20, 20, 15));

                    std::cout << "Space released" << std::endl;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                //                guy.move(-2, 0);
                maze_->move_player(-2, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                maze_->move_player(2, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                maze_->move_player(0, 2);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                maze_->move_player(0, -2);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window_);
                    std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y
                              << std::endl;
                    for (auto &bt : buttons_) {
                        bt.isClicked(mouse_pos.x, mouse_pos.y);
                    }
                }
            }
        }
    }
};

int main()
{
    // create the window

    Maze *maze = new Maze();

    Scene scena(sf::VideoMode(800, 600));
    scena.setMaze(scena.create(0));
    scena.window_loop();

    return 0;
}
