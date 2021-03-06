/* Copyright 2009-2016 Francesco Biscani (bluescarni@gmail.com)

This file is part of the Piranha library.

The Piranha library is free software; you can redistribute it and/or modify
it under the terms of either:

  * the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.

or

  * the GNU General Public License as published by the Free Software
    Foundation; either version 3 of the License, or (at your option) any
    later version.

or both in parallel, as here.

The Piranha library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received copies of the GNU General Public License and the
GNU Lesser General Public License along with the Piranha library.  If not,
see https://www.gnu.org/licenses/. */

#define BOOST_TEST_MODULE audi_test
#include <boost/test/unit_test.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

#include "../src/environment.hpp"
#include "../src/kronecker_monomial.hpp"
#include "../src/polynomial.hpp"
#include "../src/pow.hpp"
#include "../src/settings.hpp"

using namespace piranha;

// A performance test for truncated polynomial multiplication, in the spirit of automatic differentiation.
// Compute:
// (1+x1+x2+x3+x4+x5+x6+x7+x8+x9+x10)**10 * (1-x1-x2-x3-x4-x5-x6-x7-x8-x9-x10)**10
// truncated to the total degree of 10.

BOOST_AUTO_TEST_CASE(audi_test)
{
	environment env;
	if (boost::unit_test::framework::master_test_suite().argc > 1) {
		settings::set_n_threads(boost::lexical_cast<unsigned>(boost::unit_test::framework::master_test_suite().argv[1u]));
	}
	using p_type = polynomial<double,k_monomial>;
	p_type::set_auto_truncate_degree(10);
	p_type x1{"x1"}, x2{"x2"}, x3{"x3"}, x4{"x4"}, x5{"x5"}, x6{"x6"}, x7{"x7"},
		x8{"x8"}, x9{"x9"}, x10{"x10"};
	auto f = math::pow(1+x1+x2+x3+x4+x5+x6+x7+x8+x9+x10,10);
	auto g = math::pow(1-x1-x2-x3-x4-x5-x6-x7-x8-x9-x10,10);
	p_type h;
	{
	boost::timer::auto_cpu_timer r;
	h = f*g;
	}
	BOOST_CHECK_EQUAL(h.size(),122464u);
}
