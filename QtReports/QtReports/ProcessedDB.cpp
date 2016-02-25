#include "processeddb.hpp"

namespace qtreports {
	namespace detail {

		ProcessedDB::ProcessedDB() {}

		ProcessedDB::~ProcessedDB() {}

		QVariant ProcessedDB::getParam( const QString & name ) const {
			return QVariant();
		}

		QVariant ProcessedDB::getField( const QString & queryName, const QString & columnName, int row ) const {
			return QVariant();
		}

		QVariant ProcessedDB::getField( const QString & queryName, int column, int row ) const {
			return QVariant();
		}

	}
}

