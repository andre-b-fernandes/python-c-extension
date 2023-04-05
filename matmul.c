#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject* InvalidMatSize;

PyObject* matrixMultiplication(PyObject* first, PyObject* second, Py_ssize_t matSize){
		PyObject* result = PyList_New(matSize);
    for(Py_ssize_t i = 0; i < matSize ; ++i){
				PyObject* row = PyList_New(matSize);
        for(Py_ssize_t j = 0; j < matSize; ++j){
					PyObject* zero = Py_BuildValue("i", 0);
					PyList_SetItem(row, j, zero);
				}
			PyList_SetItem(result, i, row);
		}

    for(Py_ssize_t i = 0; i < matSize ; ++i){
				PyObject* firstRow = PyList_GetItem(first, i);
				PyObject* targetRow = PyList_GetItem(result, i);
	
        for(Py_ssize_t j = 0; j < matSize; ++j){
						PyObject* initialValue = PyList_GetItem(targetRow, j);
            for(Py_ssize_t k  = 0; k < matSize; ++k){
								PyObject* firstValue = PyList_GetItem(firstRow, k);
								PyObject* secondRow = PyList_GetItem(second, k);
								PyObject* secondValue = PyList_GetItem(secondRow, j);
								PyObject* multValues = PyNumber_Multiply(firstValue, secondValue);
                //result[i*matSize + j] += first[i*matSize + k] * second[k*matSize + j];
								initialValue = PyNumber_Add(initialValue, multValues);
            } 
						PyList_SetItem(targetRow, j, initialValue);
        }
    }
		return result;
}

static PyObject* listCopy(PyObject* self, PyObject* args){
	PyObject* originalMatrix;

	if(!PyArg_ParseTuple(args, "O", &originalMatrix)){
		return NULL;
	}

	Py_ssize_t matSize = PyList_Size(originalMatrix);
	PyObject* result = PyList_New(matSize);

	for(Py_ssize_t i = 0; i < matSize; i++){
		PyObject* value = PyList_GetItem(originalMatrix, i);
		Py_INCREF(value);
		PyList_SetItem(result, i, value);
	}

	return result;
}

static PyObject* matmul(PyObject* self, PyObject* args){
	PyObject* firstMat;
	PyObject* secondMat;

	if(!PyArg_ParseTuple(args, "OO", &firstMat, &secondMat)){
		return NULL;
	}

	Py_ssize_t matSize = PyList_Size(firstMat);
	Py_ssize_t secondmatSize = PyList_Size(secondMat);

	if(matSize != secondmatSize){
		PyErr_SetString(InvalidMatSize, "Matrix len(s) should be the same.");
		return NULL;
	}

	PyObject* returnMat = matrixMultiplication(firstMat, secondMat, matSize);

	return returnMat;
}

static PyMethodDef MatMulMethods[]= {
	{"matmul", matmul, METH_VARARGS, "Matrix Multiplication"},
	{"list_copy", listCopy, METH_VARARGS, "List Copy"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef matmulmodule = {
	PyModuleDef_HEAD_INIT,
	"matmul", /*name of the module*/
	NULL,
	-1,
	MatMulMethods
};

PyMODINIT_FUNC PyInit_matmul(void){
	PyObject* m = PyModule_Create(&matmulmodule);
	if (m == NULL){
		return NULL;
	}

	InvalidMatSize = PyErr_NewException("matmul.error", NULL, NULL);
	Py_XINCREF(InvalidMatSize);

	if (PyModule_AddObject(m, "error", InvalidMatSize) < 0) {
		Py_XDECREF(InvalidMatSize);
		Py_CLEAR(InvalidMatSize);
		Py_DECREF(m);
		return NULL;
	}


	return m;
}
