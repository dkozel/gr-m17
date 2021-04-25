/* -*- c++ -*- */
/*
 * Copyright 2021 Derek Kozel.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_M17_ENCODER_IMPL_H
#define INCLUDED_M17_ENCODER_IMPL_H

#include <m17cxx/M17Modulator.h>

#include <m17/encoder.h>
#include <string>

namespace gr {
namespace m17 {

class encoder_impl : public encoder
{
private:
    std::string m_destination_address;
    std::string m_source_address;
    
    std::shared_ptr<mobilinkd::M17Modulator> modulator;
    std::shared_ptr<mobilinkd::M17Modulator::audio_queue_t> audio_queue;
    std::shared_ptr<mobilinkd::M17Modulator::bitstream_queue_t> bitstream_queue;

public:
    encoder_impl(const std::string source_address, const std::string destination_address);
    ~encoder_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

    void set_destination(const std::string destination);
    void set_source(const std::string source);
};

} // namespace m17
} // namespace gr

#endif /* INCLUDED_M17_ENCODER_IMPL_H */
