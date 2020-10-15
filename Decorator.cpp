// Decorator Pattern
// Although this isn't a very practical example, but this should convery the
// idea how to use this. I will also try to create an example using
// static polymorphism with templates

#include <iostream>
#include <string>
#include <algorithm>

class StringConvertible
{
    public:
        virtual std::string Stringify() const = 0;
};

class Person : public StringConvertible
{

    public:
        Person(std::string name, std::string address, int age)
            : name_{std::move(name)}
            , address_{std::move(address)}
            , age_{age}
        {}

        std::string Stringify() const override
        {
            std::string result;
            result += "Name: " + name_ + " ";
            result += "Address: " + address_ + " ";
            result += "Age: " + std::to_string(age_);
            return result;
        }

    private:
        std::string name_;
        std::string address_;
        int         age_;
};

class StringConvertibleDecorator : public StringConvertible
{
    public:
        virtual std::string Stringify() const = 0;
};

class LowerCaseStringDecorator : public StringConvertibleDecorator
{
    public:
        LowerCaseStringDecorator(StringConvertible const* component)
            : component_{component}
        {}

    std::string Stringify() const override
    {
        auto result = component_->Stringify();
        std::transform(result.begin(), result.end(), result.begin(),  [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    private:
        const StringConvertible* component_{nullptr};
};


void LowerCasePrint(StringConvertible const* obj)
{
    LowerCaseStringDecorator temp(obj);
    std::cout << temp.Stringify() << std::endl;
}


int main()
{
    auto commander = new Person{"Anirudh", "Varanasi", 24};
    LowerCasePrint(commander);

    return 0;
}
