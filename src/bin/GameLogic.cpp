#include "GameLogic.h"

int32_t random_in_range(int32_t first, int32_t n) {
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
                            std::vector<int32_t> v(4);
                            v[0] = k;
                            v[1] = i;
                            v[2] = j;
                            v[3] = i;
                            coords.push_back(v);
                            break;
                        }
                    }
                } else {
                    std::vector<int32_t> v(4);
                    v[0] = j;
                    v[1] = i;
                    v[2] = j;
                    v[3] = i;
                    coords.push_back(v);
                }
            }
            if (matrix_[SIZE - 1][i] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = SIZE - 1;
                v[1] = i;
                v[2] = SIZE - 1;
                v[3] = i;
                coords.push_back(v);
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
                            std::vector<int32_t> v(4);
                            v[0] = k;
                            v[1] = i;
                            v[2] = j;
                            v[3] = i;
                            coords.push_back(v);
                            break;
                        }
                    }
                } else {
                    std::vector<int32_t> v(4);
                    v[0] = j;
                    v[1] = i;
                    v[2] = j;
                    v[3] = i;
                    coords.push_back(v);
                }
            }
            if (matrix_[0][i] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = 0;
                v[1] = i;
                v[2] = 0;
                v[3] = i;
                coords.push_back(v);
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
                            std::vector<int32_t> v(4);
                            v[0] = i;
                            v[1] = k;
                            v[2] = i;
                            v[3] = j;
                            coords.push_back(v);
                            break;
                        }
                    }
                } else {
                    std::vector<int32_t> v(4);
                    v[0] = i;
                    v[1] = j;
                    v[2] = i;
                    v[3] = j;
                    coords.push_back(v);
                }
            }
            if (matrix_[i][SIZE - 1] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = i;
                v[1] = SIZE - 1;
                v[2] = i;
                v[3] = SIZE - 1;
                coords.push_back(v);
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
                            std::vector<int32_t> v(4);
                            v[0] = i;
                            v[1] = k;
                            v[2] = i;
                            v[3] = j;
                            coords.push_back(v);
                            break;
                        }
                    }
                } else {
                    std::vector<int32_t> v(4);
                    v[0] = i;
                    v[1] = j;
                    v[2] = i;
                    v[3] = j;
                    coords.push_back(v);
                }
            }
            if (matrix_[i][0] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = i;
                v[1] = 0;
                v[2] = i;
                v[3] = 0;
                coords.push_back(v);
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
                    std::vector<int32_t> v(4);
                    if (matrix_[j][i] == matrix_[j + 1][i]) {
                        changed = true;
                        // matrix_[j][i]++
                        matrix_[j][i] =
                    static_cast<ETileType>(static_cast<int32_t>(matrix_[j][i]) + 1);
                        matrix_[j + 1][i] = ETileType::TILE_EMPTY;
                        v[0] = j + 1;
                        v[1] = i;
                        v[2] = j;
                        v[3] = i;
                    } else {
                        v[0] = j;
                        v[1] = i;
                        v[2] = j;
                        v[3] = i;
                    }
                    coords.push_back(v);
                }
            }
            if (matrix_[SIZE - 1][i] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = SIZE - 1;
                v[1] = i;
                v[2] = SIZE - 1;
                v[3] = i;
                coords.push_back(v);
            }
        }
    } else if (key == EKey::KEY_DOWN) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = SIZE - 1; j > 0; j--) {
                if (matrix_[j][i] != ETileType::TILE_EMPTY) {
                    std::vector<int32_t> v(4);
                    if (matrix_[j][i] == matrix_[j - 1][i]) {
                        changed = true;
                        // matrix_[j][i]++;
                        matrix_[j][i] =
                    static_cast<ETileType>(static_cast<int32_t>(matrix_[j][i]) + 1);
                        matrix_[j - 1][i] = ETileType::TILE_EMPTY;
                        v[0] = j - 1;
                        v[1] = i;
                        v[2] = j;
                        v[3] = i;
                    } else {
                        v[0] = j;
                        v[1] = i;
                        v[2] = j;
                        v[3] = i;
                    }
                    coords.push_back(v);
                }
            }
            if (matrix_[0][i] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = 0;
                v[1] = i;
                v[2] = 0;
                v[3] = i;
                coords.push_back(v);
            }
        }
    } else if (key == EKey::KEY_LEFT) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = 0; j < SIZE - 1; j++) {
                if (matrix_[i][j] != ETileType::TILE_EMPTY) {
                    std::vector<int32_t> v(4);
                    if (matrix_[i][j] == matrix_[i][j + 1]) {
                        changed = true;
                        // matrix_[i][j]++;
                        matrix_[i][j] =
                    static_cast<ETileType>(static_cast<int32_t>(matrix_[i][j]) + 1);
                        matrix_[i][j + 1] = ETileType::TILE_EMPTY;
                        v[0] = i;
                        v[1] = j + 1;
                        v[2] = i;
                        v[3] = j;
                    } else {
                        v[0] = i;
                        v[1] = j;
                        v[2] = i;
                        v[3] = j;
                    }
                    coords.push_back(v);
                }
            }
            if (matrix_[i][SIZE - 1] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = i;
                v[1] = SIZE - 1;
                v[2] = i;
                v[3] = SIZE - 1;
                coords.push_back(v);
            }
        }
    } else if (key == EKey::KEY_RIGHT) {
        for (int32_t i = 0; i < SIZE; i++) {
            for (int32_t j = SIZE - 1; j > 0; j--) {
                if (matrix_[i][j] != ETileType::TILE_EMPTY) {
                    std::vector<int32_t> v(4);
                    if (matrix_[i][j] == matrix_[i][j - 1]) {
                        changed = true;
                        // matrix_[i][j]++;
                        matrix_[i][j] =
                    static_cast<ETileType>(static_cast<int32_t>(matrix_[i][j]) + 1);
                        matrix_[i][j - 1] = ETileType::TILE_EMPTY;
                        v[0] = i;
                        v[1] = j - 1;
                        v[2] = i;
                        v[3] = j;
                    } else {
                        v[0] = i;
                        v[1] = j;
                        v[2] = i;
                        v[3] = j;
                    }
                    coords.push_back(v);
                }
            }
            if (matrix_[i][0] != ETileType::TILE_EMPTY) {
                std::vector<int32_t> v(4);
                v[0] = i;
                v[1] = 0;
                v[2] = i;
                v[3] = 0;
                coords.push_back(v);
            }
        }
    }
    return coords;
}

std::pair<int32_t, int32_t> Table::AddElement() {
    int32_t counter = 1, random = random_in_range(1, CountEmpty() + 1);
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

ETileType Table::GetTile(int32_t i, int32_t j) {
    return matrix_[i][j];
}

int32_t Table::CountEmpty() {
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

bool Table::NoMoves() {
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
