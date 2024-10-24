// Virtual register class

/**
 * @file Virtreg.cpp
 * @brief Virtual register
 * @author Peter Hakel
 * @version 0.0
 * @date Created in 2013\n
 * Last modified on 23 October 2024
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

/*
References:

Alan Clements:
Principles of Computer Hardware, Fourth Edition
Oxford University Press (2006).

David Money Harris and Sarah L. Harris:
Digital Design and Computer Architecture, Second Edition
Elsevier (2013).
*/

#include <Virtreg.h>

#include <iostream>

// -------------------------------------------

std::vector<double> Virtreg::pow2(Virtreg::nnb, 0.0);
double Virtreg::regmin = 9.33264e-302;
double Virtreg::regmax = 1.07151e+301;
bool Virtreg::sumbits[4] = {false, true, false, true};
bool Virtreg::carries[4] = {false, false, true, true};

// -------------------------------------------

void Virtreg::init()
{
    pow2[nfb] = 1.0;
    for (size_t i = nfb+1; i < nnb; ++i) pow2[i] = pow2[i-1] * 2;
    for (size_t i = nfb-1; i >   0; --i) pow2[i] = pow2[i+1] / 2;
    pow2[0] = pow2[1] / 2;  // i = 0
    regmin = pow2[0];
    regmax = 0.0;
    for (size_t i = 0; i < nnb; ++i) regmax += pow2[i];
}

// -------------------------------------------

double Virtreg::getMin()
{
    return regmin;
}

// -------------------------------------------

double Virtreg::getMax()
{
    return regmax;
}

// -------------------------------------------

void Virtreg::printOverflowWarning()
{
    std::cout << "Warning: virtual register overflow" << std::endl;
}

// -------------------------------------------

Virtreg::Virtreg(): a{}, b{}
{
    a.reset();
    b.reset();
}

// -------------------------------------------

Virtreg::Virtreg(double r): a{}, b{}
{
    a.reset();
    b.reset();
    add(r);
}

// -------------------------------------------

Virtreg::Virtreg(const Virtreg& o): a{}, b{}
{
    a = o.a;
    b = o.b;
}

// -------------------------------------------

Virtreg& Virtreg::operator=(const Virtreg& o)
{
    if (this != &o)
    {
        a = o.a;
        b = o.b;
    }
    return *this;
}

// -------------------------------------------

Virtreg::Virtreg(Virtreg&& o): a{}, b{}
{
    a = std::move(o.a);
    b = std::move(o.b);
}

// -------------------------------------------

Virtreg& Virtreg::operator=(Virtreg&& o)
{
    if (this != &o)
    {
        a = std::move(o.a);
        b = std::move(o.b);
    }
    return *this;
}

// -------------------------------------------

bool Virtreg::operator==(const Virtreg& o)
{
    for (size_t i = 0; i < n; ++i)
        if (b[i] != o.b[i]) return false;
    return true;
}

// -------------------------------------------

bool Virtreg::operator!=(const Virtreg& o)
{
    return !(*this == o);
}

// -------------------------------------------

bool Virtreg::add(double r)
{
    if (r >= 0.0)
    {
        getaBits(r);
    }
    else
    {
        getaBits(-r);
        a.flip();
    }

    bool sign_a = a[nnb];
    bool same = (sign_a == b[nnb]); // same sign bits?
    pushReg(sign_a);

    // same signs initially; result changed sign bit; negative zero reached
    return (same && ((sign_a != b[nnb]) || (b[nnb] && arebNumBits0())));
}

// -------------------------------------------

bool Virtreg::subtract(double r)
{
    return add(-r);
}

// -------------------------------------------

bool Virtreg::plus(double r)
{
    return add(r);
}

// -------------------------------------------

bool Virtreg::minus(double r)
{
    return add(-r);
}

// -------------------------------------------

Virtreg& Virtreg::operator+=(double r)
{
    add(r);
    return *this;
}

// -------------------------------------------

Virtreg& Virtreg::operator-=(double r)
{
    add(-r);
    return *this;
}

// -------------------------------------------

double Virtreg::getValue() const
{
    double r = 0.0;
    if (b[nnb]) // result < 0, perform two's complement
    {
        Virtreg aux;
        for (size_t i = 0; i < n; ++i) aux.b[i] = b[i];
        aux.b.flip();
        aux.a.reset();
        aux.pushReg(true);
        return -aux.getValue();
    }
    else // result >= 0
    {
        for (size_t i = 0; i < nnb; ++i) if (b[i]) r += pow2[i];
        return r;
    }
}

// -------------------------------------------

void Virtreg::printB() const
{
    std::cout << "Current register binary:  ";
    for (size_t i = nnb; i > nfb; --i) std::cout << (b[i] ? '1' : '0');
    std::cout << (b[nfb] ? '1' : '0');  // i = nfb
    std::cout << ".";
    for (size_t i = nfb-1; i > 0; --i) std::cout << (b[i] ? '1' : '0');
    std::cout << (b[0] ? '1' : '0');  // i = 0
    std::cout << std::endl;
}

// -------------------------------------------

void Virtreg::getaBits(double d)
{
    a.reset(n-1);
    for (size_t i = n-2; i > 0; --i)
    {
        if (d - pow2[i] >= 0.0)
        {
            a.set(i);
            d -= pow2[i];
        }
        else
        {
            a.reset(i);
        }
    }
    {
        size_t i = 0;
        if (d - pow2[i] >= 0.0)
        {
            a.set(i);
            d -= pow2[i];
        }
        else
        {
            a.reset(i);
        }
    }
}

// -------------------------------------------

void Virtreg::pushReg(bool c0)
{
    // add a (one's complement, if original a < 0), recycle b, carry c
    // c0 = initial carry-in bit = sign(a) => +1 to effect a's two's complement if a < 0
    bool bres, ccar, c;      // sum and carry bits
    // i = 0
    fullAdder(a[0], b[0], c0, bres, ccar);
    b[0] = bres;
    c = ccar;
    for (size_t i = 1; i < n; ++i)
    {
        fullAdder(a[i], b[i], c, bres, ccar);
        b[i] = bres;
        c = ccar;
    }
}

// -------------------------------------------

void Virtreg::fullAdder(bool i, bool j, bool k, bool& r, bool& c)
{
    int s = (i ? 1 : 0)  +  (j ? 1 : 0)  +  (k ? 1 : 0);
    r = sumbits[s];
    c = carries[s];
}

// -------------------------------------------

bool Virtreg::arebNumBits0() const
{
    for (size_t i = nnb-1; i > 0; --i) if (b[i]) return false;
    if (b[0]) return false;  // i = 0
    return true;
}

// ----------- End class Virtreg -------------

std::ostream& operator << (std::ostream& ost, const Virtreg& o)
{
    ost << o.getValue();
    return ost;
}

// -------------------------------------------
