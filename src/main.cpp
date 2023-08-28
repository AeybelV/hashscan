/**
 * @file main.cpp
 * @author Aeybel Varghese (aeybelvarghese@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <hs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <string_view>


#include "patterns.h"
#include "util.h"

// Hyperscan Event Handler, when a pattern match is found, the handler is called. 
// Presently we print the match to console.
// TODO: We should have the option to not print to console, but instead store results to a file.
// TODO: Handle multiple pattern matches to same string.
static int eventHandler(unsigned int id, unsigned long long from,
                        unsigned long long to, unsigned int flags, void *ctx) {
    std::string_view str((char*) ctx); 
    std::cout << "\e[0m\e[1;34m" << str.substr(from,(to-from)) << std::endl;
    std::cout << "\t\e[0m\e[4;31mType:\e[0m\e[1;32m " << pattern_labels[id] << "\n\n" << std::endl;
    return 0;
}

int main(int argc, char *argv[]){

    char *input_filename = argv[1];
    hs_database_t *database;
    hs_compile_error_t *compile_err;
    
    // For hyperscan, uses constexpr to create a list of pattern ID and flags
    constexpr size_t num_patterns = (sizeof(patterns)/sizeof(const char**))-1;
    constexpr auto pattern_ids = Pattern_ID<num_patterns>();
    constexpr auto pattern_flags = Pattern_Flags<num_patterns>();
    // Compiles the patterns to hyperscan database. In the future we should compile the database beforehand and serialize it rather than compiling all the time.
    if (hs_compile_multi(patterns, pattern_flags.flags, pattern_ids.id_list, num_patterns, HS_MODE_BLOCK,NULL,&database,
                    &compile_err) != HS_SUCCESS) {
            fprintf(stderr, "ERROR: Unable to compile patterns: %s", compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
    }

    // Reads the contents of the file specified, yoinked from hyperscan grep example. 
    // In future we should memory map files instead.
    unsigned int length;
    char *inputData = readInputData(input_filename, &length);
    if (!inputData) {
        hs_free_database(database);
        return -1;
    }

    // Allocates scratch space. In future we should have a option for multithreaded searches, each thread requires its own scratch space.
    hs_scratch_t *scratch = NULL;
    if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
        fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
        free(inputData);
        hs_free_database(database);
        return -1;
    }

    // Scans the file
    if (hs_scan(database, inputData, length, 0, scratch, eventHandler, inputData) != HS_SUCCESS) {
        fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
        hs_free_scratch(scratch);
        free(inputData);
        hs_free_database(database);
        return -1;
    }

    hs_free_database(database);
    return 0;
}
