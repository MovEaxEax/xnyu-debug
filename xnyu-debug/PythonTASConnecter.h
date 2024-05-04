#pragma once



// --- Variables ---
extern PyMethodDef xNyuTasPythonModuleMethods[];
extern PyModuleDef xNyuTasPythonModule;

extern bool PythonFrameTriggered;
extern HANDLE PythonFrameTriggeredMutex;
extern std::vector<std::string> PythonFrameTriggeredParameter;
extern bool PythonShutdownInterpreter = false;

// --- Functions ---
PyObject* frame(PyObject* self, PyObject* args);
PyObject* call_internal_function(PyObject* self, PyObject* args);
PyObject* set_internal_variable(PyObject* self, PyObject* args);
PyObject* get_internal_variable(PyObject* self, PyObject* args);
EXTERN_DLL_EXPORT PyMODINIT_FUNC PyInit_xnyutas(void);

