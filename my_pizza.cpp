#include <iostream>
#include <memory>
using namespace std;

class Pizza
{
public:
    virtual string description() const = 0;
    virtual double price() const = 0;
    virtual ~Pizza() = default;
};

class MargheritaPizza : public Pizza
{
public:
    string description() const override
    {
        return "Margherita Pizza";
    }

    double price() const override
    {
        return 9.99;
    }
};

class HawaiianPizza : public Pizza
{
public:
    string description() const override
    {
        return "Hawaiian Pizza";
    }

    double price() const override
    {
        return 11.99;
    }
};

class PepperoniPizza : public Pizza
{
public:
    string description() const override
    {
        return "Pepperoni Pizza";
    }

    double price() const override
    {
        return 12.99;
    }
};

// topping decorators
class ToppingDecorator : public Pizza
{
public:
    //explicit ToppingDecorator(unique_ptr<Pizza> pizza) : m_Pizza(move(pizza)) {};
    explicit ToppingDecorator(unique_ptr<Pizza> pizza) : m_Pizza(move(pizza)) {}
    // virtual ~ToppingDecorator() { delete m_Pizza; }

    virtual string description() const override
    {
        return m_Pizza->description();
    };

    virtual double price() const override
    {
        return m_Pizza->price();
    };   

private:
    unique_ptr<Pizza> m_Pizza;
};

class ExtraCheeseTopping : public ToppingDecorator
{
public:
    explicit ExtraCheeseTopping(unique_ptr<Pizza> pizza) : ToppingDecorator(move(pizza)) {}

    string description() const override
    {
        return ToppingDecorator::description() + ", Extra Cheese";
    }

    double price() const override
    {
        return ToppingDecorator::price() + 1.50;
    }

};

class OlivesTopping : public ToppingDecorator
{
public:
    explicit OlivesTopping(unique_ptr<Pizza> pizza) : ToppingDecorator(move(pizza)) {}

    string description() const override
    {
        return ToppingDecorator::description() + ", Olives";
    }

    double price() const override
    {
        return ToppingDecorator::price() + 1.75;
    }
};


class MushroomTopping : public ToppingDecorator
{
public:
    explicit MushroomTopping(unique_ptr<Pizza> pizza) : ToppingDecorator(move(pizza)) {}

    string description() const override
    {
        return ToppingDecorator::description() + ", Mushrooms";
    }

    double price() const override
    {
        return ToppingDecorator::price() + 1.05;
    }
};

int main()
{


    auto margheritaPizza = make_unique<MargheritaPizza>();
    auto margheritaWithMushrooms = make_unique<MushroomTopping>(move(margheritaPizza));

    // margheritaPizza is out of scope, set to 0x0
    // cout << margheritaPizza->description() << " costs $" << margheritaPizza->price() << endl;

    cout << margheritaWithMushrooms->description() << " costs $" << margheritaWithMushrooms->price() << endl;


    auto pepperoniPizza = make_unique<PepperoniPizza>();
    auto pepperoniPizzaWithOlives = make_unique<OlivesTopping>(move(pepperoniPizza));
    auto pepperoniPizzaWithOlivesWithExtraCheese = make_unique<ExtraCheeseTopping>(move(pepperoniPizzaWithOlives));

    cout << pepperoniPizzaWithOlivesWithExtraCheese->description() << " costs $" << pepperoniPizzaWithOlivesWithExtraCheese->price() << endl;

    return 0;
}
