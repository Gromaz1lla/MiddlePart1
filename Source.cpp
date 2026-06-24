#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 1. Command
// Concept: allows turning an action (e.g., placing a block) into an object.
// This is necessary for implementing an undo system.
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class PlaceBlockCommand : public Command {
    std::string blockType;
public:
    PlaceBlockCommand(std::string type) : blockType(type) {}
    void execute() override { std::cout << "Block " << blockType << " placed.\n"; }
    void undo() override { std::cout << "Block " << blockType << " removed (Undo).\n"; }
};

// 2. STATE
// Concept: allows an object to change its behavior based on its internal state.
// In Minecraft, these are game modes (Survival, Creative).
class GameMode;
class Player {
    GameMode* state;
public:
    Player(GameMode* s);
    void setMode(GameMode* s);
    void handleAction();
};

class GameMode {
public:
    virtual void doAction(Player* p) = 0;
    virtual std::string getName() = 0;
};

class SurvivalMode : public GameMode {
public:
    void doAction(Player* p) override { std::cout << "Player is mining with limited health.\n"; }
    std::string getName() override { return "Survival"; }
};

class CreativeMode : public GameMode {
public:
    void doAction(Player* p) override { std::cout << "Player is flying and building instantly.\n"; }
    std::string getName() override { return "Creative"; }
};

Player::Player(GameMode* s) : state(s) {}
void Player::setMode(GameMode* s) { state = s; }
void Player::handleAction() { state->doAction(this); }

// 3. OBSERVER
// Concept: one object (the subject) notifies other objects (observers) of changes.
// In Minecraft, this is the achievement system: when a player performs an action, the achievement manager is notified.
class Observer {
public:
    virtual void update(std::string action) = 0;
};

class AchievementManager : public Observer {
public:
    void update(std::string action) override {
        if (action == "mine_diamond") std::cout << "Achievement Unlocked: DIAMONDS!\n";
    }
};

class Subject {
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* o) { observers.push_back(o); }
    void notify(std::string action) {
        for (auto o : observers) o->update(action);
    }
};

// 4. VISITOR
// Concept: allows adding new operations to classes without modifying their code.
// Example: a player (visitor) interacts with various blocks.
class Stone;
class Wood;

class BlockVisitor {
public:
    virtual void visit(Stone* s) = 0;
    virtual void visit(Wood* w) = 0;
};

class Block {
public:
    virtual void accept(BlockVisitor* v) = 0;
};

class Stone : public Block {
public:
    void accept(BlockVisitor* v) override { v->visit(this); }
};

class Wood : public Block {
public:
    void accept(BlockVisitor* v) override { v->visit(this); }
};

class PlayerInteraction : public BlockVisitor {
public:
    void visit(Stone* s) override { std::cout << "Mining stone: drops Cobblestone.\n"; }
    void visit(Wood* w) override { std::cout << "Chipping wood: drops Logs.\n"; }
};

// 5. Strategy
// Essence: allows changing the algorithm (method of action) on the fly.
// In Minecraft: different attack methods (sword or bow).
class AttackStrategy {
public:
    virtual void attack() = 0;
};

class SwordAttack : public AttackStrategy {
public:
    void attack() override { std::cout << "Attacking with Sword (Melee).\n"; }
};

class BowAttack : public AttackStrategy {
public:
    void attack() override { std::cout << "Attacking with Bow (Ranged).\n"; }
};

class CombatSystem {
    AttackStrategy* strategy;
public:
    void setStrategy(AttackStrategy* s) { strategy = s; }
    void performAttack() { strategy->attack(); }
};


int main() {
    // Command
    PlaceBlockCommand place("Dirt");
    place.execute();
    place.undo();

    // State
    SurvivalMode survival;
    CreativeMode creative;
    Player steve(&survival);
    steve.handleAction();
    steve.setMode(&creative);
    steve.handleAction();

    // OBSERVER
    Subject playerActions;
    AchievementManager achManager;
    playerActions.addObserver(&achManager);
    playerActions.notify("mine_diamond");

    // VISITOR
    Stone s; Wood w;
    PlayerInteraction interact;
    s.accept(&interact);
    w.accept(&interact);

    // Strategy
    SwordAttack sword;
    BowAttack bow;
    CombatSystem combat;
    combat.setStrategy(&sword);
    combat.performAttack();
    combat.setStrategy(&bow);
    combat.performAttack();

    return 0;
}