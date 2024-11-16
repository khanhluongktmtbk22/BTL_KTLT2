#include "knight2.h"

int main(int argc, char** argv) {
    // BEBGIN
    KnightAdventure* knightAdventure=new KnightAdventure;
    knightAdventure->loadArmyKnights("tc1_armyknights.txt");
    knightAdventure->loadEvents("tc1_events.txt");
    knightAdventure->run();
    
    delete knightAdventure;

    return 0;
}
