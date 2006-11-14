/* General Python glue code, used in _dbus_bindings but not actually anything
 * to do with D-Bus.
 *
 * Copyright (C) 2006 Collabora Ltd.
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#define DEFERRED_ADDRESS(ADDR) 0

#if defined(__GNUC__)
#   if __GNUC__ >= 3
#       define UNUSED __attribute__((__unused__))
#   else
#       define UNUSED /*nothing*/
#   endif
#else
#   define UNUSED /*nothing*/
#endif

#define DEFINE_CHECK(type) \
static inline int type##_Check (PyObject *o) \
{ \
    return (o->ob_type == &type##Type) \
            || PyObject_IsInstance(o, (PyObject *)&type##Type); \
}

static PyObject *empty_tuple = NULL;

static int
Glue_immutable_setattro(PyObject *obj UNUSED,
                        PyObject *name UNUSED,
                        PyObject *value UNUSED)
{
    PyErr_SetString(PyExc_AttributeError, "Object is immutable");
    return -1;
}

/* Take the global interpreter lock and decrement the reference count.
 * Suitable for calling from a C callback. */
static void
Glue_TakeGILAndXDecref(PyObject *obj)
{
    PyGILState_STATE gil = PyGILState_Ensure();
    Py_XDECREF(obj);
    PyGILState_Release(gil);
}

static inline int
init_generic(void)
{
    empty_tuple = PyTuple_New(0);
    if (!empty_tuple) return 0;
    return 1;
}

/* vim:set ft=c cino< sw=4 sts=4 et: */
