#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameLogic.h"
#include <display/display.h>

class GameEngine {
 public:
    GameEngine();

    void MainCycle();

 private:
    Table table_;
    TDisplay display_;

    bool Change(EKey key);
    void Animate(const std::vector<std::vector<int32_t>>& coords);
    void Create();
};

#endif
