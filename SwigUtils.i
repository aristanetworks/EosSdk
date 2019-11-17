// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

%include exception.i

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
         // NOTE - because we're passing the PyString's internal
         // buffer directly to main_loop, we have to ensure that it
         // is never written. See sdk::main_loop for the hoops we
         // go through to ensure this is the case.
         $2[i] = PyString_AS_STRING(o);
      } else if (PyUnicode_Check(o)) {
         // NOTE - This check is added for Python3. In Python2,
         // "str" is a byte string whereas in Python3 "str" is
         // a unicode string.
         PyObject *b = PyUnicode_AsEncodedString(o, "utf-8", "strict");
         $2[i] = PyBytes_AS_STRING(b);
      } else {
         PyErr_SetString(PyExc_TypeError, "Argument must be a list of strings");
         SWIG_fail;
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

%define STD_FORWARD_LIST(data_type)

// Python --> C
%typemap(in) std::forward_list<eos::##data_type> const & {
   PyObject *t = $input;
   if (PyTuple_Check(t) != true) {
      PyErr_SetString(PyExc_TypeError, "argument must be a tuple");
      return NULL;
   }

   std::forward_list<eos::##data_type> *a = new std::forward_list<eos::##data_type>();
   auto it = a->before_begin();
   for (int i=0; i<PyTuple_Size(t); i++) {
      PyObject *fv = PyTuple_GetItem(t, i);
      eos::##data_type *fv_c;
      if (SWIG_ConvertPtr(fv, (void **)&fv_c,
               SWIGTYPE_p_eos__##data_type,
               SWIG_POINTER_EXCEPTION) == -1) {
         char buf[256];
         delete a;
         snprintf(buf, 256, "expected data type is eos::%s.", #data_type);
         SWIG_exception(SWIG_TypeError, buf);
         return NULL;
      } else {
         it = a->insert_after(it, *fv_c);
      }
   }

   $1 = a;
}

// C --> Python
%typemap(out) std::forward_list<eos::##data_type> const & {
   std::forward_list<eos::##data_type> *a = $1;
   std::forward_list<eos::##data_type>::const_iterator it;
   int count = 0;
   for (it=a->cbegin(); it!=a->cend(); ++it) {
      count += 1;
   }
   PyObject *t = PyTuple_New(count);
   int i = 0;
   for (it=a->cbegin(); it!=a->cend(); ++it) {
      PyObject *fv = SWIG_NewPointerObj((void *)&(*it),
                                        SWIGTYPE_p_eos__##data_type,
                                        0);
      PyTuple_SetItem(t, i, fv);
      i++;
   }
   $result = t;
}
%enddef

STD_FORWARD_LIST(fib_via_t)
STD_FORWARD_LIST(mpls_label_t)
