#include <Python.h>
#include <string>
#include "Tools.h"
using namespace std;

void EmbedPythonConvert(const string& ppt, const string& pdf)
{
    Py_Initialize();
    PyRun_SimpleString(
        "import sys; sys.path.append('C:/Users/kim/Desktop/Perosnal Project/FIle Converter/py')"
    );

    PyObject* module = PyImport_ImportModule("ppt2pdf");
    if (!module) {
        PyErr_Print();
        Py_Finalize();
        return;
    }

    PyObject* func = PyObject_GetAttrString(module, "convert");
    if (!func || !PyCallable_Check(func)) {
        PyErr_Print();
        Py_XDECREF(func);
        Py_DECREF(module);
        Py_Finalize();
        return;
    }

    PyObject* args = PyTuple_Pack(
        2,
        PyUnicode_FromString(ppt.c_str()),
        PyUnicode_FromString(pdf.c_str())
    );

    PyObject* result = PyObject_CallObject(func, args);
    if (!result) {
        PyErr_Print();
    }

    Py_XDECREF(result);
    Py_DECREF(args);
    Py_DECREF(func);
    Py_DECREF(module);

    Py_Finalize();
}