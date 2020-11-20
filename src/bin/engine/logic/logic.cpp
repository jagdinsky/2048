#include "logic.h"

const int32_t SIZE = 4;

int32_t RandomInRange(int32_t first, int32_t n) {
    return first + rand() % (n - first);
}

Table::Table() : matrix_(SIZE,
                        std::vector<ETileType>(SIZE, ETileType::TILE_EMPTY)) {
    AddElement();
    AddElement();
}

std::vector<std::vector<int32_t>> Table::TableShift(EKey key, bool& changed) {
    changed = false;
    std::vector<std::vector<int32_t>> coords;
    if (key == EKey::KEY_UP) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = 0; j < SIZE - 1; j++) {
                if (matrix_[j][i] == ETileType::TILE_EMPTY) {
                    for (int32_t k = j + 1; k < SIZE; k++) {
                        if (matrix_[k][i] != ETileType::TILE_EMPTY) {
                            changed = true;
                            matrix_[j][i] = matrix_[k][i];
                            matrix_[k][i] = ETileType::TILE_EMPTY;
                            coords.push_back(std::vector<int32_t>{k, i, j, i});
                            break;
                        }
                    }
                } else {
                    coords.push_back(std::vector<int32_t>{j, i, j, i});
                }
            }
            if (matrix_[SIZE - 1][i] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{SIZE - 1, i, SIZE - 1,
                                                                        i});
            }
        }
    } else if (key == EKey::KEY_DOWN) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = SIZE - 1; j > 0; j--) {
                if (matrix_[j][i] == ETileType::TILE_EMPTY) {
                    for (int32_t k = j - 1; k >= 0; k--) {
                        if (matrix_[k][i] != ETileType::TILE_EMPTY) {
                            changed = true;
                            matrix_[j][i] = matrix_[k][i];
                            matrix_[k][i] = ETileType::TILE_EMPTY;
                            coords.push_back(std::vector<int32_t>{k, i, j, i});
                            break;
                        }
                    }
                } else {
                    coords.push_back(std::vector<int32_t>{j, i, j, i});
                }
            }
            if (matrix_[0][i] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{0, i, 0, i});
            }
        }
    } else if (key == EKey::KEY_LEFT) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = 0; j < SIZE - 1; j++) {
                if (matrix_[i][j] == ETileType::TILE_EMPTY) {
                    for (int32_t k = j + 1; k < SIZE; k++) {
                        if (matrix_[i][k] != ETileType::TILE_EMPTY) {
                            changed = true;
                            matrix_[i][j] = matrix_[i][k];
                            matrix_[i][k] = ETileType::TILE_EMPTY;
                            coords.push_back(std::vector<int32_t>{i, k, i, j});
                            break;
                        }
                    }
                } else {
                    coords.push_back(std::vector<int32_t>{i, j, i, j});
                }
            }
            if (matrix_[i][SIZE - 1] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{i, SIZE - 1, i,
                                                                    SIZE - 1});
            }
        }
    } else if (key == EKey::KEY_RIGHT) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = SIZE - 1; j > 0; j--) {
                if (matrix_[i][j] == ETileType::TILE_EMPTY) {
                    for (int32_t k = j - 1; k >= 0; k--) {
                        if (matrix_[i][k] != ETileType::TILE_EMPTY) {
                            changed = true;
                            matrix_[i][j] = matrix_[i][k];
                            matrix_[i][k] = ETileType::TILE_EMPTY;
                            coords.push_back(std::vector<int32_t>{i, k, i, j});
                            break;
                        }
                    }
                } else {
                    coords.push_back(std::vector<int32_t>{i, j, i, j});
                }
            }
            if (matrix_[i][0] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{i, 0, i, 0});
            }
        }
    }
    return coords;
}

// (0, 0) (0, 1) (0, 2) (0, 3)
// (1, 0) (1, 1) (1, 2) (1, 3)
// (2, 0) (2, 1) (2, 2) (2, 3)
// (3, 0) (3, 1) (3, 2) (3, 3)

std::vector<std::vector<int32_t>> Table::TableSumming(EKey key, bool& changed) {
    changed = false;
    std::vector<std::vector<int32_t>> coords;
    if (key == EKey::KEY_UP) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = 0; j < SIZE - 1; j++) {
                if (matrix_[j][i] != ETileType::TILE_EMPTY) {
                    if (matrix_[j][i] == matrix_[j + 1][i]) {
                        changed = true;
                        // matrix_[j][i]++
                        matrix_[j][i] = static_cast<ETileType>(
                                    static_cast<int32_t>(matrix_[j][i]) + 1);
                        matrix_[j + 1][i] = ETileType::TILE_EMPTY;
                        coords.push_back(std::vector<int32_t>{j + 1, i, j, i});
                    } else {
                        coords.push_back(std::vector<int32_t>{j, i, j, i});
                    }
                }
            }
            if (matrix_[SIZE - 1][i] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{SIZE - 1, i, SIZE - 1,
                                                                        i});
            }
        }
    } else if (key == EKey::KEY_DOWN) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = SIZE - 1; j > 0; j--) {
                if (matrix_[j][i] != ETileType::TILE_EMPTY) {
                    if (matrix_[j][i] == matrix_[j - 1][i]) {
                        changed = true;
                        // matrix_[j][i]++;
                        matrix_[j][i] = static_cast<ETileType>(
                                    static_cast<int32_t>(matrix_[j][i]) + 1);
                        matrix_[j - 1][i] = ETileType::TILE_EMPTY;
                        coords.push_back(std::vector<int32_t>{j - 1, i, j, i});
                    } else {
                        coords.push_back(std::vector<int32_t>{j, i, j, i});
                    }
                }
            }
            if (matrix_[0][i] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{0, i, 0, i});
            }
        }
    } else if (key == EKey::KEY_LEFT) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = 0; j < SIZE - 1; j++) {
                if (matrix_[i][j] != ETileType::TILE_EMPTY) {
                    if (matrix_[i][j] == matrix_[i][j + 1]) {
                        changed = true;
                        // matrix_[i][j]++;
                        matrix_[i][j] = static_cast<ETileType>(
                                    static_cast<int32_t>(matrix_[i][j]) + 1);
                        matrix_[i][j + 1] = ETileType::TILE_EMPTY;
                        coords.push_back(std::vector<int32_t>{i, j + 1, i, j});
                    } else {
                        coords.push_back(std::vector<int32_t>{i, j, i, j});
                    }
                }
            }
            if (matrix_[i][SIZE - 1] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{i, SIZE - 1, i,
                                                                    SIZE - 1});
            }
        }
    } else if (key == EKey::KEY_RIGHT) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = SIZE - 1; j > 0; j--) {
                if (matrix_[i][j] != ETileType::TILE_EMPTY) {
                    if (matrix_[i][j] == matrix_[i][j - 1]) {
                        changed = true;
                        // matrix_[i][j]++;
                        matrix_[i][j] = static_cast<ETileType>(
                                    static_cast<int32_t>(matrix_[i][j]) + 1);
                        matrix_[i][j - 1] = ETileType::TILE_EMPTY;
                        coords.push_back(std::vector<int32_t>{i, j - 1, i, j});
                    } else {
                        coords.push_back(std::vector<int32_t>{i, j, i, j});
                    }
                }
            }
            if (matrix_[i][0] != ETileType::TILE_EMPTY) {
                coords.push_back(std::vector<int32_t>{i, 0, i, 0});
            }
        }
    }
    return coords;
}

std::pair<int32_t, int32_t> Table::AddElement() {
    int32_t counter = 1, random = RandomInRange(1, CountEmpty() + 1);
    for (int32_t i = 0; i < SIZE; i++) {
        for (int32_t j = 0; j < SIZE; j++) {
            if (matrix_[i][j] == ETileType::TILE_EMPTY) {
                if (counter == random) {
                    if (rand() % 10 != 9) {
                        matrix_[i][j] = ETileType::TILE_2;
                    } else {
                        matrix_[i][j] = ETileType::TILE_4;
                    }
                    return std::make_pair(i, j);
                }
                counter++;
            }
        }
    }
}

ETileType Table::GetTile(int32_t i, int32_t j) const {
    return matrix_[i][j];
}

int32_t Table::CountEmpty() const {
    int32_t counter = 0;
    for (int32_t i = 0; i < SIZE; i++) {
        for (int32_t j = 0; j < SIZE; j++) {
            if (matrix_[i][j] == ETileType::TILE_EMPTY) {
                counter++;
            }
        }
    }
    return counter;
}

bool Table::NoMoves() const {
    for (uint32_t i = 0; i < SIZE; i++) {
        for (uint32_t j = 0; j < SIZE - 1; j++) {
            if (matrix_[i][j] == matrix_[i][j + 1]) {
                return false;
            }
        }
    }
    for (uint32_t i = 0; i < SIZE; i++) {
        for (uint32_t j = 0; j < SIZE - 1; j++) {
            if (matrix_[j][i] == matrix_[j + 1][i]) {
                return false;
            }
        }
    }
    if (CountEmpty() != 0) {
        return false;
    }
    return true;
}
