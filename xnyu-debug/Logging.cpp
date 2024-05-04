#include "pch.h"
#include "GlobalSettings.h"
#include "Logging.h"



// --- Variables ---
bool DebugConsoleEnabled = false;
HANDLE DebugConsoleHandle = nullptr;
FILE* DebugConsoleFilePointer = nullptr;
HANDLE DebugConsoleOutputMutex = CreateMutex(NULL, FALSE, NULL);



// --- Functions ---
void SetDebugConsoleHandle(HANDLE handle)
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    DebugConsoleHandle = handle;
    ReleaseMutex(DebugConsoleOutputMutex);
}

void SetDebugConsoleEnabled(bool enabled)
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    DebugConsoleEnabled = enabled;
    ReleaseMutex(DebugConsoleOutputMutex);
}

void SetDebugConsoleFilePointer(FILE* fp)
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    DebugConsoleFilePointer = fp;
    ReleaseMutex(DebugConsoleOutputMutex);
}

std::tm parseTimestamp(const std::string& timestamp) {
    std::tm tm = {};
    std::stringstream ss(timestamp);
    ss >> std::get_time(&tm, "%Y-%m-%d-%H-%M-%S");
    return tm;
}

void CreateNewLogFile(const std::string& directoryPath)
{
    std::vector<fs::directory_entry> logFiles;

    // Collect all log files in the directory
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".log") {
            logFiles.push_back(entry);
        }
    }

    // Sort files by timestamp
    std::sort(logFiles.begin(), logFiles.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
        std::string timestampA = a.path().stem().string();
        std::string timestampB = b.path().stem().string();
        return parseTimestamp(timestampA) < parseTimestamp(timestampB);
        });

    // Delete oldest files if there are more than 10
    while (logFiles.size() > 10) {
        fs::remove(logFiles.front().path());
        logFiles.erase(logFiles.begin());
    }

    // Create a new log file with the current timestamp
    auto now = std::chrono::system_clock::now();
    auto nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm nowTm = *std::localtime(&nowTimeT);
    std::ostringstream oss;
    oss << std::put_time(&nowTm, "%Y-%m-%d-%H-%M-%S") << ".log";
    std::string newLogFileName = directoryPath + "/" + oss.str();
    std::ofstream newLogFile(newLogFileName);

    return newLogFile;
}

EXTERN_DLL_EXPORT void __stdcall DebugConsoleOutput(std::string text, bool dev, DEBUG_CONSOLE_COLOR color)
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    if (!DebugConsoleEnabled)
    {
        ReleaseMutex(DebugConsoleOutputMutex);
        return;
    }
    if (dev && !IsDevMode())
    {
        ReleaseMutex(DebugConsoleOutputMutex);
        return;
    }
    WORD ForegroundColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    if (color == DEBUG_CONSOLE_COLOR::RED) ForegroundColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (color == DEBUG_CONSOLE_COLOR::GREEN) ForegroundColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    if (color == DEBUG_CONSOLE_COLOR::BLUE) ForegroundColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    if (color == DEBUG_CONSOLE_COLOR::PURPLE) ForegroundColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    if (color == DEBUG_CONSOLE_COLOR::YELLOW) ForegroundColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(DebugConsoleHandle, ForegroundColor);
    std::cout << text << std::endl;
    ReleaseMutex(DebugConsoleOutputMutex);
}


