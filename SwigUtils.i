// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

// Based on http://www.swig.org/Doc2.0/SWIGDocumentation.html#Python_nn60
%typemap(in) (int argc, char **argv) {
   if (!PyList_Check($input)) {
      PyErr_SetString(PyExc_TypeError, "Argument 2 must be a list");
      return NULL;
   }
   $1 = PyList_Size($input);
   $2 = (char **) malloc(($1+1) * sizeof(char *));
   int i;
   for (i = 0; i < $1; i++) {
      PyObject *o = PyList_GetItem($input, i);
      if (PyString_Check(o)) {
         $2[i] = PyString_AsString(PyList_GetItem($input, i));
      } else {
         PyErr_SetString(PyExc_TypeError, "Argument 2 must be a list of strings");
         free($2);
         return NULL;
      }
   }
   $2[i] = 0;
}

%typemap(freearg) (int argc, char **argv) {
  free((char *) $2);
}

namespace std {
   template <size_t N> class bitset {
   public:
      bool operator==(bitset<N> const &) const;
      bool operator!=(bitset<N> const &) const;
      bool operator[] (size_t pos) const;
      bitset<N>& operator&=(bitset<N> const &);
      bitset<N>& operator|=(bitset<N> const &);
      bitset<N>& operator^=(bitset<N> const &);
      bitset<N> operator~() const;
      bool test(size_t position) const;
      bitset<N>& set(size_t position);
      bitset<N>& reset(size_t position);
      bitset<N>& flip(size_t position);
      bool all() const;
      bool any() const;
      bool none() const;
      std::string to_string() const;
      size_t count() const;
      size_t size() const;
   };
}
