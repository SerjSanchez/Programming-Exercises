#include <stdio.h>
#include <iostream>

#include "single_responsibility.cpp"
#include "open_closed.cpp"
#include "liskov_sustitution.cpp"

using namespace std;
using namespace cpp_logger;

int main() {
    cout << "SOLID Principles example" << endl;

    cout << endl << "-----------------------------------------" << endl;
    cout << endl << "Principle 1: Single Responsibility" << endl;
    CppLogger logger = CppLogger("C++ Logger");
    logger.add_entry("Logger created. Adding first entry");
    logger.add_entry("Flux condenser warming up");
    logger.add_entry("Flux condenser ready");
    logger.add_entry("Flux condenser too hot");
    logger.add_entry("42");

    LoggerPersistance::storeLogger(logger);

    cout << endl << "-----------------------------------------" << endl;
    cout << endl << "Principle 2: Open-closed" << endl;

    Fruit apple {"Apple", Color::red, Size::medium};
    Fruit watermelon {"Watermelon", Color::green, Size::large};
    Fruit blueberry {"Blueberry", Color::blue, Size::small};
    Fruit pear {"Pear", Color::green, Size::medium};
    Fruit strawberry {"Strawberry", Color::red, Size::small};
    vector<Fruit*> fruits {&apple, &watermelon, &blueberry, &pear, &strawberry};
    FruitFilter ff;
    ColorSpecification redSpec = ColorSpecification(Color::red);

    auto const redFruits = ff.filter(fruits, redSpec);
    cout << "Red fruits:" << endl;
    for(auto const redFruit : redFruits) {
        cout << " - " << redFruit->name << endl;
    }

    ColorSpecification greenSpec = ColorSpecification(Color::green);
    SizeSpecification largeSpec = SizeSpecification(Size::large);
    CombinedSpec largeAndGreen = CombinedSpec(largeSpec, greenSpec);

        auto const largeGreenFruits = ff.filter(fruits, largeAndGreen);
        cout << "Large and green fruits:" << endl;
        for(auto const fruit : largeGreenFruits) {
        cout << " - " << fruit->name << endl;
    }

    cout << endl << "-----------------------------------------" << endl;
    cout << endl << "Principle 3: Liskov Sustitution" << endl;

    Rectangle rect(3, 4);
    processRectangle(rect);

    Square square(4);
    processRectangle(square);

    return 0;
}