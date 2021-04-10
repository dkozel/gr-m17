/* -*- c++ -*- */
/*
 * Copyright 2021 Derek Kozel.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_M17_ENCODER_IMPL_H
#define INCLUDED_M17_ENCODER_IMPL_H

#include <m17/encoder.h>

namespace gr {
namespace m17 {

class encoder_impl : public encoder
{
private:

public:
    encoder_impl();
    ~encoder_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace m17
} // namespace gr

#endif /* INCLUDED_M17_ENCODER_IMPL_H */
