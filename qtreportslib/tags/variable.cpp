#include "variable.hpp"

namespace qtreports {
    namespace detail {
    Variable::Variable()
    {
        m_resetType = "Report";
        m_resetGroup = "";
        m_incrementType = "None";
        m_incrementGroup = "";
        m_calculation = "Nothing";
    }
    Variable::~Variable(){}

    void Variable::setClassName(const QString &name)
    {
        m_className = name;
    }

    const QString Variable::getClassName() const
    {
        return m_className;
    }

    void Variable::setResetType(const QString &type)
    {
        m_resetType = type;
    }

    const QString Variable::getResetType() const
    {
        return m_resetType;
    }

    void Variable::setResetGroup(const QString &groupName)
    {
        m_resetGroup = groupName;
    }

    const QString Variable::getResetGroup() const
    {
        return m_resetGroup;
    }

    void Variable::setIncrementType(const QString &type)
    {
        m_incrementType = type;
    }

    const QString Variable::getIncrementType() const
    {
        return m_incrementType;
    }

    void Variable::setIncrementGroup(const QString &groupName)
    {
        m_incrementGroup = groupName;
    }

    const QString Variable::getIncrementGroup() const
    {
        return m_incrementGroup;
    }

    void Variable::setCalculation(const QString & type)
    {
        m_calculation = type;
    }

    const QString Variable::getCalculation() const
    {
        return m_calculation;
    }

    void Variable::setVariableExpression(const QString & expression)
    {
        m_expression = expression;
    }

    QString Variable::getVariableExpression()
    {
        return m_expression;
    }

    void Variable::setInitialValueExpression(const QString & expression)
    {
        m_initialExpression = expression;
    }

    QString Variable::getInitialValueExpression() const
    {
        return m_initialExpression;
    }

    }
}
