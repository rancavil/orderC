/*
*       orderC.c
*       Copyright (C) 2020  Rodrigo Ancavil del Pino
*       Email   rancavil@yinnovaser.cl
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define VERSION 1.0

static PyObject *orderCError;

void swap(int *x, int *y);
void bubble(int arr[], int n); 

PyObject* bubbleC(PyObject *self, PyObject *args) {
	PyObject *pylist;
	int *list;
	int len;
	int i=0;

	if(!PyArg_ParseTuple(args,"O",&pylist) || !PyList_Check(pylist)) {
		PyErr_SetString(orderCError,"Invalid list");
		return NULL;
	}
	len  = PySequence_Fast_GET_SIZE(pylist);
	list = malloc(len*sizeof(int));

	/* load c list */
	PyObject* order_list = PyList_New(len);
	for(i=0;i<len;i++) {
		PyObject *item = PySequence_Fast_GET_ITEM(pylist,i);
		if(!item) {
			Py_DECREF(pylist);
			free(list);
			Py_INCREF(Py_None);
			return Py_None;
		}
		list[i] = PyLong_AsLong(item);
	}

	/* order: bubble sort */
	bubble(list,len);

	/* load result */
	for(i=0;i<len;i++) {
		PyObject *item = Py_BuildValue("i",list[i]);
		if(!item) {
			Py_INCREF(Py_None);
			free(list);
			return Py_None;
		}

		PyList_SetItem(order_list,i,item);
	}
	return order_list;
}

void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
void bubble(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject *error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "error something has happened");
    return NULL;
}

static PyMethodDef Methods[] = {
 {"bubbleC",bubbleC,METH_VARARGS,"method to order a list"},
 {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
 {NULL,NULL,0,NULL}
};

#if PY_MAJOR_VERSION >= 3

static int orderC_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int orderC_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "orderC",
        NULL,
        sizeof(struct module_state),
        Methods,
        NULL,
        orderC_traverse,
        orderC_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_orderC(void)

#else
#define INITERROR return

void initorderC(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *mod = PyModule_Create(&moduledef);
#else
    PyObject *mod = Py_InitModule("orderC",Methods);
#endif
    PyObject *exc = PyModule_GetDict(mod);
    orderCError = PyErr_NewException("orderC.orderCError",NULL,NULL);
    PyDict_SetItemString(exc,"orderCError",orderCError);

#if PY_MAJOR_VERSION >= 3
    return mod;
#endif
}

