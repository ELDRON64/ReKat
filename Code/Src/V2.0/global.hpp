#pragma once

#define OPENGL
#define OPENAL
#define ONLINE_PEER
#include <ReKat.hpp>
using namespace ReKat;

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <filesystem>

bool Main_shutdown = false;
std::string Begin_string = "ReKat: ";

int current_command = 0;
std::vector < std::string > history;

std::stringstream output;

int start_line = 0;
int total_lines = 0;

enum COMMAND_STATUS {
    SUCCESS,
    NO_COMMAND = -1,
    FAULTY_COMMAND = -2,
    INCORRECT_COMMAND = -3,
    TERMINATE = -999
};

bool ctrl = false;
bool shift = false;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// add the trasmition of N size string