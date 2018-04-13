#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <QSharedPointer>

#include <QString>
#include "object.hpp"

namespace qtreports {
    namespace detail {
        /*enum ResetType {None = "None", Report = "Report", Page = "Page", Column = "Column", Group = "Group"};
        enum IncrementType {None = "None", Report = "Report", Page = "Page", Column = "Column", Group = "Group"};

        enum CalculationType {Nothing = "Nothing" , Count = "Count", DistinctCount = "DistinctCount", Sum = "Sum",
                              Average = "Average", Lowest = "Lowest", Highest = "Highest",
                              StandardDeviation = "StandardDeviation", Variance = "Variance", System = "System",
                              First = "First"};*/

        class Variable : public Object {
        public:
            Variable();
            ~Variable();

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
            void            setResetType( const QString & type );

            /*! @~russian
            Возвращает атрибут resetType.
            */
            const QString getResetType() const;

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
            void                  setIncrementType( const QString & type );

            /*! @~russian
            Возвращает атрибут incrementType.
            */
            const QString   getIncrementType() const;

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
            void                    setCalculation( const QString & type );

            /*! @~russian
            Возвращает атрибут calculation.
            */
            const QString   getCalculation() const;

            /*! @~russian
            Устанавливает атрибут expression
            @param[in] expression Выражение
            */
            void        setVariableExpression( const QString & expression );

            /*! @~russian
            Возвращает атрибут expression.
            */
            QString     getVariableExpression();

            /*! @~russian
            Устанавливает атрибут initialExpression
            @param[in] expression Выражение
            */
            void        setInitialValueExpression( const QString & expression );

            /*! @~russian
            Возвращает атрибут initialExpression.
            */
            QString     getInitialValueExpression() const;


        private:
            QString     m_className;
            QString     m_resetType;
            QString     m_resetGroup;
            QString     m_incrementType;
            QString     m_incrementGroup;
            QString     m_calculation;
            QString     m_expression;
            QString     m_initialExpression;
        };

        typedef QSharedPointer<Variable> VariablePtr;
    }
}



#endif // VARIABLE_HPP
