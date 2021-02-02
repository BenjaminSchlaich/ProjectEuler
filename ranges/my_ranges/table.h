#pragma once

#include <concepts>
#include <list>
#include <stdexcept>
#include <string>
#include <ostream>
#include "comparable.h"

namespace rangeslib
{

	template <Comparable C>
	class Table;

	template <Comparable C>
	class range;

	/*template <Comparable C>
	std::ostream& operator<<(std::ostream& os, const range<C> r)
	{
		std::cout << r.to_string();
		return os;
	}// this got replaced by an anonymous friend function inside the range class! */

	template <Comparable C>
	void removeRange(C& var);

	/*
		This strucutre holds all information on the range of a variable. It is used to store all ranges.
	*/
	template <Comparable C>
	class range
	{
		friend Table<C>;
		// friend std::ostream& operator<<(std::ostream& os, const range<C> r);
		friend void removeRange<C>(C& var);

		friend inline std::ostream& operator<<(std::ostream& os, const range<C> r)
		{
			std::cout << r.to_string();
			return os;
		}

	public:

		range(C& var) : var(var)
		{

		}

	private:

		std::string to_string()
		{
			std::string s;

			if (hasLower)
			{
				if (lowerExclusive)
					s.append("]" + std::to_string(lowerBound) + " ");
				else
					s.append("[" + std::to_string(lowerBound) + " ");
			}
			else
			{
				s.append(" ... ");
			}

			s.append("VAR");

			if (hasUpper)
			{
				if (upperExclusive)
					s.append(std::to_string(upperBound) + " [" + " ");
				else
					s.append(std::to_string(upperBound) + " ]" + " ");
			}
			else
			{
				s.append(" ... ");
			}

			return s;
		}

		C& var;		// the variable the range restriction is applied to

		bool hasUpper;			// wether or not the variable has an upper(/ below lower) bound
		C upperBound;			// the bound specified
		bool upperExclusive;	// if the limit is defined inclusively or exclusively (e.g. if the bound is 3.0, is 3.0 just allowed or not? )

		bool hasLower;			// see above ( c a.)
		C lowerBound;			// c a.
		bool lowerExclusive;	// c a.
	};

	/*
	This class contains and handles all ranges for all variables as static members
	*/
	template <Comparable C>
	class Table
	{
		friend void removeRange<C>(C& var);

	public:

		/*
		Add bounds to a variable
		*/
		static void add(C lowerBound, C& variable, C upperBound, bool lowerExclusive = false, bool upperExclusive = false)
		{
			range<C> r(variable);

			r.hasUpper = true;
			r.upperBound = upperBound;
			r.upperExclusive = upperExclusive;

			r.hasLower = true;
			r.lowerBound = lowerBound;
			r.lowerExclusive = lowerExclusive;

			l.push_back(r);
		}
		
		static void add(C lowerBound, C& variable, bool lowerExclusive = false)
		{
			range<C> r(variable);

			r.hasUpper = false;

			r.hasLower = true;
			r.lowerBound = lowerBound;
			r.lowerExclusive = lowerExclusive;

			l.push_back(r);
		}

		static void add(C& variable, C upperBound, bool upperExclusive = false)
		{
			range<C> r(variable);

			r.hasUpper = true;
			r.upperBound = upperBound;
			r.upperExclusive = upperExclusive;

			l.push_back(r);
		}

		static const range<C>& get(C& var)
		{
			for (range<C>& r : l)
			{
				if (&var == &r.var)
					return r;
			}
		}

		/*
		Check if a given variable is within it's range
		*/
		static bool check(C& var)
		{
			for (range<C> &r : l)
			{
				if (&var == &r.var)	// we've found the entry for this variable by comparing the adresses
				{
					if (r.hasUpper)	// an upper limit was defined, let's check if it holds
					{

						if (r.upperExclusive)
						{
							if (var >= r.upperBound)
								return false;
						}
						else
						{
							if (var > r.upperBound)
								return false;
						}
					}

					if (r.hasLower)	// a lower limit was defined, let's check if it holds
					{
						if (r.lowerExclusive)
						{
							if (var <= r.lowerBound)
								return false;
						}
						else
						{
							if (var < r.lowerBound)
								return false;
						}
					}

					// the variable is evidently within its bounds
					return true;
				}
			}

			// no entry could be found for the given variable
			throw std::invalid_argument("no bounds were specified for the given variable");
		}

		/*
		Remove the entry for a variable
		*/
		static void remove(C& var)
		{
			for (range<C> r : l)
			{
				if (&var == &r.var)	// we found an entry for this variable
				{
					l.remove(r);
				}
			}
		}

	private:
		static std::list<range<C>> l;
	};

	/*
	The list l is the static member that contains all ranges. It must be initialized outside of it's class
	*/
	template <Comparable C>
	std::list<range<C>> Table<C>::l = std::list<range<C>>();

	// The following function templates provide acces to the Table class, so automatic template deduction can be used to access 
	// the correct table for each variable ( depending on its type obviously) in an easy way
	template <Comparable C>
	void addRange(C low, C& var, C high, bool exclusiveLow = 0, bool exclusiveHigh = 0)
	{
		Table<C>::add(low, var, high, exclusiveLow, exclusiveHigh);
	}

	template <Comparable C>
	void removeRange(C& var)
	{
		for (range<C>& r : Table<C>::l)
		{
			if (&r.var == &var)
			{
				Table<C>::l.remove(r);
				return;
			}
		}
	}

}
