// https://sourcemaking.com/design_patterns/visitor
//
//
#include <iostream>

class Visitor
{
    public:
        virtual void visit(class Element const& elem) const
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        virtual void visit(class Bold const& elem) const
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        virtual void visit(class List const& elem) const
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
};

class Element
{
    public:
        virtual void accept(Visitor const& vistor) = 0;
};

class List : public Element
{
    public:
        void accept(Visitor const& visitor) override
        {
            visitor.visit(*this);
        }
};

class Bold : public Element
{
    public:
        void accept(Visitor const& visitor) override
        {
            visitor.visit(*this);
        }
};

class PrintVisitor : public Visitor
{
    public:
        void visit(List const& l) const
        {
            std::cout << "Print List" << std::endl;
        }

        void visit(Bold const& b) const
        {
            std::cout << "Print Bold" << std::endl;
        }
};

class CountVisitor : public Visitor
{
    public:
        void visit(List const& l) const override
        {
            static int visited{0};
            std::cout << __PRETTY_FUNCTION__ << " visited " << ++visited << "\n";
        }

        void visit(Bold const& b) const override
        {
            static int visited{0};
            std::cout << __PRETTY_FUNCTION__ << " visited " << ++visited << "\n";
        }

};

int main()
{
    CountVisitor cv;
    PrintVisitor pv;

    Element *list[] = { new Bold, new List};

    for (auto l : list)
    {
        l->accept(cv);
    }
    for (auto l : list)
    {
        l->accept(pv);
    }
}
