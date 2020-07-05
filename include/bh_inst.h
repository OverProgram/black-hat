//
// Created by tomer on 04/07/2020.
//

#ifndef BLACKHAT_BH_INST_H
#define BLACKHAT_BH_INST_H

#include "program.h"
#include "terminal.h"

#include <vector>
#include <map>
#include <queue>

class TerminalWidget;
class Program;

class BHInstance {
public:

    BHInstance();
    ~BHInstance();

    int add_terminal(const std::string& program_path, int width, int height, int font_width=16, int font_height=32);
    std::shared_ptr<TerminalWidget> get_terminal(int handle);
    void close_terminal(int handle);

    int add_program(const std::string& path, int parent_handle);
    std::shared_ptr<Program> get_program(int handle);
    void remove_program(int handle);

    std::string get_env(const std::string& name) const;
    void set_env(const std::string& name, const std::string& value);

private:
    std::map<int, std::shared_ptr<Program>> programs;
    int last_added_program_index;
    std::priority_queue<int, std::vector<int>, std::greater<>> free_program_indices;

    std::map<int, std::shared_ptr<TerminalWidget>> terminals;
    int last_added_terminal_index;
    std::priority_queue<int, std::vector<int>, std::greater<>> free_terminal_indices;

    std::map<std::string, std::string> env_vars;

    std::shared_ptr<BHInstance> this_ptr;
};

#endif //BLACKHAT_BH_INST_H
