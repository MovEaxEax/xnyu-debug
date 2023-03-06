// Input Mappings
std::vector<std::string> keyboard_mapping;
std::vector<std::string> joystick_mapping;
std::vector<std::string> mouse_mapping;
std::vector<std::string> float_mapping;
std::vector<std::string> integer_mapping;
std::vector<std::string> bytearray_mapping;
std::vector<std::string> debugfunction_mapping;
std::vector<std::string> address_mapping;

std::string FileNameInputMapping;




//
// Input ---------------------------------------------------------------------------
//

void ReadKeyboardMapping(std::string file_path) {
    // File stream
    std::ifstream file(file_path);

    // Index for the current key
    int index = 0;

    // Clear old list data
    if (keyboard_mapping.size() > 0) keyboard_mapping.clear();

    while (!file.eof()) {
        // Read line
        std::string line;
        std::getline(file, line);

        // Make line lowercase
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });

        // Delete comments and line delimiter
        if (line.find(";") != std::string::npos) {
            line.replace(line.find(";"), line.length() - line.find(";"), "");
        }

        // Delete whitespaces
        if (line.find(" ") != std::string::npos) {
            while (line.find(" ") != std::string::npos) {
                line.replace(line.find(" "), 1, "");
            }
        }

        // Delete tabulators
        if (line.find("\t") != std::string::npos) {
            while (line.find("\t") != std::string::npos) {
                line.replace(line.find("\t"), 1, "");
            }
        }

        if (line != "[keyboard]" && line != "" && line.length() > 2) {

            int line_index = std::stoi(line.substr(0, line.find("=")));

            // Generate standard key entry if none is available in the list
            if (line_index > index) {
                for (int p = index; p < line_index; p++) keyboard_mapping.push_back("dik_ind" + std::to_string(p));
            }

            // Write key from mapping
            keyboard_mapping.push_back(line.substr(line.find("=") + 1, line.length() - line.find("=") - 1));

            // Update current index
            index = line_index + 1;
        }
    }

    if (keyboard_mapping.size() < 256) {
        for (int p = keyboard_mapping.size(); p < 256; p++) keyboard_mapping.push_back("dik_ind" + std::to_string(p));
    }

    // Close the file stream
    file.close();
}

void ReadJoystickMapping(std::string file_path) {
    // File stream
    std::ifstream file(file_path);

    // Clear old list data
    if (joystick_mapping.size() > 0) joystick_mapping.clear();

    while (!file.eof()) {
        // Read line
        std::string line;
        std::getline(file, line);

        // Make line lowercase
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });

        // Delete comments and line delimiter
        if (line.find(";") != std::string::npos) {
            line.replace(line.find(";"), line.length() - line.find(";"), "");
        }

        // Delete whitespaces
        if (line.find(" ") != std::string::npos) {
            while (line.find(" ") != std::string::npos) {
                line.replace(line.find(" "), 1, "");
            }
        }

        // Delete tabulators
        if (line.find("\t") != std::string::npos) {
            while (line.find("\t") != std::string::npos) {
                line.replace(line.find("\t"), 1, "");
            }
        }

        if (line != "[joystick]" && line != "" && line.length() > 2) {

            // Write key from mapping
            joystick_mapping.push_back(line.substr(line.find("=") + 1, line.length() - line.find("=") - 1));

        }
    }

    // Close the file stream
    file.close();
}

void ReadMouseMapping(std::string file_path) {
    // File stream
    std::ifstream file(file_path);

    // Clear old list data
    if (mouse_mapping.size() > 0) mouse_mapping.clear();

    while (!file.eof()) {
        // Read line
        std::string line;
        std::getline(file, line);

        // Make line lowercase
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });

        // Delete comments and line delimiter
        if (line.find(";") != std::string::npos) {
            line.replace(line.find(";"), line.length() - line.find(";"), "");
        }

        // Delete whitespaces
        if (line.find(" ") != std::string::npos) {
            while (line.find(" ") != std::string::npos) {
                line.replace(line.find(" "), 1, "");
            }
        }

        // Delete tabulators
        if (line.find("\t") != std::string::npos) {
            while (line.find("\t") != std::string::npos) {
                line.replace(line.find("\t"), 1, "");
            }
        }

        if (line != "[mouse]" && line != "" && line.length() > 2) {

            // Write key from mapping
            mouse_mapping.push_back(line.substr(line.find("=") + 1, line.length() - line.find("=") - 1));

        }
    }

    // Close the file stream
    file.close();
}


