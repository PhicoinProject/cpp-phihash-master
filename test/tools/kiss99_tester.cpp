// Ethash: C/C++ implementation of Ethash, the Ethereum Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#include <ethash/pcg32.hpp>
#include <iomanip>
#include <iostream>

int main()
{
    constexpr uint32_t mod = 11;
    uint64_t histogram[mod] = {};

   
    uint64_t initstate = 42;  
    uint64_t initseq = 54;    
    pcg32 rng(initstate, initseq);

    constexpr uint64_t output_interval = 1000000000;
    uint64_t output_point = output_interval;

    constexpr double expected = double(1) / mod;

    for (uint64_t i = 0; i <= uint64_t(-1); ++i)
    {
        auto x = rng() % mod;
        ++histogram[x];

        if (i == output_point)
        {
            std::cout << std::right << std::setw(4) << (i / output_interval)
                      << "G:" << std::fixed;

            // Errors:
            for (auto h : histogram)
                std::cout << ' ' << std::setw(10) << std::setprecision(6)
                          << (double(h) / double(i) - expected) / expected * 10 << '%';
            std::cout << '\n';

            output_point += output_interval;
        }
    }

    return 0;
}