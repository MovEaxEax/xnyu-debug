#pragma once

// --- Structs ---
struct SavefileField {
    std::string nameParent;
    std::string nameChild;
    std::string nameFull;
    Variable value;
};

struct SavefileParent {
    std::string nameParent;
    std::vector<SavefileField> fields;
};



// --- Variables ---
extern std::vector<SavefileParent> SavefileParents;
extern std::vector<std::string> SavefileFiles;
extern std::string SavefileCurrentFile;
extern int SavefileParentFocus;
extern int SavefileFielFocus;
extern char* SavefileFilesBuffer;
extern HANDLE DebugSavefileEditorMutex;



// --- Functions ---
bool LoadSavefileLayouts();


