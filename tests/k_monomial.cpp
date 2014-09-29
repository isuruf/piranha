/***************************************************************************
 *   Copyright (C) 2009-2011 by Francesco Biscani                          *
 *   bluescarni@gmail.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "../src/k_monomial.hpp"

#define BOOST_TEST_MODULE k_monomial_test
#include <boost/test/unit_test.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <limits>

#include "../src/environment.hpp"

typedef boost::mpl::vector<signed char,short,int,long,long long> si_types;
//typedef boost::mpl::vector<std::integral_constant<std::size_t,0u>,std::integral_constant<std::size_t,1u>,std::integral_constant<std::size_t,5u>,
//	std::integral_constant<std::size_t,10u>> size_types;

using namespace piranha;

// Constructors, assignments and element access.
struct constructor_tester
{
	template <typename T>
	void operator()(const T &)
	{
		using k_type = k_monomial<T>;
		std::cout << "Size of k_monomial: " << sizeof(k_type) << '\n';
		std::cout << "Number of elements per signed value: " << ((std::numeric_limits<T>::digits + 1) / 8) << '\n';
	}
};

BOOST_AUTO_TEST_CASE(k_monomial_constructor_test)
{
	environment env;
	boost::mpl::for_each<si_types>(constructor_tester());
}
