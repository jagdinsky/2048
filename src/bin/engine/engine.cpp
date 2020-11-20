#include "engine.h"

const uint32_t FRAMES = 200;
const float SPEED = 1.0 / FRAMES;

GameEngine::GameEngine() : table_(), display_() {
}

void GameEngine::MainCycle() {
    ETileType tile;

    EKey key;

    bool is_over;

    while (!display_.Closed()) {
        display_.ProcessEvents();
        for (int32_t i = 0; i < 4; i++) {
            for (int32_t j = 0; j < 4; j++) {
                tile = table_.GetTile(i, j);
                if (tile != ETileType::TILE_EMPTY) {
                    display_.DrawTile(i, j, tile);
                }
            }
        }
        display_.Render();

        bool is_pressed = true;
        if (display_.IsKeyPressed(EKey::KEY_UP)) {// table.is_posible(Ekey::KEY_UP)
            key = EKey::KEY_UP;
        } else if (display_.IsKeyPressed(EKey::KEY_DOWN)) {
            key = EKey::KEY_DOWN;
        } else if (display_.IsKeyPressed(EKey::KEY_LEFT)) {
            key = EKey::KEY_LEFT;
        } else if (display_.IsKeyPressed(EKey::KEY_RIGHT)) {
            key = EKey::KEY_RIGHT;
        } else {
            is_pressed = false;
        }

        if (is_pressed) {
            is_over = Change(key);
        }

        if (is_over) {
            display_.DrawWinMessage();
        }
    }
}

bool GameEngine::Change(EKey key) {
    std::vector<std::vector<int32_t>> coords_1, coords_2, coords_3;
    bool changed_1, changed_2, changed_3;

    coords_1 = table_.TableShift(key, changed_1);
    Animate(coords_1);

    coords_2 = table_.TableSumming(key, changed_2);
    Animate(coords_2);

    coords_3 = table_.TableShift(key, changed_3);
    Animate(coords_3);

    if (changed_1 || changed_2 || changed_3) {
        Create();
    }

    if (table_.NoMoves()) {
        return true;
    }
    return false;
}

void GameEngine::Animate(const std::vector<std::vector<int32_t>>& coords) {
    display_.ProcessEvents();

    std::vector<float> step_x(coords.size());
    std::vector<float> step_y(coords.size());
    for (int32_t j = 0; j < coords.size(); j++) {
        step_x[j] = (coords[j][2] - coords[j][0]) * SPEED;
        step_y[j] = (coords[j][3] - coords[j][1]) * SPEED;
    }

    std::vector<float> pos_x(coords.size());
    std::vector<float> pos_y(coords.size());
    for (int32_t j = 0; j < coords.size(); j++) {
        pos_x[j] = coords[j][0];
        pos_y[j] = coords[j][1];
    }

    for (int32_t i = 0; i < FRAMES; i++) {
        for (int32_t j = 0; j < coords.size(); j++) {
            display_.DrawTile(pos_x[j], pos_y[j],
                                    table_.GetTile(coords[j][2], coords[j][3]));
            pos_x[j] += step_x[j];
            pos_y[j] += step_y[j];
        }
        display_.Render();
    }
}

void GameEngine::Create() {
    if (table_.CountEmpty() == 0) {
        return;
    }

    std::pair<int32_t, int32_t> the_pair = table_.AddElement();
    ETileType tile;

    for (float transparency = 0.00; transparency < 1.0; transparency += 0.01) {
        display_.ProcessEvents();
        for (int32_t i = 0; i < 4; i++) {
            for (int32_t j = 0; j < 4; j++) {
                tile = table_.GetTile(i, j);
                if (i == the_pair.first && j == the_pair.second) {
                    display_.DrawTile(i, j, tile, transparency);
                    continue;
                }
                if (tile != ETileType::TILE_EMPTY) {
                    display_.DrawTile(i, j, tile);
                }
            }
        }
        display_.Render();
    }
}
