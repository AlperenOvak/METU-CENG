// server.cpp
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <poll.h>
#include <cstring>
#include "game_structs.h"
#include "print_output.h"
#include <sstream> 

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, 0, fd)

struct PlayerInfo {
    char symbol;
    std::vector<char*> argv;
    std::vector<std::string> args; // keep ownership
    pid_t pid;
    int fd_read_write;   // server reads from this
};

int grid_width, grid_height, streak_size, player_count;
std::vector<PlayerInfo> players;
std::vector<std::vector<char> > board;
std::vector<grid_update> grid_updates;
int filled_count = 0;

void init_board() {
    board = std::vector<std::vector<char> >(grid_height, std::vector<char>(grid_width, '.'));
}

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
            player.args.push_back(arg);                 // keep ownership
        }

        for (const auto& s : player.args) {
            player.argv.push_back(strdup(s.c_str()));  // allocates a fresh C string
        }
        player.argv.push_back(nullptr);                 // execv needs null-terminated

        players.push_back(player);
    }
}

bool check_winner(int x, int y, char symbol) {
    int dx[] = {1, 0, 1, 1};
    int dy[] = {0, 1, 1, -1};

    for (int d = 0; d < 4; ++d) {
        int count = 1;
        for (int step = 1; step < streak_size; ++step) {
            int nx = x + dx[d] * step;
            int ny = y + dy[d] * step;
            if (nx < 0 || ny < 0 || nx >= grid_width || ny >= grid_height || board[ny][nx] != symbol)
                break;
            count++;
        }
        for (int step = 1; step < streak_size; ++step) {
            int nx = x - dx[d] * step;
            int ny = y - dy[d] * step;
            if (nx < 0 || ny < 0 || nx >= grid_width || ny >= grid_height || board[ny][nx] != symbol)
                break;
            count++;
        }
        if (count >= streak_size)
            return true;
    }
    return false;
}


void run_server_loop(){
    bool is_win = false;
    bool is_draw = false;
    int pipes[player_count][2];
    int active_pipes[player_count];
    int active_pipes_count = player_count;
    for (int i = 0; i < player_count; ++i) {
        if (PIPE(pipes[i]) == -1) {
            perror("socketpair");
            exit(1);
        }
        active_pipes[i] = 1;
    }
    // Fork each player
    for (int i = 0; i < player_count; ++i) {
        players[i].pid = fork();
        //std::cout<<i<<" "<<players[i].pid;
        if (players[i].pid == 0) { // Child process
            
            /*std::cerr << "Executing:  ";
            for (int j = 0; players[i].argv[j] != nullptr; ++j) {
                std::cerr << players[i].argv[j] << " ";
            }
            std::cerr << std::endl;*/
            dup2(pipes[i][1], 1); // Redirect stdin to read from the pipe
            dup2(pipes[i][1], 0); // Redirect stdout to write to the pipe
            close(pipes[i][0]); // Close the write end of the pipe
            close(pipes[i][1]); // Close the read end of the pipe
            execv(players[i].argv[0], players[i].argv.data());
            if (access(players[i].argv[0], X_OK) != 0) {
                perror("access check failed");
                return;
            }
        } else { // Parent process
            players[i].fd_read_write = pipes[i][0]; // Store the read end of the pipe
            close(pipes[i][1]); // Close the read end of the pipe
        }
    }
    
    while(active_pipes_count > 0){
        // Poll the pipes
        std::vector<pollfd> polls;
        for (int i = 0; i < player_count; ++i) {
            if (active_pipes[i]) {
                polls.push_back({
                    .fd = players[i].fd_read_write,
                    .events = POLLIN,
                    .revents = 0
                });
            }
        }

        int poll_result = poll(polls.data(), active_pipes_count, -1);
        if (poll_result == -1) {
            perror("poll");
            exit(1);
        }

        for (int i = 0; i < active_pipes_count; ++i) {
            if (polls[i].revents & POLLIN) {
                // Read the message from the pipe
                cm message;
                int byte = read(polls[i].fd, &message, sizeof(message));

                //Draw and win check
                if(is_win){
                    sm endmsg = {END, 0, 0};
                    for (int k = 0; k < player_count; ++k) {
                        if (!active_pipes[k]) continue;
                        smp elog = {players[k].pid, &endmsg};
                        print_output(nullptr, &elog, nullptr, 0);
                        write(players[k].fd_read_write, &endmsg, sizeof(endmsg));
                    }
                    printf("Winner: Player%c\n", players[i].symbol);
                    return;
                }
                if(is_draw){
                    sm endmsg = {END, 0, 0};
                    for (int k = 0; k < player_count; ++k) {
                        if (!active_pipes[k]) continue;
                        smp elog = {players[k].pid, &endmsg};
                        print_output(nullptr, &elog, nullptr, 0);
                        write(players[k].fd_read_write, &endmsg, sizeof(endmsg));
                    }
                    printf("Draw\n");
                    return;
                }
                
                if(byte < 0){
                    active_pipes[i] = 0;
                    close(polls[i].fd);
                    int status;
                    waitpid(players[i].pid, &status, 0);
                    active_pipes_count--;
                    continue;
                }

                cmp client_msg;
                client_msg.process_id = players[i].pid;
                client_msg.client_message = &message;
                print_output(&client_msg, nullptr, nullptr, 0);

                // create a template for the server message
                sm server_result_msg;
                server_result_msg.type = RESULT;
                server_result_msg.success = 0;
                server_result_msg.filled_count = filled_count;

                if (message.type == START) {
                    // TODO: Send the initial grid to the player
                } else if (message.type == MARK) {
                    // Process the MARK message
                    int x = message.position.x;
                    int y = message.position.y;

                    if (x >= 0 && x < grid_width && y >= 0 && y < grid_height && board[y][x] == '.') {
                        board[y][x] = players[i].symbol;
                        filled_count++;
                        
                        // update the server message
                        server_result_msg.success = 1;
                        server_result_msg.filled_count = filled_count;

                        // update the grid updates
                        grid_update update;
                        update.position.x = x;
                        update.position.y = y;
                        update.character = players[i].symbol;
                        grid_updates.push_back(update);
                    } 
                    //printf("Player%c marked (%d, %d,%d) \n", players[i].symbol, x, y,server_result_msg.success);
                    //write(polls[i].fd, &server_result_msg, sizeof(server_result_msg));
                    //printf("Server sent result to Player%c\n", players[i].symbol);

                    // Check for a winner
                    if (check_winner(x, y, players[i].symbol)) {
                        is_win = true;
                    }

                    if (filled_count == grid_width * grid_height) {
                        is_draw = true;
                    }
                }
                smp server_print;
                server_print.process_id = players[i].pid;
                server_print.server_message = &server_result_msg;
                print_output(nullptr, &server_print, grid_updates.data(), filled_count);

                // Send the server message back to the player
                write(players[i].fd_read_write, &server_result_msg, sizeof(server_result_msg));
                //printf("Server sent result to Player%c\n. Size of grid_update is equal = %d %d\n", players[i].symbol, grid_updates.size(), server_result_msg.filled_count);
                
                // Send the grid updates to the player
                write(players[i].fd_read_write, grid_updates.data(), grid_updates.size() * sizeof(grid_update));
                //printf("Server sent grid updates to Player%c, remaining %d\n", players[i].symbol, active_pipes_count-i);
            
            }

        }
    }
}

int main() {
    read_input();
    // Create the play board
    init_board();
    // Create pipes for each player
    run_server_loop();
    // Wait for all child processes to finish
    for (int i = 0; i < player_count; ++i) {
        close(players[i].fd_read_write);
        int status;
        waitpid(players[i].pid, &status, 0);
    }

    return 0;
}