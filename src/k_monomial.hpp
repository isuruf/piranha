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

#ifndef PIRANHA_K_MONOMIAL_HPP
#define PIRANHA_K_MONOMIAL_HPP

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <type_traits>

#include "small_vector.hpp"

namespace piranha
{

template <typename SignedInt = std::make_signed<std::size_t>::type, int NBits = 8>
class k_monomial
{
	public:
		using value_type = SignedInt;
	private:
		// NOTE: here the +1 is to count the sign bit.
		static_assert(NBits > 0 && NBits <= std::numeric_limits<SignedInt>::digits + 1,"Invalid number of bits.");
		static const unsigned ksize = static_cast<unsigned>((std::numeric_limits<SignedInt>::digits + 1) / NBits);
		template <typename T>
		using init_list_enabler = typename std::enable_if<std::is_constructible<value_type,T>::value,int>::type;
	public:
		using size_type = typename small_vector<value_type>::size_type;
		k_monomial() = default;
		k_monomial(const k_monomial &) = default;
		k_monomial(k_monomial &&) = default;
		template <typename T, init_list_enabler<T> = 0>
		explicit k_monomial(std::initializer_list<T> list)
		{
			for (const auto &x : list) {

			}
		}
		~k_monomial() = default;
		k_monomial &operator=(const k_monomial &) = default;
		k_monomial &operator=(k_monomial &&) = default;
	private:
		small_vector<value_type> m_vec;
};

}

#endif
