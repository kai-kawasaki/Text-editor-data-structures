#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include "gapBuffer.h"
#include "pieceTable.h"

using namespace std;
using namespace chrono;

class Timer
{
private:
    time_point<system_clock> startTime;
    time_point<system_clock> endTime;
    bool running = false;
public:
    void start() {
        startTime = system_clock::now();
        running = true;
    }

    void stop()
    {
        endTime = system_clock::now();
        running = false;
    }

    double elapsedMicroseconds()
    {

        if(running)
        {
            endTime = system_clock::now();
        }

        return duration_cast<microseconds >(endTime - startTime).count();
    }

    double elapsedMilliseconds()
    {

        if(running)
        {
            endTime = system_clock::now();
        }

        return duration_cast<milliseconds>(endTime - startTime).count();
    }

    int elapsedSeconds() {
        return elapsedMilliseconds() / 1000;
    }
};

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

    void performActionA(int &tableTime, int &bufferTime, pieceTable *table, GapBuffer *buffer) {
        // Perform action A
        Timer timer;
        timer.start();
        string testString = "TEST STRING";
        for (int i = 0; i < 1000; i++) {
            table->insert(rand()%100, (testString.substr(0,rand()%10)));
        }
        tableTime = timer.elapsedMicroseconds();
        timer.start();
        for (int i=0; i < 1000; i++) {
            int randing = rand()%1000;
            for (int i=0; i<randing; i++) {
                buffer->move_right();
            }
            for (int i=0; i<rand()%10; i++) {
                buffer->insert_char(testString[i]);
            }
            for (int i=0; i<randing; i++) {
                buffer->move_left();
            }
        }
        bufferTime = timer.elapsedMicroseconds();
    }

    void performActionB(int &tableTime, int &bufferTime, pieceTable *table, GapBuffer *buffer) {
        // Perform action B
        Timer timer;
        int randing = rand()%10;
        timer.start();
        for (int i = 0; i < 1000; i++) {
            table->remove(rand()%100, (randing));
        }
        tableTime = timer.elapsedMicroseconds();
        timer.start();
        for (int i=0; i < 10; i++) {
            for (int x=0; x<randing; x++) {
                buffer->delete_char();
            }
        }

        bufferTime = timer.elapsedMicroseconds();
    }


};

UnnamedClass createObject() {
    return UnnamedClass();
}

std::string getAverageTimeString() {
    // This function would be implemented elsewhere
    return "Average time placeholder";
}
void processInput(string& inputstring) {

}

int main() {
    pieceTable *table = new pieceTable();
    GapBuffer *buffer = new GapBuffer();
    Timer timer;
    timer.start();
    table->loadFile("files/input.txt");
    double tableLoadTime = timer.elapsedMicroseconds();
    timer.start();
    buffer->from_file("files/input.txt");
    double bufferLoadTime = timer.elapsedMicroseconds();
    buffer->print();
    int tableAddTime;
    int bufferAddTime;
    int tableRemoveTime;
    int bufferRemoveTime;

    sf::RenderWindow window(sf::VideoMode(960, 720), "Two Button Window");
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        std::cout << "Error loading font file" << std::endl;
        return false;
    }
    sf::Text inputHeading("File load time (microseconds):", font, 24);
    inputHeading.setPosition(50, 50);
    inputHeading.setFillColor(sf::Color::Black);

    sf::RectangleShape inputBox(sf::Vector2f(700, 50));
    inputBox.setPosition(50, 90);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::Black);

    sf::Text inputText("", font, 18);
    inputText.setPosition(60, 100);
    inputText.setFillColor(sf::Color::Black);

    // Buttons
    Button buttonA(50, 160, 150, 50, font, "Add random");
    Button buttonB(250, 160, 150, 50, font, "Remove random");

    // Output box
    sf::Text outputHeading("Average Time:", font, 24);
    outputHeading.setPosition(50, 230);
    outputHeading.setFillColor(sf::Color::Black);

    sf::RectangleShape outputBox(sf::Vector2f(700, 100));
    outputBox.setPosition(50, 270);
    outputBox.setFillColor(sf::Color::White);
    outputBox.setOutlineThickness(2);
    outputBox.setOutlineColor(sf::Color::Black);

    sf::Text outputText("", font, 18);
    outputText.setPosition(60, 280);
    outputText.setFillColor(sf::Color::Black);

    UnnamedClass obj = createObject();
    std::string input;
    bool isInputActive = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (inputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isInputActive = true;
                } else {
                    isInputActive = false;
                    processInput(input);  // Process input when clicking outside the box
                }

                if (buttonA.isMouseOver(window)) {
                    obj.performActionA(tableAddTime, bufferAddTime, table, buffer);
                    outputText.setString("Piece table average time: " + to_string(tableAddTime) + "ms\nGap buffer average time: " +
                                                 to_string(bufferAddTime) + "ms");
                } else if (buttonB.isMouseOver(window)) {
                    obj.performActionB(tableRemoveTime, bufferRemoveTime, table, buffer);
                    outputText.setString("Piece table average time: " + to_string(tableRemoveTime) + "ms\nGap buffer average time: " +
                                         to_string(bufferRemoveTime) + "ms");
                }
            }
            else if (event.type == sf::Event::TextEntered && isInputActive) {
                if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back();
                } else if (event.text.unicode < 128) {
                    input += static_cast<char>(event.text.unicode);
                }
                //inputText.setString(input);
            }
        }
        inputText.setString("Piece Table: " + to_string((int)tableLoadTime) + "ms, Gap Buffer: " + to_string((int)bufferLoadTime) + "ms");

        window.clear(sf::Color(240, 240, 240));

        window.draw(inputHeading);
        window.draw(inputBox);
        window.draw(inputText);
        buttonA.draw(window);
        buttonB.draw(window);
        window.draw(outputHeading);
        window.draw(outputBox);
        window.draw(outputText);

        window.display();
    }

    return 0;
}


