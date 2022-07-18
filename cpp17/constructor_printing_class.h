// A class which prints its constructor calls and assigns a unique id to each instance. This is uusefull for when trying ot understand which call gets triggered in different cases.
//
//
//
class ConstructorPrintingClass {
    static inline int uid_generator = 0;

    int uid = -1;

    public:
    // Default Constructor
    ConstructorPrintingClass() : uid{++uid_generator} {
        std::cout << __PRETTY_FUNCTION__ << " " << uid << std::endl;
    }

    // Copy Constructor
    ConstructorPrintingClass(ConstructorPrintingClass const& other) : uid{++uid_generator} {
        std::cout << __PRETTY_FUNCTION__ << " " << uid << " " << other.uid << std::endl;
    }

    // Move Assignment Operator
    ConstructorPrintingClass(ConstructorPrintingClass&& other) {
        uid = other.uid;
        std::cout << __PRETTY_FUNCTION__ << " " << uid << std::endl;
    }

    // Copy Assignment Operator
    ConstructorPrintingClass& operator=(ConstructorPrintingClass const& other) {
        std::cout << __PRETTY_FUNCTION__ << " " << uid << " " << other.uid << std::endl;
        uid = other.uid;
        return *this;
    }

    // Move Assignment Operator
    ConstructorPrintingClass& operator=(ConstructorPrintingClass&& other) {
        std::cout << __PRETTY_FUNCTION__ << " " << uid << " " << other.uid << std::endl;
        uid = other.uid;
        return *this;
    }
};
