
#pragma once

#include <hs.h>

// Hyperscan RegEx Patterns
const char *patterns[] = {
    "\\b[a-f0-9]{32}\\b",             // MD5
    "\\b[a-f0-9]{64}\\b",             // SHA256
    "\\b.+@gmail\.com\\b",            // Gmail
    "\\b.+@yahoo\.com\\b",            // Yahoo
    "\\b.+@outlook\.com\\b",          // Outlook
    "\\b.+@proton\.me\\b",            // Proton Mail
    "\\b.+@aol\.com\\b",              // AOL Mail
    "\\b.+@icloud\.com\\b",           // iCloud Mail
    "\\b.+@hotmail\.com\\b",          // Hotmail Mail
    0
};

// Used for output, the index in this array matches up with index of patterns
const char *pattern_labels[]={
    "MD5",
    "SHA256",
    "Gmail Email Address",
    "Yahoo Email Address",
    "Outlook Email Address",
    "Proton Mail Email Address",
    "AOL Email Address",
    "iCloud Email Address",
    "Hotmail Email Address"
};

// At compile time, pattern ID's are created for all the hash patterns. The ID corresponds to its respective hash in hash_names and patterns
template<int N>
struct Pattern_ID{
    constexpr Pattern_ID() : id_list() {
        for (auto i = 0; i != N; ++i){
            id_list[i] = i; 
        }
    }
    unsigned int id_list[N];
};

// To get the start of a match, every pattern needs the HS_FLAG_SOM_LEFTMOST flag set at hyperscan compile.
template<int N>
struct Pattern_Flags{
    constexpr Pattern_Flags() : flags() {
        for (auto i = 0; i != N; ++i){
            flags[i] = HS_FLAG_SOM_LEFTMOST; 
        }
    }
    unsigned int flags[N];
};


