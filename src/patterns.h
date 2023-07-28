
#pragma once

#include <hs.h>

// Hyperscan
const char *patterns[] = {
    "[a-f0-9]{32}", // MD5
    0
};

// Used for output
const char *hash_names[]={
    "MD5",
};

// const unsigned int pattern_id[] = {
//     HID_MD5,
// };



template<int N>
struct Pattern_ID{
    constexpr Pattern_ID() : id_list() {
        for (auto i = 0; i != N; ++i){
            id_list[i] = i; 
        }
    }
    unsigned int id_list[N];
};


template<int N>
struct Pattern_Flags{
    constexpr Pattern_Flags() : flags() {
        for (auto i = 0; i != N; ++i){
            flags[i] = HS_FLAG_SOM_LEFTMOST; 
        }
    }
    unsigned int flags[N];
};


