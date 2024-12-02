#include <iostream>
#include <string>

class GenericCreature {
public:
    GenericCreature() {
        std::cout << "GenericCreature: Constructor called." << std::endl;
    }

    ~GenericCreature() {
        std::cout << "GenericCreature: Destructor called." << std::endl;
    }
};

class OceanCreature : public GenericCreature {
public:
    OceanCreature() {
        std::cout << "OceanCreature: Constructor called." << std::endl;
    }

    ~OceanCreature() {
        std::cout << "OceanCreature: Destructor called." << std::endl;
    }

    void swim() {
        std::cout << "OceanCreature: Swimming." << std::endl;
    }
};

class Amphibious : public OceanCreature {
public:
    Amphibious() {
        std::cout << "Amphibious: Constructor called." << std::endl;
    }

    ~Amphibious() {
        std::cout << "Amphibious: Destructor called." << std::endl;
    }

    void walk() {
        std::cout << "Amphibious: Walking." << std::endl;
    }
};

class TerrestrialCreature : public Amphibious {
public:
    TerrestrialCreature() {
        std::cout << "TerrestrialCreature: Constructor called." << std::endl;
    }

    ~TerrestrialCreature() {
        std::cout << "TerrestrialCreature: Destructor called." << std::endl;
    }
private:
    using Amphibious::swim;
};

class Bird : public TerrestrialCreature {
public:
    Bird() {
        std::cout << "Bird: Constructor called." << std::endl;
    }

    ~Bird() {
        std::cout << "Bird: Destructor called." << std::endl;
    }

    void fly() {
        std::cout << "Bird: Flying." << std::endl;
    }
};

class Waterfowl : public Bird {
public:
    Waterfowl() {
        std::cout << "Waterfowl: Constructor called." << std::endl;
    }

    ~Waterfowl() {
        std::cout << "Waterfowl: Destructor called." << std::endl;
    }
    using Amphibious::swim;
    
};

int main() {
    std::cout << "Creating a Waterfowl object:" << std::endl;
    Waterfowl duck;
    duck.walk(); // Из класса Bird (через TerrestrialCreature)
    duck.fly(); // Из класса Bird
    duck.swim(); // Из класса OceanCreature

    return 0;
}
