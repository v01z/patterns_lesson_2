//
// Created by bincat on 2022-03-25.
//

#ifndef LESSON_2_TASK3_H
#define LESSON_2_TASK3_H

class Beverage{            // Абстрактный класс
public:
    virtual std::string getDescription() const { return "Кофе "; };
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

class HouseBlend: public Beverage{   // Молотый
public:
    double cost() const override {
        return 5.5;
    }

    std::string getDescription() const override{
        return Beverage::getDescription() + "молотый:";
    }
};

class DarkRoast: public Beverage{  // Темной обжарки
public:
    double cost() const override {
        return 6.0;
    }

    std::string getDescription() const override{
        return Beverage::getDescription() + "тёмной обжарки:";
    }
};

class Decaf: public Beverage{    // Без кофеина
public:
    double cost() const override {
        return 7.3;
    }

    std::string getDescription() const override{
        return Beverage::getDescription() + "без кофеина:";
    }
};

class Espresso: public Beverage{  // Эспрессо
public:
    double cost() const override {
        return 3.5;
    }

    std::string getDescription()const override{
        return Beverage::getDescription() + "эспрессо:";
    }
};

class Decorator: public Beverage{
private:
    Beverage* _beverage;
public:
    Decorator(Beverage* beverage): _beverage { beverage } {}

    std::string getDescription() const override{
        return "Добавили ";
    }

    double cost() const override{
        return _beverage->cost();
    }
};

class ChocolateDecorator: public Decorator{
private:
    //Стоимость одной порции (ложки) какао
    static constexpr double chocolatePrice { 1.55 };

    //Число ложек с какао
    size_t spoonCount;

public:
    //Если не указать количество ложек с какао, то будем считать
    //их равным нулю
    ChocolateDecorator(Beverage* beverage, size_t spoonCount = 0):
        Decorator(beverage), spoonCount { spoonCount } {}

    std::string getDescription() const override{
        return Decorator::getDescription() + "шоколад:";
    }
    double cost() const override{
       return Decorator::cost() + spoonCount * chocolatePrice;
    }
};

class CinnamonDecorator: public Decorator{
private:
    static constexpr double cinnamonPrice { 0.47 };

    size_t spoonCount;

public:
    CinnamonDecorator(Beverage* beverage, size_t spoonCount = 0):
        Decorator(beverage), spoonCount { spoonCount } {}

    std::string getDescription() const override{
        return Decorator::getDescription() + "корицу:";
    }

    double cost() const override{
        return Decorator::cost() + spoonCount * cinnamonPrice;
    }
};

class ChantillyDecorator: public Decorator{
private:
    static constexpr double chantillyPrice { 0.53 };

    size_t spoonCount;

public:
    ChantillyDecorator(Beverage* beverage, size_t spoonCount = 0):
        Decorator(beverage), spoonCount { spoonCount } {}

    std::string getDescription() const override{
        return Decorator::getDescription() + "взбитые сливки:";
    }

    double cost() const override{
        return Decorator::cost() + spoonCount * chantillyPrice;
    }
};

class NoSugarDecorator: public Decorator{
private:
    static constexpr double sugarPrice { 0.37 };

public:
    NoSugarDecorator(Beverage* beverage): Decorator(beverage) {}

    std::string getDescription() const override{
        return "Удалили сахар:";
    }

    double cost() const override{
        return Decorator::cost() - sugarPrice;
    }
};


#endif //LESSON_2_TASK3_H
