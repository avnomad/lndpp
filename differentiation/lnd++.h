/*
 *  Copyright (C) 2010,2011 Anogeianakis Vaptistis
 *
 *
 *  This file is part of λ&d++.
 *
 *  λ&d++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  λ&d++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with λ&d++.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef LNDPP_H
#define LNDPP_H

#include <cmath>

//template<typename C> struct Const;
//struct Arg;
//template<typename L,typename R> struct Sum;
//template<typename L,typename R> struct Diff;
//template<typename L,typename R> struct Prod;
//template<typename L,typename R> struct Quot;
//template<typename T> struct Neg;
//template<typename T> struct Sin;
//template<typename T> struct Cos;
//
//
//template<typename T>
//struct isNode
//{
//	static const bool value = false;
//};
//
//#define is_node(A) struct isNode<A > \
//{ \
//	static const bool value = true; \
//};
//
//#define binary_is_node(node) template<typename L, typename R> \
//struct isNode<node<L,R> > \
//{ \
//	static const bool value = true; \
//};
//
//template<typename C>
//is_node(Const<C>)
//template< >
//is_node(Arg)
//binary_is_node(Sum)
//binary_is_node(Diff)
//binary_is_node(Prod)
//binary_is_node(Quot)
//template<typename T>
//is_node(Neg<T>)
//template<typename T>
//is_node(Sin<T>)
//template<typename T>
//is_node(Cos<T>)
//#undef is_node
//#undef binary_is_node

template<typename C>
struct Const	// maybe name it C for 'constant' function
{
	C iC;

	inline Const(C c) :iC(c) {}	// 'inline' is redundant here.

	template<typename T>
	inline C operator()(T t)	// better pass by reference?
	{
		//static_assert(!isNode<C>::value,"Const nodes cannot contain other nodes");
		//static_assert(!isNode<T>::value,"Lambda expressions should not (?) be applied to lambda expressions");
		return iC;
	} // end function operator()
};


struct Arg	// maybe name it I for 'identity' function
{
	template<typename T>
	inline T operator()(T t)
	{
		return t;
	} // end function operator()
};

#define BinaryType(op,name) \
	template<typename L,typename R> \
	struct name \
	{ \
		L iL; \
		R iR; \
		\
		inline name(L l,R r) :iL(l),iR(r) {} \
		\
		template<typename ArgType> \
		auto operator()(ArgType arg)->decltype(iL(arg) op iR(arg)) \
		{ \
			return iL(arg) op iR(arg); \
		} \
	};

BinaryType(+,Sum)
BinaryType(-,Diff)
BinaryType(*,Prod)
BinaryType(/,Quot)
#undef BinaryType

#define UnaryType(op,name) \
	template<typename T> \
	struct name \
	{ \
		T iT; \
		\
		inline name(T t) :iT(t) {} \
		\
		template<typename ArgType> \
		auto operator()(ArgType arg)->decltype(op(iT(arg)))  \
		{ \
			return op(iT(arg)); \
		} \
	};

UnaryType(-,Neg)
UnaryType(sin,Sin)
UnaryType(cos,Cos)
#undef UnaryType

template<typename T>
struct Convert
{
	typedef Const<T> type;
};

template< >
struct Convert<Arg>
{
	typedef Arg type;
};

template<typename T>
struct Convert<Const<T> >
{
	typedef Const<T> type;
};

#define BinaryConvert(name) \
	template<typename L,typename R> \
	struct Convert<name<L,R> > \
	{ \
		typedef name<L,R> type; \
	};

BinaryConvert(Sum)
BinaryConvert(Diff)
BinaryConvert(Prod)
BinaryConvert(Quot)
#undef BinaryConvert

#define UnaryConvert(name) \
	template<typename T> \
	struct Convert<name<T> > \
	{ \
		typedef name<T> type; \
	};

UnaryConvert(Neg)
UnaryConvert(Sin)
UnaryConvert(Cos)
#undef UnaryConvert

#define convert(T) typename Convert<T>::type

#define BinaryOperator(op,returnType) \
	template<typename L,typename R> \
	inline returnType<convert(L),convert(R)> op(L l,R r) \
	{ \
		return returnType<convert(L),convert(R)>(l,r); \
	}

BinaryOperator(operator+,Sum)
BinaryOperator(operator-,Diff)
BinaryOperator(operator*,Prod)
BinaryOperator(operator/,Quot)
#undef BinaryOperator

#define UnaryOperator(op,returnType) \
	template<typename T> \
	inline returnType<convert(T)> op(T t) \
	{ \
		return returnType<convert(T)>(t); \
	}

UnaryOperator(operator-,Neg)
UnaryOperator(sin,Sin)
UnaryOperator(cos,Cos)
#undef UnaryOperator

#undef convert



inline Const<int> Differentiate(Arg a)
{
	return Const<int>(1);
}

template<typename T>
inline Const<T> Differentiate(Const<T> c)
{
	return Const<T>(0);
}

template<typename T>
inline auto Differentiate(Neg<T> neg)->decltype(-Differentiate(neg.iT))
{
	return -Differentiate(neg.iT);
}

template<typename L,typename R>
inline auto Differentiate(Sum<L,R> sum)->decltype(Differentiate(sum.iL) + Differentiate(sum.iR))
{
	return Differentiate(sum.iL) + Differentiate(sum.iR);
}

template<typename L,typename R>
inline auto Differentiate(Diff<L,R> diff)->decltype(Differentiate(diff.iL) - Differentiate(diff.iR))
{
	return Differentiate(diff.iL) - Differentiate(diff.iR);
}

template<typename L,typename R>
inline auto Differentiate(Prod<L,R> prod)->decltype(Differentiate(prod.iL)*prod.iR + prod.iL*Differentiate(prod.iR))
{
	return Differentiate(prod.iL)*prod.iR + prod.iL*Differentiate(prod.iR);
}

template<typename L,typename R>
inline auto Differentiate(Quot<L,R> quot)->decltype((Differentiate(quot.iL)*quot.iR - quot.iL*Differentiate(quot.iR)) / (quot.iR*quot.iR))
{
	return (Differentiate(quot.iL)*quot.iR - quot.iL*Differentiate(quot.iR)) / (quot.iR*quot.iR);
}

template<typename T>
inline auto Differentiate(Sin<T> exp)->decltype(cos(exp.iT)*Differentiate(exp.iT))
{
	return cos(exp.iT)*Differentiate(exp.iT);
}

template<typename T>
inline auto Differentiate(Cos<T> exp)->decltype(-sin(exp.iT)*Differentiate(exp.iT))
{
	return -sin(exp.iT)*Differentiate(exp.iT);
}

#endif // LNDPP_H