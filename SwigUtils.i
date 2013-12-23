// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

// From the docs: this tells SWIG to treat char ** as a special case
// http://www.swig.org/Doc1.3/Python.html#Python_nn59
%typemap(in) char ** {
   /* Check if is a list */
   if (PyList_Check($input)) {
      int size = PyList_Size($input);
      int i = 0;
      $1 = (char **) malloc((size+1)*sizeof(char *));
      for (i = 0; i < size; i++) {
         PyObject *o = PyList_GetItem($input,i);
         if (PyString_Check(o))
            $1[i] = PyString_AsString(PyList_GetItem($input,i));
         else {
            PyErr_SetString(PyExc_TypeError,"list must contain strings");
            free($1);
            return NULL;
         }
      }
      $1[i] = 0;
   } else {
      PyErr_SetString(PyExc_TypeError,"not a list");
      return NULL;
   }
}
// This cleans up the char ** array we malloc'd before the function call
%typemap(freearg) char ** {
   free((char *) $1);
}
