//
// Created by bcat on 2022-03-25.
//

#ifndef LESSON_2_TASK2_H
#define LESSON_2_TASK2_H

#include <vector>
#include <map>

enum class Colors {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    WHITE
};

class Light{
public:
    Light():state(false), color(Colors::WHITE){};

    void On(){
        if(!state){
            state = true;
        }
    };

    void Off(){
        if(state){
            state = false;
        }
    };

    void changeColor(Colors newColor){
        color = newColor;
    }

    bool getState() const {
        return state;
    }

    //Для удобства
    Colors getColor() const{
        return color;
    }

private:
    bool state;
    Colors color;
};

class Command{
protected:
    Light *light;
    Command(Light *light): light { light } {};
public:
    virtual ~Command(){};

    virtual void Execute() = 0;
};

class OnCommand: public Command{
public:
    OnCommand(Light *light): Command(light) {}

    void Execute() override{
        light->On();
    }
};

class OffCommand: public Command{
public:
    OffCommand(Light* light): Command(light) {}

    void Execute() override{
        light->Off();
    }
};

class ChangeColorCommand: public Command{
private:
    Colors color;
public:
    ChangeColorCommand(Light *light, Colors color):
        Command(light), color { color } {}

    void Execute() override{
        light->changeColor(color);
    }
};

class Invoker{
private:
    std::vector<Command*> _cmds;
    Light *light;

    //Для цветного вывода
    static const std::map<Colors, std::string> colorMap;

public:

    Invoker(Light *light): light { light } {}

    void Add(Command *cmd){
        _cmds.push_back(cmd);
    }

    //Можно не прописывать словами значение Light::color, цветной
    //вывод в терминал покажет это более наглядно
    void PrintLightStatus(){
        std::cout << (light->getState()?
        colorMap.at(light->getColor()) + "горит":"не горит");
        std::cout << colorMap.at(Colors::WHITE) << std::endl;
    }

    void ExecForward() {
        if (_cmds.size() == 0)
        {
            std::cout << "There are no command yet.\n";
            return;
        }

       for (Command *ptrCmd: _cmds)
       {
           ptrCmd->Execute();

           PrintLightStatus();
       }
    }

    void ExecBack() {
        if (_cmds.size() == 0)
        {
            std::cout << "There are no command yet.\n";
            return;
        }

        for (auto it { _cmds.rbegin() }; it != _cmds.rend(); ++it)
        {
            (*it)->Execute();

            PrintLightStatus();
        }
    }

    ~Invoker(){
        for (const Command *ptrCmd: _cmds)
            delete ptrCmd;
    }
};

const std::map<Colors, std::string> Invoker::colorMap =
                   { { Colors::RED, "\x1B[31m" },
                   { Colors::ORANGE, "\x1B[33m" },
                   { Colors::YELLOW, "\x1B[93m" },
                   { Colors::GREEN, "\x1B[32m" },
                   { Colors::CYAN, "\x1B[36m" },
                   { Colors::BLUE, "\x1B[34m" },
                   { Colors::VIOLET, "\x1B[35m" },
                   { Colors::WHITE, "\x1B[0m"} };

#endif //LESSON_2_TASK2_H
