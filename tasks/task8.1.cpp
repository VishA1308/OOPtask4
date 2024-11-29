#include <iostream> 
#include <string> 

class GenericCreature {
public:
    GenericCreature() {
        std::cout << "GenericCreature: Constructor called." << std::endl;
    }

    virtual ~GenericCreature() {
        std::cout << "GenericCreature: Destructor called." << std::endl;
    }

    void breathe() {
        std::cout << "GenericCreature: Breathing." << std::endl;
    }
};

class OceanCreature : virtual public GenericCreature {
public:
    OceanCreature() {
        std::cout << "OceanCreature: Constructor called." << std::endl;
    }

    virtual ~OceanCreature() {
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

class TerrestrialCreature : virtual public GenericCreature {
public:
    TerrestrialCreature() {
        std::cout << "TerrestrialCreature: Constructor called." << std::endl;
    }

    virtual ~TerrestrialCreature() {
        std::cout << "TerrestrialCreature: Destructor called." << std::endl;
    }

    void walk() {
        std::cout << "TerrestrialCreature: Walking." << std::endl;
    }
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

class Waterfowl : public Bird, public OceanCreature {
public:
    Waterfowl() {
        std::cout << "Waterfowl: Constructor called." << std::endl;
    }

    ~Waterfowl() {
        std::cout << "Waterfowl: Destructor called." << std::endl;
    }

    void swim() {
        std::cout << "Waterfowl: Swimming." << std::endl;
    }
};

int main() {
    std::cout << "Creating a Waterfowl object:" << std::endl;
    Waterfowl duck;

    duck.breathe();
    duck.walk();
    duck.fly();
    duck.swim();

    return 0;
}
