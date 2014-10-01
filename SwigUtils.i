// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

// Based on http://www.swig.org/Doc2.0/SWIGDocumentation.html#Python_nn60
%typemap(in) (int argc, char **argv) {
   if (!PyList_Check($input)) {
      PyErr_SetString(PyExc_TypeError, "Argument must be a list");
      return NULL;
   }
   $1 = PyList_Size($input);
   $2 = (char **) malloc(($1+1) * sizeof(char *));
   int i;
   for (i = 0; i < $1; i++) {
      PyObject *o = PyList_GetItem($input, i);
      if (PyString_Check(o)) {
         // We have to make a copy of **argv (technically just the
         // first) because in the case of main_loop, we end up
         // scribbling over argv[0]. However this memory is owned by
         // the PyString object, which doesn't know that it has
         // changed, and doesn't appropriately resize itself (in the
         // case that we fill the buffer with null characters).
         $2[i] = strdup(PyString_AS_STRING(PyList_GetItem($input, i)));
      } else {
         PyErr_SetString(PyExc_TypeError, "Argument must be a list of strings");
         SWIG_fail;
      }
   }
   $2[i] = 0;
}

%typemap(freearg) (int argc, char **argv) {
  if($2) {
     int i;
     for (i = 0; i < $1; i++) {
        free($2[i]);
     }
  }
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
