#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rijndael.h"

extern void bytes_free(bytes * addr);
extern bytes * rijndael256_cbc_encrypt(char * key, char * initVector, char * plaintext, int textlength);
extern bytes * rijndael256_cbc_decrypt(char * key, char * initVector, char * ciphertext, int textlength);

static PyObject * pyFunc_EncryptRJ256(PyObject * self, PyObject * args)
{
    char * data_to_encrypt;
    int dataLength;
    char * iv;
    char * key;
    int iv_length;
    int key_length;
    if(!PyArg_ParseTuple(args, "s#s#s#", &key, &key_length, &iv, &iv_length, &data_to_encrypt, &dataLength))
        return NULL;
    bytes * byte = rijndael256_cbc_encrypt(key, iv, data_to_encrypt, dataLength);
    if(byte==NULL)
    {
        PyErr_SetString(PyExc_ValueError, "Incorrect value inserted");
        return Py_BuildValue("y", NULL);
    }
    PyObject * returnValue = Py_BuildValue("y#", byte->data, byte->length);
    bytes_free(byte);
    return returnValue;
}

static PyObject * pyFunc_DecryptRJ256(PyObject * self, PyObject * args)
{
    char * data_to_decrypt;
    int dataLength;
    char * iv;
    char * key;
    int iv_length;
    int key_length;
    if(!PyArg_ParseTuple(args, "s#s#s#", &key, &key_length, &iv, &iv_length, &data_to_decrypt, &dataLength))
        return NULL;
    bytes * byte = rijndael256_cbc_decrypt(key, iv, data_to_decrypt, dataLength);
    if(byte==NULL)
    {
        PyErr_SetString(PyExc_ValueError, "Incorrect value inserted");
        return Py_BuildValue("y", NULL);
    }
    PyObject * returnValue = Py_BuildValue("y#", byte->data, byte->length);
    bytes_free(byte);
    return returnValue;
}

static struct PyMethodDef methods[] = {
    {"encrypt", pyFunc_EncryptRJ256, METH_VARARGS, "Encrypt Plain string to Rijndael256 Bytearray"},
    {"decrypt", pyFunc_DecryptRJ256, METH_VARARGS, "Decrypt Rijndael256 Bytearray to Plain String"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = 
{
    PyModuleDef_HEAD_INIT,
    "cgss_rijndael",
    "",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_cgss_rijndael(void)
{
    return PyModule_Create(&module);
}