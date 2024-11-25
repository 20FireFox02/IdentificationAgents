#pragma once
#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_agent.hpp>

class AuthorizationAgent : public ScActionInitiatedAgent
{
public:
    ScAddr GetActionClass() const override;

    ScResult DoProgram(ScAction & action) override;

    bool InputCheck(std::string & check_str);

    bool EmptyCheck();

    bool SpaceCheck(std::string & str);

    bool SizeCheck(std::string & str);

    ScAddr UserSearch(std::string input_login, std::string input_password);

    ScAddr GetUser(ScAddr user_login);
};
