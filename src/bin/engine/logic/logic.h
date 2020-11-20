#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <utility>
#include <cmath>

#include <display/display.h>

// from <display/display.h> we use only:
//
// enum class ETileType {
//     TILE_EMPTY,
//     TILE_2,
//     TILE_4,
//     TILE_8,
//     TILE_16,
//     TILE_32,
//     TILE_64,
//     TILE_128,
//     TILE_256,
//     TILE_512,
//     TILE_1024,
//     TILE_2048
// };
//
// enum class EKey {
//     KEY_UP,
//     KEY_DOWN,
//     KEY_LEFT,
//     KEY_RIGHT
// };

uint32_t RandomInRange(uint32_t first, uint32_t n);

class Table {
 public:
    Table();

    std::vector<std::vector<int32_t>> TableShift(EKey key, bool& changed);
    std::vector<std::vector<int32_t>> TableSumming(EKey key, bool& changed);
    std::pair<int32_t, int32_t> AddElement();
    ETileType GetTile(int32_t i, int32_t j) const;
    int32_t CountEmpty() const;
    bool NoMoves() const;

 private:
    std::vector<std::vector<ETileType>> matrix_;
};

#endif
