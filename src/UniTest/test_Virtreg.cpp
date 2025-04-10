/*=============================================================================

test_Virtreg.cpp
Definitions for unit, integration, and regression tests for class Virtreg.

Created on 23 September 2023
Last modified on 10 April 2025

=============================================================================*/

//  Note: only use trimmed strings for names

#include <Test.h>
#include <Virtreg.h>

void test_Virtreg(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Virtreg";
const double EQT = 1.0e-15;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "case1", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Virtreg::init();
        Virtreg r;
        double s = 1.0e-50;
        r.add(1.0);
        r.add(s);
        r.add(-1.0);
        double expected = s;
        double actual = r.getValue();

        failed_test_count += t.check_equal_real_num(expected, actual, s*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "case2", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Virtreg::init();
        Virtreg r;
        double s = -2.0e-90;
        r.add(2.0);
        r.add(s);
        r.add(-2.0);
        double expected = s;
        double actual = r.getValue();

        failed_test_count += t.check_equal_real_num(expected, actual, -s*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "case3", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Virtreg::init();
        Virtreg r;
        double s = 3.0e-150;
        r.add(3.0);
        r.add(s);
        r.add(-3.0);
        double expected = s;
        double actual = r.getValue();

        failed_test_count += t.check_equal_real_num(expected, actual, s*EQT);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "case4", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Virtreg::init();
        Virtreg r;
        double s = -4.0e-250;
        r.add(-4.0);
        r.add(s);
        r.add(4.0);
        double expected = s;
        double actual = r.getValue();

        failed_test_count += t.check_equal_real_num(expected, actual, -s*EQT);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Virtreg.cpp
