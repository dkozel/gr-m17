/* -*- c++ -*- */
/*
 * Copyright 2021 Derek Kozel.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "encoder_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace m17 {

using input_type  = unsigned short;
using output_type = unsigned char;

encoder::sptr encoder::make(const std::string source_address, const std::string destination_address) {
    return gnuradio::make_block_sptr<encoder_impl>(source_address, destination_address);
}

/*
 * The private constructor
 */
encoder_impl::encoder_impl(const std::string source_address, const std::string destination_address)
    : gr::sync_block("encoder",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    
    modulator = std::make_shared<mobilinkd::M17Modulator>(source_address, destination_address);

    auto future = modulator->run(audio_queue, bitstream_queue);

    modulator->ptt_on();
}

/*
 * Our virtual destructor.
 */
encoder_impl::~encoder_impl() {
    modulator->ptt_off();
    modulator->wait_until_idle();
    audio_queue->close();
    bitstream_queue->close();
}

void encoder_impl::set_destination(const std::string destination) {
    m_destination_address = destination;
}

void encoder_impl::set_source(const std::string source) {
    m_source_address = source;
}

int encoder_impl::work(int noutput_items,
                       gr_vector_const_void_star& input_items,
                       gr_vector_void_star& output_items)
{
    const input_type* in = reinterpret_cast<const input_type*>(input_items[0]);
    output_type* out = reinterpret_cast<output_type*>(output_items[0]);

    using namespace std::chrono_literals;
    // Feed entire input buffer into the modulator queue
    for (int index = 0; index < noutput_items; index++) {
        audio_queue->put(reinterpret_cast<uint16_t>(in[index]), 10ms);
    }
    consume(0, noutput_items);

    // Read all available bitstream values from the modulator output queue
    int index = 0;
    uint8_t bits;
    while(bitstream_queue->get(bits, 10ms)) {
        out[index++] = bits;
    }

    // Tell runtime system how many output items we produced.
    return index;
}

} /* namespace m17 */
} /* namespace gr */
