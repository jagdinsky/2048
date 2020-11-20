#ifndef ENGINE_H
#define ENGINE_H

#include "logic/logic.h"
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
