#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Button {
public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string text)
            : rectangle(sf::Vector2f(width, height)) {
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(sf::Color::Black);

        this->text.setFont(font);
        this->text.setString(text);
        this->text.setCharacterSize(18);
        this->text.setFillColor(sf::Color::Black);
        this->text.setPosition(
                x + (width - this->text.getLocalBounds().width) / 2.0f,
                y + (height - this->text.getLocalBounds().height) / 2.0f
        );
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        float btnPosX = rectangle.getPosition().x;
        float btnPosY = rectangle.getPosition().y;
        float btnxPosWidth = rectangle.getPosition().x + rectangle.getLocalBounds().width;
        float btnyPosHeight = rectangle.getPosition().y + rectangle.getLocalBounds().height;

        return (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY);
    }

private:
    sf::RectangleShape rectangle;
    sf::Text text;
};

class UnnamedClass {
public:
    UnnamedClass() {}

    void performActionA() {
        // Perform action A
    }

    void performActionB() {
        // Perform action B
    }
};

UnnamedClass createObject() {
    return UnnamedClass();
}

std::string getAverageTimeString() {
    // This function would be implemented elsewhere
    return "Average time placeholder";
}

int main() {
    sf::RenderWindow window(sf::VideoMode(960, 720), "Two Button Window");
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
        return false;
    }

    Button buttonA(50, 50, 150, 50, font, "Gap Buffer");
    Button buttonB(250, 50, 150, 50, font, "Piece Table");

    sf::Text outputHeading("Average Time:", font, 24);
    outputHeading.setPosition(50, 150);
    outputHeading.setFillColor(sf::Color::Black);

    sf::RectangleShape outputBox(sf::Vector2f(700, 100));
    outputBox.setPosition(50, 200);
    outputBox.setFillColor(sf::Color::White);
    outputBox.setOutlineThickness(2);
    outputBox.setOutlineColor(sf::Color::Black);

    sf::Text outputText("", font, 18);
    outputText.setPosition(60, 210);
    outputText.setFillColor(sf::Color::Black);

    UnnamedClass obj = createObject();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (buttonA.isMouseOver(window)) {
                    obj.performActionA();
                    outputText.setString(getAverageTimeString());
                } else if (buttonB.isMouseOver(window)) {
                    obj.performActionB();
                    outputText.setString(getAverageTimeString());
                }
            }
        }

        window.clear(sf::Color(240, 240, 240));

        buttonA.draw(window);
        buttonB.draw(window);
        window.draw(outputHeading);
        window.draw(outputBox);
        window.draw(outputText);

        window.display();
    }

    return 0;
}
