//
// Created by bincat on 2022-03-24.
//

#ifndef LESSON_2_TASK1_H
#define LESSON_2_TASK1_H

class Pizza{
public:

    virtual void prepare(const std::string &type) const {
        std::cout << "Готовится пицца \'" << type << "\'.\n";
    };

    virtual void bake() {};
    virtual void cut() {};
    virtual void box() {};

    virtual ~Pizza(){};
};

class CheesePizza:public Pizza{};
class GreekPizza:public Pizza{};
class PepperoniPizza:public Pizza{};



class PizzaFactory{
public:
    virtual Pizza* createPizza() = 0;
    virtual ~PizzaFactory(){};
};

class CheesePizzaFactory: public PizzaFactory{
public:
    Pizza* createPizza() override{
        return new CheesePizza;
    }
};

class GreekPizzaFactory: public PizzaFactory{
public:
    Pizza* createPizza() override{
        return new GreekPizza;
    }
};

class PepperoniPizzaFactory: public PizzaFactory{
public:
    Pizza* createPizza() override{
        return new PepperoniPizza;
    }
};

Pizza* orderPizza(const std::string &type){
    Pizza* pizza { nullptr };
    PizzaFactory* factory { nullptr };

    if (type == "cheese"){
        factory = new CheesePizzaFactory;
    }
    else if (type == "greek"){
        factory = new GreekPizzaFactory;
    }
    else if (type == "pepperoni"){
        factory = new PepperoniPizzaFactory;
    }
    else
    {
        std::cout << "Такой пиццы нет в пиццерии.\n";
        return pizza; //Вернём nullptr
    }

    pizza = factory->createPizza();
    pizza->prepare(type);

    delete factory;
    return pizza;
}

#endif //LESSON_2_TASK1_H
