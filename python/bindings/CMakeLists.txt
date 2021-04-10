# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT m17_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT m17_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND m17_python_files
    encoder_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(m17 
   ../..
   gr::m17
   "${m17_python_files}")

install(TARGETS m17_python DESTINATION ${GR_PYTHON_DIR}/m17 COMPONENT pythonapi)
