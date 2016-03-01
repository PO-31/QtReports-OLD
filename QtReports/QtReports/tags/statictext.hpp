#pragma once
#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "object.hpp"

namespace qtreports {
	namespace detail {

		class StaticText : public Object {

		public:
			StaticText( ObjectPtr parent = ObjectPtr() );

            QString getClassName();

		};

	}
}

#endif // STATICTEXT_HPP
