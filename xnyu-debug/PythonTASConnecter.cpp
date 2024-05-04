#include "pch.h"
#include "Variable.h"
#include "PythonTASConnecter.h"



// --- Variables ---

// Define python module methods
PyMethodDef xNyuTasPythonModuleMethods[] =
{
    {"frame", frame, METH_VARARGS, "Set the input for the next frame. (Pass multiple string parameter)"},
    {"call_internal_function", call_internal_function, METH_VARARGS, "Call an internal function of the debug modification. (Pass name as string and parameter as type)"},
    {"set_internal_variable", set_internal_variable, METH_VARARGS, "Set an internal variable of the debug modification. (Pass name as string and value as type)"},
    {"get_internal_variable", get_internal_variable, METH_VARARGS, "Get an internal variable of the debug modification. (Pass name as string)"}
};

// Configure python module settings
PyModuleDef xNyuTasPythonModule =
{
    PyModuleDef_HEAD_INIT,
    "xnyutas",
    NULL,
    -1,
    xNyuTasPythonModuleMethods
};

bool PythonFrameTriggered;
HANDLE PythonFrameTriggeredMutex = CreateMutex(NULL, FALSE, NULL);
std::vector<std::string> PythonFrameTriggeredParameter;
bool PythonShutdownInterpreter = false;

// --- Functions ---

// Call a frame and specify the input
PyObject* frame(PyObject* self, PyObject* args)
{
    // Create touple for parameter
    PyObject* string_args_tuple;
    if (!PyArg_ParseTuple(args, "O!", &PyTuple_Type, &string_args_tuple)) return NULL;

    // Convert the touples to vector
    std::vector<std::string> frameInputs;
    Py_ssize_t num_args = PyTuple_Size(string_args_tuple);
    for (Py_ssize_t i = 0; i < num_args; i++)
    {
        PyObject* item = PyTuple_GetItem(string_args_tuple, i);
        if (!PyUnicode_Check(item)) continue;
        const char* string = PyUnicode_AsUTF8(item);
        frameInputs.push_back(std::string(string));
    }

    // Trigger the
    WaitForSingleObject(PythonFrameTriggeredMutex, INFINITE);
    PythonFrameTriggered = true;
    PythonFrameTriggeredParameter = frameInputs;
    ReleaseMutex(PythonFrameTriggeredMutex);

    while (true)
    {
        WaitForSingleObject(PythonFrameTriggeredMutex, INFINITE);
        if (!PythonFrameTriggered)
        {
            ReleaseMutex(PythonFrameTriggeredMutex);
            Py_RETURN_NONE;
        }
        if (PythonShutdownInterpreter)
        {
            ReleaseMutex(PythonFrameTriggeredMutex);
            PyErr_SetString(PyExc_Exception, "Shutdown interpreter, TAS stopped!");
            return NULL;
        }
        ReleaseMutex(PythonFrameTriggeredMutex);
    }
}

PyObject* call_internal_function(PyObject* self, PyObject* args)
{
    // Create touple for parameter
    const char* firstStringParameter;
    PyObject* restParameter;
    if (!PyArg_ParseTuple(args, "sO", &firstStringParameter, &restParameter)) return NULL;

    // Get name of funciton to call
    std::string dbgFunctionName(firstStringParameter);

    // Get parameter to pass the function
    std::vector<Variable> dbgFunctionParameter;

    // Check if the rest_of_args is a tuple
    if (PyTuple_Check(restParameter))
    {
        Py_ssize_t argsCount = PyTuple_Size(restParameter);
        for (Py_ssize_t i = 0; i < argsCount; ++i)
        {
            PyObject* item = PyTuple_GetItem(restParameter, i);
            if (PyLong_Check(item))
            {
                // Check int32 and int 64
                long long val = PyLong_AsLongLong(item);
                if ((val <= INT_MAX) && (val >= INT_MIN)) dbgFunctionParameter.emplace_back(static_cast<int>(val));
                else dbgFunctionParameter.emplace_back(val);
            }
            else if (PyBool_Check(item))
            {
                // Check bool
                dbgFunctionParameter.emplace_back(item == Py_True);
            }
            else if (PyFloat_Check(item))
            {
                // Check float and double
                double val = PyFloat_AsDouble(item);
                if (val >= -FLT_MAX && val <= FLT_MAX) dbgFunctionParameter.emplace_back(static_cast<float>(val));
                else dbgFunctionParameter.emplace_back(val);
            }
            else if (PyUnicode_Check(item))
            {
                // Check string
                dbgFunctionParameter.emplace_back(std::string(PyUnicode_AsUTF8(item)));
            }
            else if (PyBytes_Check(item) && PyBytes_Size(item) == 1)
            {
                // Check byte
                dbgFunctionParameter.emplace_back(static_cast<byte>(PyBytes_AsString(item)[0]));
            }
        }
    }

    Py_RETURN_NONE;
}

PyObject* set_internal_variable(PyObject* self, PyObject* args)
{
    // Create touple for parameter
    const char* firstStringParameter;
    PyObject* restParameter;
    if (!PyArg_ParseTuple(args, "sO", &firstStringParameter, &restParameter)) return NULL;

    // Get name of funciton to call
    std::string internalVariableName(firstStringParameter);

    // Get parameter to pass the function
    Variable internalVariableValue = nullptr;

    // Check if the rest_of_args is a tuple
    if (PyTuple_Check(restParameter))
    {
        Py_ssize_t argsCount = PyTuple_Size(restParameter);
        if (argsCount == 0) Py_RETURN_NONE;
        PyObject* item = PyTuple_GetItem(restParameter, 0);
        if (PyLong_Check(item))
        {
            // Check int32 and int 64
            long long val = PyLong_AsLongLong(item);
            if ((val <= INT_MAX) && (val >= INT_MIN)) internalVariableValue = Variable(static_cast<int>(val));
            else internalVariableValue = Variable(val);
        }
        else if (PyBool_Check(item))
        {
            // Check bool
            internalVariableValue = Variable(item == Py_True);
        }
        else if (PyFloat_Check(item))
        {
            // Check float and double
            double val = PyFloat_AsDouble(item);
            if (val >= -FLT_MAX && val <= FLT_MAX) internalVariableValue = Variable(static_cast<float>(val));
            else internalVariableValue = Variable(val);
        }
        else if (PyUnicode_Check(item))
        {
            // Check string
            internalVariableValue = Variable(std::string(PyUnicode_AsUTF8(item)));
        }
        else if (PyBytes_Check(item) && PyBytes_Size(item) == 1)
        {
            // Check byte
            internalVariableValue = Variable(static_cast<byte>(PyBytes_AsString(item)[0]));
        }
    }

    // ...
    // Call the set logic
    // ...

    Py_RETURN_NONE;
}

PyObject* get_internal_variable(PyObject* self, PyObject* args)
{
    // Create touple for parameter
    const char* firstStringParameter;
    if (!PyArg_ParseTuple(args, "s", &firstStringParameter)) return NULL;

    // Get name of variable to get
    std::string internalVariableName(firstStringParameter);

    // Get parameter to pass the function
    Variable internalVariable = nullptr;

    switch (internalVariable.getType())
    {
        case VariableType::BYTE:
            return PyLong_FromUnsignedLong(internalVariable.getByte());
        case VariableType::BOOL:
            return PyBool_FromLong(internalVariable.getBool());
        case VariableType::INT32:
            return PyLong_FromLong(internalVariable.getInt32());
        case VariableType::INT64:
            return PyLong_FromLongLong(internalVariable.getInt64());
        case VariableType::FLOAT:
            return PyFloat_FromDouble(internalVariable.getFloat());
        case VariableType::DOUBLE:
            return PyFloat_FromDouble(internalVariable.getValueAs<double>());
        case VariableType::STRING:
            return PyUnicode_FromString(internalVariable.getValueAs<std::string>().c_str());
        default:
            return NULL;
    }
}

// Export the module
EXTERN_DLL_EXPORT PyMODINIT_FUNC PyInit_xnyutas(void) {
    return PyModule_Create(&xNyuTasPythonModule);
}




