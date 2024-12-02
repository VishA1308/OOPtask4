#include <iostream>
#include <vector>

// Абстрактный класс GenericCreature
class GenericCreature {
public:
    virtual void eat() = 0; // Чистая виртуальная функция
    virtual ~GenericCreature() {} // Виртуальный деструктор
};

// Класс OceanCreature, наследник GenericCreature
class OceanCreature : public GenericCreature {
public:
    void eat() override {
        std::cout << "OceanCreature: Eating seaweed." << std::endl;
    }

    void swim() {
        std::cout << "OceanCreature: Swimming." << std::endl;
    }
};

// Класс Amphibious, наследник OceanCreature
class Amphibious : public OceanCreature {
public:
    void eat() override {
        std::cout << "Amphibious: Eating plants and small fish." << std::endl;
    }

    void walk() {
        std::cout << "Amphibious: Walking on land." << std::endl;
    }
};

// Класс TerrestrialCreature, наследник GenericCreature
class TerrestrialCreature : public GenericCreature {
public:
    void eat() override {
        std::cout << "TerrestrialCreature: Eating grass and plants." << std::endl;
    }

    void walk() {
        std::cout << "TerrestrialCreature: Walking on land." << std::endl;
    }
};

// Класс Bird, наследник TerrestrialCreature
class Bird : public TerrestrialCreature {
public:
    void eat() override {
        std::cout << "Bird: Eating seeds and insects." << std::endl;
    }

    void fly() {
        std::cout << "Bird: Flying." << std::endl;
    }
};

// Класс Waterfowl, наследник Bird
class Waterfowl : public Bird {
public:
    void eat() override {
        std::cout << "Waterfowl: Eating aquatic plants and small fish." << std::endl;
    }

    void swim() {
        std::cout << "Waterfowl: Swimming." << std::endl;
    }
};

int main() {

    std::vector<GenericCreature*> creatures;

    // Добавляем объекты разных классов в массив
    creatures.push_back(new OceanCreature());
    creatures.push_back(new Amphibious());
    creatures.push_back(new TerrestrialCreature());
    creatures.push_back(new Bird());
    creatures.push_back(new Waterfowl());

    // Полиморфное поведение: вызываем метод eat() для каждого объекта
    std::cout << "Demonstrating polymorphic behavior:" << std::endl;
    for (auto creature : creatures) {
        creature->eat(); // Вызываем полиморфный метод
    }

    // Не полиморфное поведение: вызов специфических методов
    std::cout << "\nDemonstrating non-polymorphic behavior:" << std::endl;

    // Проверяем типы объектов и вызываем специфические методы
    for (auto creature : creatures) {
        if (Waterfowl* wf = dynamic_cast<Waterfowl*>(creature)) {
            wf->walk();
            wf->fly();
            wf->swim();
        }
        else if (Bird* b = dynamic_cast<Bird*>(creature)) {
            b->walk();
            b->fly();
        }
        else if (Amphibious* a = dynamic_cast<Amphibious*>(creature)) {
            a->walk();
            a->swim();
        }
        else if (OceanCreature* oc = dynamic_cast<OceanCreature*>(creature)) {
            oc->swim();
        }
        else if (TerrestrialCreature* tc = dynamic_cast<TerrestrialCreature*>(creature)) {
            tc->walk();
        }
    }

    // Освобождаем память
    for (auto creature : creatures) {
        delete creature;
    }

    return 0;
}
