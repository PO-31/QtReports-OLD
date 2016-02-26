#pragma once
#include <QString>

namespace qtreports {
	namespace detail {

		class DrawingException {

		public:
			DrawingException( const QString & error );
			~DrawingException();

			QString		getError() const;

		private:
			QString m_error;

		};

	}
}