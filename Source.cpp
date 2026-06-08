#include <iostream>
#include <vector>
#include <string>

class MinecraftSave {
private:
    static MinecraftSave* instance;
    std::string dim;
    MinecraftSave() : dim("Overworld") {}
public:
    static MinecraftSave* getInstance() {
        if (!instance) instance = new MinecraftSave();
        return instance;
    }
    void setDim(std::string d) { dim = d; }
    void printDim() { std::cout << dim << std::endl; }
};
MinecraftSave* MinecraftSave::instance = nullptr;

class Mob {
public:
    virtual Mob* clone() = 0;
    virtual void spawn() = 0;
    virtual ~Mob() {}
};

class Zombie : public Mob {
public:
    Mob* clone() override { return new Zombie(*this); }
    void spawn() override { std::cout << "Zombie spawned" << std::endl; }
};

class VillageStructure {
public:
    std::vector<std::string> parts;
    void show() {
        for (size_t i = 0; i < parts.size(); ++i) {
            std::cout << parts[i] << (i == parts.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }
};

class VillageBuilder {
private:
    VillageStructure* s;
public:
    VillageBuilder() { s = new VillageStructure(); }
    void addWalls() { s->parts.push_back("StoneWalls"); }
    void addWorkstation() { s->parts.push_back("BrewingStand"); }
    VillageStructure* getResult() { return s; }
};

class Block { public: virtual void place() = 0; };
class BiomeMob { public: virtual void action() = 0; };

                       class Sand : public Block { void place() override { std::cout << "Sand Block" << std::endl; } };
                       class Husk : public BiomeMob { void action() override { std::cout << "Husk Growl" << std::endl; } };

                       class BiomeFactory {
                       public:
                           virtual Block* createBlock() = 0;
                           virtual BiomeMob* createMob() = 0;
                       };

                       class DesertFactory : public BiomeFactory {
                       public:
                           Block* createBlock() override { return new Sand(); }
                           BiomeMob* createMob() override { return new Husk(); }
                       };

                       int main() {
                           MinecraftSave* save = MinecraftSave::getInstance();
                           save->printDim();

                           save->setDim("Nether");

                           Zombie proto;
                           Mob* z = proto.clone();
                           z->spawn();

                           VillageBuilder builder;
                           builder.addWalls();
                           builder.addWorkstation();
                           VillageStructure* house = builder.getResult();
                           house->show();

                           BiomeFactory* factory = new DesertFactory();
                           Block* b = factory->createBlock();
                           BiomeMob* m = factory->createMob();
                           b->place();
                           m->action();

                           delete z; delete house; delete b; delete m; delete factory;
                           return 0;
                       }