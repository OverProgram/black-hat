//
// Created by tomer on 04/07/2020.
//
#include "bh_inst.h"

#include <utility>

BHInstance::BHInstance() : last_added_program_index(0), last_added_terminal_index(0) {}

BHInstance::~BHInstance() = default;

int BHInstance::add_program(const std::string& path, int parent_handle) {
    int index;
    if (free_program_indices.empty()) {
        index = ++last_added_program_index;
    } else {
        index = free_program_indices.top();
        free_program_indices.pop();
    }
    programs[index] = std::make_shared<Program>(path, this, parent_handle, index);
    return index;
}

void BHInstance::remove_program(int handle) {
    programs.erase(handle);
    free_program_indices.push(handle);
}

std::string BHInstance::get_env(const std::string &name) const {
    if (env_vars.contains(name)) {
        return env_vars.at(name);
    } else {
        return "";
    }
}

void BHInstance::set_env(const std::string &name, const std::string &value) {
    env_vars[name] = value;
}


int BHInstance::add_terminal(const std::string& program_path, int width, int height, int font_width, int font_height) {
    int index;
    if (free_terminal_indices.empty()) {
        index = ++last_added_terminal_index;
    } else {
        index = free_terminal_indices.top();
        free_terminal_indices.pop();
    }
    terminals[index] = std::make_shared<TerminalWidget>(this, index, width, height, font_width, font_height);
    terminals[index]->run(program_path);
    return index;
}

void BHInstance::close_terminal(int handle) {
    terminals.erase(handle);
    free_terminal_indices.push(handle);
}

std::shared_ptr<Program> BHInstance::get_program(int handle) {
    return programs[handle];
}

std::shared_ptr<TerminalWidget> BHInstance::get_terminal(int handle) {
    return terminals[handle];
}
