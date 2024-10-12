#ifndef VIRTREG_H_
#define VIRTREG_H_

/**
 * @file Virtreg.h
 * @brief Virtual register
 * @author Peter Hakel
 * @version 0.0
 * @date Created in 2013\n
 * Last modified on 10 October 2024
 * @copyright (c) 2024, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*
Copyright 2024. Triad National Security, LLC. All rights reserved.
This program was produced under U.S. Government contract 89233218CNA000001
for Los Alamos National Laboratory (LANL), which is operated by Triad National Security, LLC
for the U.S. Department of Energy/National Nuclear Security Administration.
All rights in the program are reserved by Triad National Security, LLC, and
the U.S. Department of Energy/National Nuclear Security Administration.
The Government is granted for itself and others acting on its behalf a nonexclusive, paid-up,
irrevocable worldwide license in this material to reproduce, prepare derivative works,
distribute copies to the public, perform publicly and display publicly,
and to permit others to do so.
*/

#include <bitset>
#include <vector>

// -------------------------------------------

/// Virtual register class
class Virtreg
{
public:

    /// Initialize class
    static void init();

    /// Return register's minimum positive value
    static double getMin();

    /// Return register's maximum value
    static double getMax();

    /// Print register's overflow warning
    static void printOverflowWarning();

    /// Default constructor (register is initialized to 0)
    Virtreg();

    /// Constructor (register is initialized to provided double)
    explicit Virtreg(double);

    /// Copy constructor
    Virtreg(const Virtreg&);

    /// Copy assignment
    Virtreg& operator=(const Virtreg&);

    /// Move constructor
    Virtreg(Virtreg&&);

    /// Move assignment
    Virtreg& operator=(Virtreg&&);

    /// Destructor
    ~Virtreg() = default;

    /// Equality test
    bool operator==(const Virtreg&);

    /// Non-equality test
    bool operator!=(const Virtreg&);

    /// Add a double to the register (return false if OK; return true if overflow)
    bool add(double);

    /// Subtract  a double from the register (return false if OK; return true if overflow)
    bool subtract(double);

    /// Add a double to the register (return false if OK; return true if overflow)
    bool plus(double);

    /// Subtract  a double from the register (return false if OK; return true if overflow)
    bool minus(double);

    /// Add a double to the register
    Virtreg& operator+=(double);

    /// Subtract a double from the register
    Virtreg& operator-=(double);

    /// Add another register to the register
    Virtreg& operator+=(const Virtreg&);

    /// Subtract another register from the register
    Virtreg& operator-=(const Virtreg&);

    /// Return register as a double
    double getValue() const;

    /// Print register's bits
    void printB() const;
    
    
private:

    /// Number of integer bits
    static const size_t nib = 1000;

    /// Number of fractional bits
    static const size_t nfb = 1000;

    /// Number of numerical bits
    static const size_t nnb = nib + nfb;

    /// Register size (includes the sign bit)
    static const size_t n = nnb + 1;

    /// Powers of 2
    static std::vector<double> pow2;

    /// Register's minimum positive value
    static double regmin;

    /// Register's maximum value
    static double regmax;

    /// Sum bits for full adder's result
    static bool sumbits[4];

    /// Carry bits for full adder's result
    static bool carries[4];

    /// Convert non-negative double to "a" bits
    void getaBits(double);

    /// Push bits onto the aggregate register (passing in initial carry-in bit value)
    void pushReg(bool);

    /// Add 3 bits, result: 2 bits (sum and carry)
    static void fullAdder(bool, bool, bool, bool&, bool&);

    /// Are all "b" numerical bits zero?
    bool arebNumBits0() const;

    /// Bits of the added register
    std::bitset<n> a;

    /// Bits of the aggregate register
    std::bitset<n> b;
};

// ----------- End class Virtreg -------------

#endif  // VIRTREG_H_
