/* -*- c++ -*- */
/*
 * Copyright 2021 Derek Kozel.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_M17_ENCODER_H
#define INCLUDED_M17_ENCODER_H

#include <gnuradio/sync_block.h>
#include <m17/api.h>

namespace gr {
namespace m17 {

/*!
 * \brief M17 Digital Voice encoder
 * \ingroup m17
 *
 */
class M17_API encoder : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<encoder> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of m17::encoder.
     *
     * To avoid accidental use of raw pointers, m17::encoder's
     * constructor is in a private implementation
     * class. m17::encoder::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace m17
} // namespace gr

#endif /* INCLUDED_M17_ENCODER_H */
