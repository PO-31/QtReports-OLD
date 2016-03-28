#include "field.hpp"

namespace qtreports {
    namespace detail {

        Field::Field() {}

        Field::~Field() {}

        void    Field::setClassName( const QString & name ) {
            //int id = QMetaType::type( name.toStdString().c_str() );
            //QMetaType type( id );
            //return type.isValid();
            m_className = name;
        }

        const QString   Field::getClassName() const {
            return m_className;
        }

        void Field::setData(const QVector<QVariant> &data)
        {
            m_data = data;
        }

        QString Field::getData(int row)
        {
            if (row < 0 || row >= m_data.size())
                return QString();

            return m_data[row].toString();
        }

        int Field::getRowCount()
        {
            return m_data.size();
        }

    }
}
