#include <Python/Python.h>
#include <iostream>

#include "Language.h"

using namespace std;

Language::Language(string keyPath) {
    credentialPath = keyPath;
}

bool Language::checkEntities(string text, vector<string> entities) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pText, *pArgs, *pValue;

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");

    pName = PyString_FromString("LangCall");
    pText = PyString_FromString(text.c_str());

    if (!pText) {
        cout << "Cannot convert text." << endl;
        return false;
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "checkEntities");

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);  // Argument list

            // First argument: keyPath
            pValue = PyString_FromString(credentialPath.c_str());
            PyTuple_SetItem(pArgs, 0, pValue);

            // Second argument: text
            PyTuple_SetItem(pArgs, 1, pText);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            Py_DECREF(pText);

            // Compare
            if (pValue != NULL) {
                vector<string> result;
                PyObject *pItem;
                
                cerr << "result size: " << PyList_Size(pValue) << endl;  // DEBUG

                // Adds to result
                for (int i = 0; i < PyList_Size(pValue); i++) {
                    pItem = PyList_GetItem(pValue, i);

                    const char* tempCStr = PyString_AsString(pItem);
                    string tempStr = tempCStr;
                    result.push_back(tempStr);
                }

                // Outputs API call result
                cout << "Result of call:\n";
                for (int i = 0; i < result.size(); i++) {
                    cout << result[i] << endl;
                }

                Py_DECREF(pValue);
                Py_DECREF(pItem);
                Py_DECREF(pFunc);
                Py_DECREF(pModule);

                for (int i = 0; i < entities.size(); i++) {
                    vector<string>::iterator it;
                    it = find (result.begin(), result.end(), entities[i]);

                    if (it == result.end()) {
                        return false;
                    }
                }
                return true;
            } else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);

                cout << "Call failed." << endl;
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            cout << "Cannot call function." << endl;
            Py_DECREF(pModule);
        }
    } else {
        PyErr_Print();
        cout << "Failed to load module." << endl;
    }

    Py_Finalize();

    return false;
}