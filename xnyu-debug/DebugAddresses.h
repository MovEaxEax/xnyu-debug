#pragma once

// --- Structs ---
struct DebugAddress {
    std::string nameParent;
    std::string nameChild;
    std::string nameFull;
    std::vector<std::string> description;
    Variable value;
};

struct DebugAddressParent {
    std::string nameParent;
    std::vector<std::string> description;
    std::vector<DebugAddress> addresses;
};



// --- Variables ---
extern std::vector<DebugAddressParent> DebugAddresses;
extern HANDLE DebugAddressesMutex;



// --- Functions ---
bool DebugAddressSortNameParent(DebugAddress a, DebugAddress b);
bool DebugAddressSortNameChild(DebugAddress a, DebugAddress b);
bool DebugAddressSortNameFull(DebugAddress a, DebugAddress b);
bool LoadDebugAddresses();


