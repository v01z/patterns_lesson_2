#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"

int main() {
    // ****************** task 1 ************************

    //Закажем пиццу 'Пепперони'
    Pizza *pizza { orderPizza("pepperoni") };

    //Если пицца существует, то её можно съесть
    if (pizza != nullptr)
        delete pizza;

    // ****************** task 2 ************************

    Light *light { new Light };

    //Произвольный набор команд
    std::vector<Command *> lightCommands
        {
          new ChangeColorCommand { light, Colors::CYAN },
          new OnCommand { light },
          new ChangeColorCommand { light, Colors::RED },
          new ChangeColorCommand { light, Colors::GREEN },
          new ChangeColorCommand { light, Colors::BLUE },
          new OffCommand { light },
          new OnCommand { light },
          new ChangeColorCommand { light, Colors::YELLOW}
        };

    Invoker invoker { light };
    for (const auto &cmd : lightCommands)
        invoker.Add(cmd);


    std::cout << "\n****** Вперёд ******\n";
    invoker.ExecForward();

    std::cout << "\n****** Назад ******\n";
    invoker.ExecBack();

    delete light;

    // ****************** task 3 ************************

    //Лямбда для удобства вывода инфы
    auto infoLambda { [] (const Beverage *beverage) {
       std::cout << beverage->getDescription() << std::endl;
       std::cout << "Стоимость: ";
       std::cout << beverage->cost() << '.' << std::endl;
    }};

    Beverage *espresso= new Espresso;

    //Стоимость дефолтной чашки эспрессо
    infoLambda(espresso);

    //Сделаем эспрессо с ложкой какао (так вообще делают?):
    Beverage *espressoWithChocolate { new ChocolateDecorator (espresso, 1) };

    //И эта чашка будет стоить:
    infoLambda(espressoWithChocolate);

    //Добавим туда ложку корицы
    Beverage *espressoWithChocolateAndWithCinnamon
        { new CinnamonDecorator (espressoWithChocolate, 1) };

    //Теперь цена возросла до:
    infoLambda(espressoWithChocolateAndWithCinnamon);

    //Ложку со взитыми сливками туда же
    Beverage *espressoWithChocolateWithCinnamonAndWithChantilly
        { new ChantillyDecorator (espressoWithChocolateAndWithCinnamon, 1) };

    //Итоговая цена:
    infoLambda(espressoWithChocolateWithCinnamonAndWithChantilly);

    //Получилось дорого, поэтому не будем ложить сахар
    Beverage *espressoWithChocolateWithCinnamonWithChantillyNoSugar
        { new NoSugarDecorator (espressoWithChocolateWithCinnamonAndWithChantilly) };

    //Окончательная цена всех устроила
    infoLambda(espressoWithChocolateWithCinnamonWithChantillyNoSugar);

    delete espressoWithChocolateWithCinnamonWithChantillyNoSugar;
    delete espressoWithChocolateWithCinnamonAndWithChantilly;
    delete espressoWithChocolateAndWithCinnamon;
    delete espressoWithChocolate;
    delete espresso;

    return 0;
}
