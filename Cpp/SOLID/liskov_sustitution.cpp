#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Create a base class that implements a series of functionalities
class Rectangle {

    protected:
        int width, height;
    public: 
        Rectangle(int width, int height) : width(width), height(height) {}

        int getWidth() {
            return width;
        }
        int getHeight() {
            return height;
        }

        virtual void setWidth(int width) {
            Rectangle::width = width;
        }

        virtual void setHeight(int height) {
            Rectangle::height = height;
        }

        int area() {
            return width * height;
        }
};

// To test how to do things wrong with this, let's create a function to do some processing on the rectangle
void processRectangle(Rectangle& r) {
    int w = r.getWidth();
    r.setHeight(10);

    cout << "Expected area = " << w*10 << endl;
    cout << "Calculated area = " << r.area() << endl;
    if (w*10 == r.area()) {
        cout << "This time it's OK!" << endl << endl;
    } else {
        cout << "Whoops, not OK" << endl << endl;
    }
}

// Now, lets inherit from the Rectangle (Public inheritance -> All members visibility inherited as defined in the original class)
class Square : public Rectangle {
    public:
        Square(int size) : Rectangle(size, size) {}
        // This overrides are going to break the Lyskov substitution because this child class cannot substitute the Rectangle class in processRectangle()
        // This happens because we are affecting more variables than the parent class with the overrides
        // It's not possible to avoid breaking the Liskov substitution principle in this case, so it would be best to not have this inheritance at all
        // and use any other way of relating these shapes (such as a factory)
        void setWidth(int width) override {
            this->width = this->height = width;
        }

        void setHeight(int height) override {
            this->width = this-> height = width;
        }
};