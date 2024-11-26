#pragma once
#include <sc-memory/sc_agent_context.hpp>

class InputCheckContex : public ScAgentContext
{
public:
    InputCheckContex(ScAddr const & userAddr)
    : ScAgentContext(userAddr)
    {
    }

    InputCheckContex(sc_memory_context * other)
    : ScAgentContext(other)
    {
    }

    InputCheckContex(InputCheckContex && other)
    : ScAgentContext(std::move(other))
    {
    }

    InputCheckContex & operator=(ScAgentContext && other)
    {
      ScAgentContext::operator=(std::move(other));
      return *this;
    }

    bool ElementCheck(std::string active_agent, ScAddr element);
    bool EmptyCheck(std::string active_agent, ScAddr input_field, std::string * input_field_str);
    bool SpaceCheck(std::string active_agent, std::string & str);
    bool SizeCheck(std::string active_agent, std::string & str);
};