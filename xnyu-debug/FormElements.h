#pragma once



// --- Structs ---
enum ALIGN : int
{
	TOP_CENTER = 0,
	TOP_RIGHT = 1,
	TOP_LEFT = 2,
	LEFT_CENTER = 3,
	RIGHT_CENTER = 4,
	BOTTOM_CENTER = 5,
	BOTTOM_RIGHT = 6,
	BOTTOM_LEFT = 7,
	CENTER_CENTER = 8
};

enum FORM_TYPE : int
{
	TEXTBOX = 0,
	CHECKBOX = 1,
	COMBOBOX = 2,
	BUTTON = 3
};

struct FormElementParameter
{
	std::vector<std::string> comboboxItems;
	std::string textboxPlaceholder = "";
	void* function = nullptr;
};

struct FormElement
{
	FORM_TYPE type = TEXTBOX;
	FormElementParameter parameter;
	std::string name = "";
	std::string label = "";
	std::string info = "";
	Variable value = nullptr;
	int index = 0;
	bool hovered = false;
	bool clicked = false;
	bool focused = false;
};

// --- Functions ---
FormElement CreateFormTextbox(std::string name, std::string label = "", std::string info = "", std::string placeholder = "");
FormElement CreateFormCheckbox(std::string name, std::string label = "", std::string info = "");
FormElement CreateFormCombobox(std::string name, std::vector<std::string> content, std::string label = "", std::string info = "");
FormElement CreateFormButton(std::string name, std::string label, void* function, std::string info = "");

FormElement* FindFormElement(std::vector<FormElement>& formElements, std::string name);
std::string GetFormTextboxValue(FormElement& formElement);
bool GetFormCheckboxValue(FormElement& formElement);
std::string GetFormComboboxValue(FormElement& formElement);
void SetFormTextboxValue(FormElement& formElement, std::string value);
void SetFormCheckboxValue(FormElement& formElement, bool value);
void SetFormComboboxValue(FormElement& formElement, std::string value);
void SetFormComboboxValue(FormElement& formElement, int index);
void SetFormButtonFunction(FormElement& formElement, void* function);


