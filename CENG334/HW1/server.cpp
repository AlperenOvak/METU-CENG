// server.cpp
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <poll.h>
#include <cstring>
#include "game_structs.h"
#include "print_output.h"
#include <sstream> 

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

struct PlayerInfo {
    char symbol;
    std::vector<char*> argv;
    pid_t pid;
    int fd_read_write;   // server reads from this
};

int grid_width, grid_height, streak_size, player_count;
std::vector<PlayerInfo> players;

void read_input() {
    std::cin >> grid_width >> grid_height >> streak_size >> player_count;

    for (int i = 0; i < player_count; ++i) {
        PlayerInfo player;
        int arg_count;

        std::cin >> player.symbol >> arg_count;

        // Read the executable path and arguments
        for (int j = 0; j <= arg_count; ++j) {
            std::string arg;
            std::cin >> arg;
            //std::cout << "arg: " << arg << "\n";
            player.argv.push_back(&arg[0]);
        }
        player.argv.push_back(nullptr);

        players.push_back(player);
    }
}

int main() {
    read_input();

    std::cout << "Grid: " << grid_width << "x" << grid_height << "\n";
    std::cout << "Streak size: " << streak_size << "\n";
    std::cout << "Player count: " << player_count << "\n";

    for (int i = 0; i < player_count; ++i) {
        PlayerInfo& p = players[i];
        std::cout << "Player " << i + 1 << ": " << p.symbol << "\n";
        std::cout << "  Executable and args:";

        // Print until we hit the nullptr
        for (size_t j = 0; j < p.argv.size() - 1; ++j) {
            std::cout << " " << p.argv[j];
        }
        std::cout << "\n";
    }

    return 0;
}