#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { red, green, blue };
enum class Size {small, medium, large};

struct Fruit {
    string name;
    Color color;
    Size size;
};

// To make the filters generic, start defining two templates
// The first one, a generic specification, to indicate a type that allows checking if a quality is found
template <typename T> struct Specification {
    virtual bool isSatisfied(T *item) = 0;
};
// The second one, a generic filter, as an object that implements the specification
template <typename T> struct Filter {
    virtual vector <T*> filter(vector <T*>, Specification<T>& spec) = 0;
};

// Now, create an specification for each type of parameter we want to filter by
struct ColorSpecification : Specification<Fruit> {
    Color color;

    ColorSpecification(Color color) : color(color) {}

    bool isSatisfied(Fruit *fruit) override {
        return fruit->color == color;
    }
};
// With this structure, adding more specifications is just a matter of creating them, without touching the previous code
struct SizeSpecification : Specification<Fruit> {
    Size size;

    SizeSpecification(Size size) : size(size) {}

    bool isSatisfied(Fruit *fruit) override {
        return fruit->size == size;
    }
};

// Now it would even be possible to combine specifications without updating the previous code using a combinator
template <typename T> struct CombinedSpec : Specification<Fruit> {
    Specification &first;
    Specification &second;

    CombinedSpec(Specification<T> &first, Specification<T> &second) : first(first), second(second) {}

    bool isSatisfied(Fruit *fruit) override {
        return first.isSatisfied(fruit) && second.isSatisfied(fruit);
    }
};


struct FruitFilter : Filter<Fruit> {
    vector<Fruit*> filter(vector<Fruit*> items, Specification<Fruit>& spec) override {
        vector<Fruit*> result;
        for(auto const & item : items) {
            if (spec.isSatisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};