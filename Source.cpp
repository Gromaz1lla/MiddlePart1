#include <iostream>
#include <vector>
#include <string>
#include <map>

// pattern Adapter
class OldRedstoneSystem {
public:
    int getSignal() { return 15; }
};

class NewPowerSystem {
public:
    virtual double getVoltage() = 0;
};

class RedstoneAdapter : public NewPowerSystem {
private:
    OldRedstoneSystem* oldSystem;
public:
    RedstoneAdapter(OldRedstoneSystem* s) : oldSystem(s) {}
    double getVoltage() override { return (double)oldSystem->getSignal() * 0.8; }
};

// pattern Facade
class FuelSystem {
public:
    bool hasCoal() { return true; }
};

class TemperatureSystem {
public:
    void heatUp() { std::cout << "Furnace is hot" << std::endl; }
};

class FurnaceFacade {
private:
    FuelSystem fuel;
    TemperatureSystem temp;
public:
    void smelt() {
        if (fuel.hasCoal()) {
            temp.heatUp();
            std::cout << "Item smelted" << std::endl;
        }
    }
};

// pattern Proxy
class IChest {
public:
    virtual void open() = 0;
};

class RealChest : public IChest {
public:
    void open() override { std::cout << "Chest opened" << std::endl; }
};

class ChestProxy : public IChest {
private:
    RealChest* chest;
    bool isOp;
public:
    ChestProxy(bool op) : isOp(op) { chest = new RealChest(); }
    void open() override {
        if (isOp) chest->open();
        else std::cout << "Access denied" << std::endl;
    }
    ~ChestProxy() { delete chest; }
};

// pattern Composite
class WorldObject {
public:
    virtual void render() = 0;
};

class Block : public WorldObject {
private:
    std::string name;
public:
    Block(std::string n) : name(n) {}
    void render() override { std::cout << name << " "; }
};

class Structure : public WorldObject {
private:
    std::vector<WorldObject*> objects;
public:
    void add(WorldObject* obj) { objects.push_back(obj); }
    void render() override {
        for (auto obj : objects) obj->render();
    }
};

// pattern Bridge
class Material {
public:
    virtual std::string getProp() = 0;
};

class Diamond : public Material {
    std::string getProp() override { return "Diamond"; }
};

class Tool {
protected:
    Material* mat;
public:
    Tool(Material* m) : mat(m) {}
    virtual void info() = 0;
};

class Pickaxe : public Tool {
public:
    Pickaxe(Material* m) : Tool(m) {}
    void info() override { std::cout << mat->getProp() << " Pickaxe" << std::endl; }
};

// pattern Flyweight
class BlockType {
public:
    std::string texture;
    BlockType(std::string t) : texture(t) {}
};

class BlockFactory {
private:
    std::map<std::string, BlockType*> types;
public:
    BlockType* getType(std::string t) {
        if (types.find(t) == types.end()) types[t] = new BlockType(t);
        return types[t];
    }
};

int main() {
    // Adapter
    OldRedstoneSystem oldS;
    RedstoneAdapter adapter(&oldS);
    std::cout << "Voltage: " << adapter.getVoltage() << std::endl;

    // Facade
    FurnaceFacade furnace;
    furnace.smelt();

    // Proxy
    ChestProxy badProxy(false);
    badProxy.open();
    ChestProxy goodProxy(true);
    goodProxy.open();

    // Composite
    Structure house;
    house.add(new Block("Wall"));
    house.add(new Block("Door"));
    house.render();
    std::cout << std::endl;

    // Bridge
    Diamond dia;
    Pickaxe pick(&dia);
    pick.info();

    // Flyweight
    BlockFactory factory;
    BlockType* t1 = factory.getType("GrassTexture");
    std::cout << "Texture: " << t1->texture << std::endl;

    return 0;
}