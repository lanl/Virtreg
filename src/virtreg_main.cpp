// Driver to demo the virtual register class (Virtreg)

/**
 * @file virtreg\_main.cpp
 * @brief Virtual register demo driver
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

#include <cstdlib>
#include <iostream>

#include <Virtreg.h>

int main(int argc, char* argv[])
{
    bool showbits = false;
    if (argc == 2) if (std::string(argv[1]) == "verbose") showbits = true;
    double a, s;
    bool ierr;

    s = 0.0;
    Virtreg::init();
    std::cout << "Register minimum: " << Virtreg::getMin() << std::endl;
    std::cout << "Register maximum: " << Virtreg::getMax() << std::endl;

    std::cout << "\nEnter double 1: ";
    std::cin >> a;
    s += a;

    Virtreg reg(a);
    if (showbits) reg.printB();
    std::cout << "Floating point sum: " << s << std::endl;
    std::cout << "Virtual register sum: " << reg.getValue() << std::endl;

    std::cout << "\nEnter double 2: ";
    std::cin >> a;
    s += a;
    ierr = reg.add(a);
    if (ierr) reg.printOverflowWarning();
    if (showbits) reg.printB();
    std::cout << "Floating point sum: " << s << std::endl;
    std::cout << "Virtual register sum: " << reg.getValue() << std::endl;

    std::cout << "\nEnter double 3: ";
    std::cin >> a;
    s += a;
    reg += a;
    if (showbits) reg.printB();
    std::cout << "Floating point sum: " << s << std::endl;
    std::cout << "Virtual register sum: " << reg.getValue() << std::endl;
    
    return EXIT_SUCCESS;
}

//  end virtreg_main.cpp
