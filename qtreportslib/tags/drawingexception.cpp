#include "drawingexception.hpp"

namespace qtreports {
    namespace detail {

        DrawingException::DrawingException( const QString & error ) : m_error( error ) {}

        DrawingException::~DrawingException() {}

        const QString   DrawingException::getError() const {
            return m_error;
        }

    }
}