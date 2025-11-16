#include <Python.h>
#include <String>
using namespace std;

void EmbedPythonConvert(const string& ppt, const string& pdf)
{
    Py_Initialize();

    PyObject* module = PyImport_ImportModule("ppt to pdf");
    PyObject* func = PyObject_GetAttrString(module, "convert");

    PyObject* args = PyTuple_Pack(
        2,
        PyUnicode_FromString(ppt.c_str()),
        PyUnicode_FromString(pdf.c_str())
    );

    PyObject_CallObject(func, args);

    Py_Finalize();
}