#include "maze_head.h"

void create_path(std::vector<std::vector<int> >& map, int x, int y) {
    map[y][x] = 0;
    int moveArr[4][2] = { {-2,0},{0,2},{2,0},{0,-2} };
    int order[4] = { 0 };
    int n = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        order[n % 4] = rand() % 4;
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                if (order[i] == order[j]) {
                    flag = true;
                }
            }
        }
        n++;
    }
    int nx = 0, ny = 0, dx = 0, dy = 0;
    for (int i = 0; i < 4; i++) {
        dx = moveArr[order[i]][1];
        dy = moveArr[order[i]][0];
        if (x + dx < 0 || x + dx >= map[0].size() || y + dy < 0 || y + dy >= map.size()) {
            continue;
        }
        else {
            if (map[y + dy][x + dx] == 2) {
                nx = x + dx / 2;
                ny = y + dy / 2;
                map[ny][nx] = 0;
                nx = nx + dx / 2;
                ny = ny + dy / 2;
                map[ny][nx] = 0;
                create_path(map, nx, ny);
            }
        }
    }
}

void randomMap(std::vector<std::vector<int> >& map, int height, int width) {
    map.resize(height, std::vector<int>(width, 1));
    time_t t;
    srand(time(&t));
    for (int i = 1; i < map.size(); i += 2) {
        for (int j = 1; j < map[0].size(); j += 2) {
            map[i][j] = 2;
        }
    }
    create_path(map, 1, 1);
}

void readMap(std::vector<std::vector<int> >& map, std::string filename) {
    std::ifstream infile;
    infile.open(filename, std::ios::in);
    if (!infile.is_open()) {
        std::cout << "error opening file" << std::endl;
        exit(1);
    }
    map.reserve(400);
    std::vector<int> line;
    std::string s;
    while (getline(infile, s)) {
        std::istringstream is(s);
        int d;
        while (!is.eof()) {
            is >> d;
            line.push_back(d);
        }
        map.push_back(line);
        line.clear();
        s.clear();
    }
    infile.close();
}