#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

const sf::Vector2f reflect(const sf::Vector2f& vector, const sf::Vector2f& normal)
{
    return vector - 2 * dotProduct(vector, normal) * normal;
}

float magnitude(const sf::Vector2f v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

const sf::Vector2f normalize(const sf::Vector2f v)
{
    return v / magnitude(v);
}

const float directionLength(const sf::Vector2f v)
{
    return std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
}

class Font
{
public:
    sf::Font m_font;
    bool m_valid = false;
    std::string m_path = "";
    int m_size = -1;
    sf::Color m_color;

public:
    Font(const std::string& path, const int size, const sf::Color& color) 
        : m_path(path)
        , m_size(size)
        , m_color(color)
    {
        m_valid = m_font.loadFromFile(m_path);
    }

    bool setText(const std::string& string, sf::Text& text)
    {
        if (!m_valid)
        {
            std::cout << "Font is invalid!" << std::endl;
            return false;
        }

        text.setFont(m_font);
        text.setCharacterSize(m_size);
        text.setFillColor(m_color);
        text.setString(string);

        return true;
    }
};

class Shape
{
protected:
    sf::Shape* m_shape;
    std::string m_name;
    int m_posX;
    int m_posY;
    sf::Vector2f m_velocity;
    sf::Color m_color;
    bool m_isRendering = true;
    sf::Vector2f m_move;

public:
    Shape(const std::string& name, 
          const int posX, const int posY, 
          const sf::Vector2f& velocity,
          const sf::Color& color)
        : m_name(name)
        , m_posX(posX)
        , m_posY(posY)
        , m_velocity(velocity)
        , m_color(color)
    {
        m_move = m_velocity;
    }

    const sf::Shape* getShape() const { return m_shape; }
    sf::Shape* getShape() { return m_shape; }
    const std::string& getName() const { return m_name; }
    const sf::Vector2f& getVelocity() const { return m_velocity; }
    const bool isRendering() const { return m_isRendering; }
    bool* isRendering() { return &m_isRendering; }
    void setIsRendering(const bool isRendering) { m_isRendering = isRendering; }
    void setName(const std::string& name) { m_name = name; } 
    void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }

    void draw(sf::RenderWindow& window, sf::Clock& deltaClock, Font& font)
    {
        if(!m_shape)
        {
            return;
        }

        if (!m_isRendering)
        {
            return;
        }

        sf::Vector2f shapeSize = sf::Vector2f(
            m_shape->getLocalBounds().width * m_shape->getScale().x,
            m_shape->getLocalBounds().height * m_shape->getScale().y
        );

        if (m_shape->getPosition().x < 0)
        {
            m_move = reflect(m_move, sf::Vector2f(1, 0));
        }
        else if (m_shape->getPosition().x > window.getSize().x - shapeSize.x)
        {
            m_move = reflect(m_move, sf::Vector2f(-1, 0));
        }

        if (m_shape->getPosition().y < 0)
        {
            m_move = reflect(m_move, sf::Vector2f(0, 1));
        }
        else if (m_shape->getPosition().y > window.getSize().y - shapeSize.y)
        {
            m_move = reflect(m_move, sf::Vector2f(0, -1));
        }
    
        m_move = normalize(m_move);
        m_shape->move(sf::Vector2f(
            m_move.x * m_velocity.x, 
            m_move.y * m_velocity.y
        ));

        sf::Text text;
        font.setText(m_name, text);
        float textPosX = m_shape->getPosition().x;
        textPosX += shapeSize.x / 2 - text.getLocalBounds().width / 2;
        float textPosY = m_shape->getPosition().y;
        textPosY += shapeSize.y / 2 - (text.getLocalBounds().height / 2 + (text.getCharacterSize() - text.getLocalBounds().height));
        text.setPosition(textPosX, textPosY);

        window.draw(*m_shape);
        window.draw(text);
    };
};

// Circle CGreen 100 100 -3 2 0 255 0 50
class Circle : public Shape
{
public:
    Circle(const std::string& name, 
            const int posX, const int posY, 
            const sf::Vector2f& velocity,
            const sf::Color& color,
            const float radius)
    : Shape(name, posX, posY, velocity, color)
    {
        m_shape = new sf::CircleShape(radius);
        m_shape->setPosition(m_posX, m_posY);
        m_shape->setFillColor(m_color);
    }
};

// Rectangle RRed 200 200 4 4 255 0 0 50 25
class Rectangle : public Shape
{
public:
    Rectangle(const std::string& name, 
            const int posX, const int posY, 
            const sf::Vector2f& velocity,
            const sf::Color& color,
            const sf::Vector2f& size)
    : Shape(name, posX, posY, velocity, color)
    {
        m_shape = new sf::RectangleShape(size);
        m_shape->setFillColor(m_color);
        m_shape->setPosition(m_posX, m_posY);
    }
};

class ConfigManager
{
    unsigned int m_windowWidth = 0;
    unsigned int m_windowHeight = 0;
    std::string m_configPath;
    std::ifstream m_fileIn;
    std::vector<Font> m_fonts;
    std::vector<Shape*> m_shapes;

    void resetFileStream()
    {
        m_fileIn.clear();
        m_fileIn.seekg(0);
    }

    void getWindowSize()
    {
        std::string token;
        while (m_fileIn >> token)
        {
            if (token == "Window")
            {
                m_fileIn >> m_windowWidth >> m_windowHeight;
            }
        }
        resetFileStream();
    }
    
public:
    ConfigManager(const std::string& configPath)
        : m_configPath(configPath)
        , m_fileIn(std::ifstream(m_configPath))
    {
        getWindowSize();
        getFonts();
        setCircles();
        setRectangles();
    }

    unsigned int getWindowWidth() const { return m_windowWidth; }
    unsigned int getWindowHeight() const { return m_windowHeight; }
    std::vector<Shape*>& getShapes() { return m_shapes; } 
    Shape* findShape(const std::string& name)
    {
        for (Shape* shape : m_shapes)
        {
            if (shape->getName() == name)
            {
                return shape;
            }
        }

        return nullptr;
    }

    std::vector<Font>& getFonts()
    {
        if (m_fonts.size() > 0)
        {
            return m_fonts;
        }

        // Font fonts/tech.ttf 18 255 255 255
        std::string token;
        std::string path;
        int size;
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        while (m_fileIn >> token)
        {
            if (token == "Font")
            {
                m_fileIn >> path >> size >> red  >> green >> blue;
                m_fonts.push_back(Font(path, size, sf::Color(red, green, blue)));
            }
        }

        resetFileStream();

        return m_fonts;
    }

    void setCircles()
    {
        std::string token;
        std::string name;
        int posX;
        int posY;
        int velocityX;
        int velocityY;
        int red;
        int green;
        int blue;
        int radius;
        while(m_fileIn >> token)
        {
            // Circle CGreen 100 100 -3 2 0 255 0 50
            if (token == "Circle")
            {
                m_fileIn >> name >> posX >> posY >> velocityX >> velocityY >> red >> green >> blue >> radius;
                m_shapes.push_back(new Circle(name, posY, posX, sf::Vector2f(velocityX, velocityY), sf::Color(red, green, blue), radius));
            }
        }
        resetFileStream();
    }

    void setRectangles()
    {
        std::string token;
        std::string name;
        int posX;
        int posY;
        int velocityX;
        int velocityY;
        int red;
        int green;
        int blue;
        int sizeX;
        int sizeY;
        while(m_fileIn >> token)
        {
            // Rectangle RRed 200 200 4 4 255 0 0 50 25
            if (token == "Rectangle")
            {
                m_fileIn >> name >> posX >> posY >> velocityX >> velocityY >> red >> green >> blue >> sizeX >> sizeY;
                m_shapes.push_back(new Rectangle(name, 
                                                 posX, posY, 
                                                 sf::Vector2f(velocityX, velocityY),
                                                 sf::Color(red, green, blue), 
                                                 sf::Vector2f(sizeX, sizeY)));
            }
        }
        resetFileStream();
    }
};

// ImGui Data

int main(int argc, char* argv[])
{
    ConfigManager configManager("config.txt");
    sf::RenderWindow window(sf::VideoMode({configManager.getWindowWidth(), configManager.getWindowHeight()}), "Assignment 1");
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window))
    {
        return -1;
    }
    sf::Clock deltaClock;


    while (window.isOpen())
    {
	sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Shape Properties");
        ImGui::PushItemWidth(200);

        // Dropdown with the shape names
        static std::string selectedName = configManager.getShapes()[0]->getName();
        static bool selectionChanged = true;
        if (ImGui::BeginCombo("Shape", selectedName.c_str()))
        {
            for (Shape* shape : configManager.getShapes())
            {
                if (ImGui::Selectable(shape->getName().c_str(), shape->getName() == selectedName))
                {
                    selectedName = shape->getName();
                    selectionChanged = true;
                }

                if (shape->getName() == selectedName)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        Shape* selectedShape = configManager.findShape(selectedName);
        const sf::Color& shapeColor = selectedShape->getShape()->getFillColor();

        static float scaleValue = selectedShape->getShape()->getScale().x;
        static float velocityX = 0.0f;
        static float velocityY = 0.0f;
        static float col[3] = { shapeColor.r / 255.0f, shapeColor.g / 255.0f, shapeColor.b / 255.0f };
        static char strNameInput[255] = "";

        if (selectionChanged)
        {
            scaleValue = selectedShape->getShape()->getScale().x;
            col[0] = shapeColor.r / 255.0f;
            col[1] = shapeColor.g / 255.0f;
            col[2] = shapeColor.b / 255.0f;
            velocityX = selectedShape->getVelocity().x;
            velocityY = selectedShape->getVelocity().y;
        }

        // Properties for the shape
        ImGui::Checkbox("Draw Shape", selectedShape->isRendering());

        selectedShape->getShape()->setScale(scaleValue, scaleValue);
        ImGui::SliderFloat("Scale", &scaleValue, 0, 4);

        selectedShape->setVelocity(sf::Vector2f(velocityX, velocityY));
        ImGui::PushItemWidth(100);
        ImGui::Text("Velocity");
        ImGui::SliderFloat("X", &velocityX, -8.0f, 8.0f); ImGui::SameLine();
        ImGui::SliderFloat("Y", &velocityY, -8.0f, 8.0f);
        ImGui::PopItemWidth();

        selectedShape->getShape()->setFillColor(sf::Color(col[0] * 255, col[1] * 255, col[2] * 255));
        ImGui::ColorEdit3("Color", col);

        if (selectionChanged)
        {
            strncpy(strNameInput, selectedShape->getName().c_str(), sizeof(strNameInput) - 1);
            selectionChanged = false;
        }
        else
        {
            selectedShape->setName(std::string(strNameInput));
            selectedName = std::string(strNameInput);
        }
        ImGui::InputText("Name", strNameInput, IM_ARRAYSIZE(strNameInput));

        ImGui::PopItemWidth();
        ImGui::End();

        window.clear();
        for (Shape* shape : configManager.getShapes())
        {
            shape->draw(window, deltaClock, configManager.getFonts()[0]);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
