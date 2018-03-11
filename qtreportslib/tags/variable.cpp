#include "variable.hpp"

namespace qtreports {
    namespace detail {
    Variable::Variable(){}
    Variable::~Variable(){}

    void Variable::setVariableName(const QString &name)
    {
        m_variableName = name;
    }

    const QString Variable::getVariableName() const
    {
        return m_variableName;
    }

    void Variable::setClassName(const QString &name)
    {
        m_className = name;
    }

    const QString Variable::getClassName() const
    {
        return m_className;
    }

    void Variable::setResetType(const SpaceType &type)
    {
        m_resetType = type;
    }

    const SpaceType Variable::getResetType() const
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

    void Variable::setIncrementType(const SpaceType &type)
    {
        m_incrementType = type;
    }

    const SpaceType Variable::getIncrementType() const
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

    void Variable::setCalculation(const CalculationType &type)
    {
        m_calculation = type;
    }

    const CalculationType Variable::getCalculation() const
    {
        return m_calculation;
    }

    }
}
