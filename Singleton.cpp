/*
 * So lets say in your pgroam, there is one object
 * that should preform the function.
 *
 * This is many times called an Anti-Pattern.
 *
 * Why to do this
 * 1. It is easy to implement
 * 2. It is to share the object in the program
 *
 * Destruction of dependent Singletons, use the atexit()
 *
 * References:
 * 1. https://sourcemaking.com/design_patterns/singleton
 *
 */

#include <iostream>

class Singleton
{
    int value{0};

    // Constructor is private
    // People cannot create an object of this class
    Singleton() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    // This is just to present that idea, this destructor is really called.
    // Private destructor is allowed, becuase the object is created by the class itself.
    ~Singleton() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    public:
    // Delete Copy Constructor and Assignment
    // Now we have ensured nobody can create a copy of static object
    Singleton(Singleton const& other) = delete;
    Singleton& operator=(Singleton const& other) = delete;

    static Singleton& instance()
    {
        static Singleton inst;
        return inst;
    }

    void print() const
    {
        std::cout << value << std::endl;
    }
};


int main()
{
    // Singleton x;         // This is not allowed

    // auto x = new Singleton(); // This is also not allowed
    std::cout << "Called Main" << std::endl;

    Singleton::instance().print();
    std::cout << "Exitting Main" << std::endl;

    return 0;
}
