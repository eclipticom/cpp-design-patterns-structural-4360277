#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Abstract base class for concrete Shape classes
class Shape
{
public:
    Shape(int x, int y) : m_X(x), m_Y(y) {}
    // TODO: add rotation 
    
    virtual void draw() const = 0;
    virtual ~Shape() = default;

protected:
    int m_X = 0;
    int m_Y = 0;

    string getPosition() const
    {
        return "Position: (" + to_string(m_X) + ", " + to_string(m_Y) + ")";
    }
};

// Concrete Shape classes
class Circle : public Shape
{
public:
    explicit Circle(int x, int y, double radius) : Shape(x,y), m_Radius(radius) {}

    void draw() const override
    {
        cout << "Drawing a circle with radius " << m_Radius << " " << getPosition() << endl;
    }

private:
    double m_Radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(int x, int y, double width, double height) : Shape(x,y), m_Width(width), m_Height(height) {}

    void draw() const override
    {
        cout << "Drawing a rectangle with width " << m_Width << " and height " << m_Height << " " << getPosition() << endl;
    }

private:
    double m_Width;
    double m_Height;
};

class Triangle : public Shape
{
public:
    Triangle(int x, int y, double side1, double side2, double side3) : Shape(x,y), m_Side1(side1), m_Side2(side2), m_Side3(side3) {}

    void draw() const override
    {
        cout << "Drawing a triangle with sides " << m_Side1 << ", " << m_Side2 << ", and " << m_Side3 << " " << getPosition() << endl;
    }

private:
    double m_Side1;
    double m_Side2;
    double m_Side3;
};

class CompositeShape : public Shape
{
public:
    CompositeShape(int x, int y) : Shape(x,y) {}
    void addShape(unique_ptr<Shape> shape)
    {
        m_Shapes.push_back(move(shape));
    }

    void draw() const override
    {
        cout << "Drawing a composite shape " << getPosition() << endl;
        for (const auto &shape : m_Shapes)
        {
            shape->draw();
        }
    }

    void removeShape(size_t index)
    {
        if (index < m_Shapes.size())
        {
            m_Shapes.erase(m_Shapes.begin() + index);
            cout << "Shape at index " << index << " removed." << endl;
        }
        else
        {
            cout << "Index "<< index <<" out of range. No shape removed." << endl;        
        }
    };

    private:
    std::vector<unique_ptr<Shape>> m_Shapes;
};

int main()
{

    // Create a composite shape and add shapes to it
    auto cs = make_unique<CompositeShape>(10,20);
    auto circle = make_unique<Circle>(1,2,5);
    auto rectangle = make_unique<Rectangle>(10,20, 10, 20);
    auto triangle = make_unique<Triangle>(100,100, 3, 4, 5);
    


    cs->addShape(move(circle)); 
    cs->addShape(move(rectangle));
    cs->addShape(move(triangle));
    cs->draw();

    cout << "\nAdding 1 more cirlce." << endl;

    auto circle2 = make_unique<Circle>(10,10,5);
    cs->addShape(move(circle2)); 
    cs->draw();

    cout << "\nTrying to remove a shape that is not part of the composite shape." << endl;
    cs->removeShape(3); // This will not work as circle2 is not part of the composite shape
    cs->draw(); // This will still show the original circle 

    return 0;
}
