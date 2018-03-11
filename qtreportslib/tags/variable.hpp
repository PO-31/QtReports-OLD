#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <QSharedPointer>

#include <QVariant>
#include <QString>
#include "object.hpp"

namespace qtreports {
    namespace detail {
        enum SpaceType {None = "None", Report = "Report", Page = "Page", Column = "Column", Group = "Group"};

        enum CalculationType {Nothing = "Nothing" , Count = "Count", DistinctCount = "DistinctCount", Sum = "Sum",
                              Average = "Average", Lowest = "Lowest", Highest = "Highest",
                              StandardDeviation = "StandardDeviation", Variance = "Variance", System = "System",
                              First = "First"};

        class Variable : public Object {
        public:
            Variable();
            ~Variable();

            /*! @~russian
            Устанавливает атрибут variableName
            @param[in] name Название переменной
            */
            void            setVariableName(const QString & name);

            /*! @~russian
            Возвращает атрибут variableName.
            */
            const QString   getVariableName() const;

            /*! @~russian
            Устанавливает атрибут className
            @param[in] name Название класса
            */
            void            setClassName( const QString & name );

            /*! @~russian
            Возвращает атрибут className.
            */
            const QString   getClassName() const;

            /*! @~russian
            Устанавливает атрибут resetType
            @param[in] type Тип области сброса переменой
            */
            void            setResetType( const SpaceType & type );

            /*! @~russian
            Возвращает атрибут resetType.
            */
            const SpaceType getResetType() const;

            /*! @~russian
            Устанавливает атрибут resetGroup
            @param[in] groupName Название группы. Используется для сброса переменной, если тип области Group
            */
            void            setResetGroup( const QString & groupName );

            /*! @~russian
            Возвращает атрибут resetGroup.
            */
            const QString   getResetGroup() const;

            /*! @~russian
            Устанавливает атрибут incrementType
            @param[in] type Тип области инкрементирования переменной
            */
            void            setIncrementType( const SpaceType & type );

            /*! @~russian
            Возвращает атрибут incrementType.
            */
            const SpaceType   getIncrementType() const;

            /*! @~russian
            Устанавливает атрибут incrementGroup
            @param[in] groupName Название группы. Используется для инкрементирования переменной, если тип области Group
            */
            void            setIncrementGroup( const QString & groupName );

            /*! @~russian
            Возвращает атрибут incrementGroup.
            */
            const QString   getIncrementGroup() const;

            /*! @~russian
            Устанавливает атрибут calculation
            @param[in] type Название класса
            */
            void            setCalculation( const CalculationType & type );

            /*! @~russian
            Возвращает атрибут calculation.
            */
            const CalculationType   getCalculation() const;


        private:
            QString m_variableName;
            QString m_className;
            SpaceType m_resetType;
            QString m_resetGroup;
            SpaceType m_incrementType;
            QString m_incrementGroup;
            CalculationType m_calculation;
        };

        typedef QSharedPointer<Variable> VariablePtr;
    }
}



#endif // VARIABLE_HPP
