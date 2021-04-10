/* -*- c++ -*- */
/*
 * Copyright 2021 Derek Kozel.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <m17cxx/M17Modulator.h>

#include "encoder_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace m17 {

using input_type = float;
using output_type = char;
encoder::sptr encoder::make() { return gnuradio::make_block_sptr<encoder_impl>(); }


/*
 * The private constructor
 */
encoder_impl::encoder_impl()
    : gr::sync_block("encoder",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
}

/*
 * Our virtual destructor.
 */
encoder_impl::~encoder_impl() {}

int encoder_impl::work(int noutput_items,
                       gr_vector_const_void_star& input_items,
                       gr_vector_void_star& output_items)
{
    const input_type* in = reinterpret_cast<const input_type*>(input_items[0]);
    output_type* out = reinterpret_cast<output_type*>(output_items[0]);


    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace m17 */
} /* namespace gr */
