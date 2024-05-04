#include "pch.h"
#include "Variable.h"
#include "FormElements.h"



// --- Functions ---
FormElement CreateFormTextbox(std::string name, std::string label, std::string info, std::string placeholder)
{
	FormElement form = FormElement();
	form.type = FORM_TYPE::TEXTBOX;
	form.parameter.textboxPlaceholder = placeholder;
	form.label = label;
	form.name = name;
	form.info = info;
	form.value = Variable(VariableType::STRING);
	return form;
}

FormElement CreateFormCheckbox(std::string name, std::string label, std::string info)
{
	FormElement form = FormElement();
	form.type = FORM_TYPE::CHECKBOX;
	form.label = label;
	form.name = name;
	form.info = info;
	form.value = Variable(VariableType::BOOL);
	return form;
}

FormElement CreateFormCombobox(std::string name, std::vector<std::string> content, std::string label, std::string info)
{
	FormElement form = FormElement();
	form.type = FORM_TYPE::COMBOBOX;
	form.parameter.comboboxItems = content;
	form.label = label;
	form.name = name;
	form.info = info;
	form.value = Variable(VariableType::STRING);
	if (content.size() > 0) form.value.setValue(content[0]);
	return form;
}

FormElement CreateFormButton(std::string name, std::string label, void* function, std::string info)
{
	FormElement form = FormElement();
	form.type = FORM_TYPE::BUTTON;
	form.parameter.function = function;
	form.label = label;
	form.name = name;
	form.info = info;
	form.value = Variable(VariableType::BOOL);
	return form;
}

FormElement* FindFormElement(std::vector<FormElement>& formElements, std::string name)
{
	for (int i = 0; i < formElements.size(); i++) if (formElements[i].name == name) return &formElements[i];
	return nullptr;
}

std::string GetFormTextboxValue(FormElement& formElement)
{
	return formElement.value.getString();
}

bool GetFormCheckboxValue(FormElement& formElement)
{
	return formElement.value.getBool();
}

std::string GetFormComboboxValue(FormElement& formElement)
{
	return formElement.value.getString();
}

void SetFormTextboxValue(FormElement& formElement, std::string value)
{
	formElement.value.setValue(value);
}

void SetFormCheckboxValue(FormElement& formElement, bool value)
{
	formElement.value.setValue(value);
}

void SetFormComboboxValue(FormElement& formElement, std::string value)
{
	for (int i = 0; i < formElement.parameter.comboboxItems.size(); i++) if (formElement.parameter.comboboxItems[i] == value) formElement.value.setValue(value);
}

void SetFormComboboxValue(FormElement& formElement, int index)
{
	if (index >= 0 && index < formElement.parameter.comboboxItems.size()) formElement.value.setValue(formElement.parameter.comboboxItems[index]);
}

void SetFormButtonFunction(FormElement& formElement, void* function)
{
	formElement.parameter.function = function;
}


