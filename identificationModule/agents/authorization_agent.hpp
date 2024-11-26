#pragma once
#include <sc-memory/sc_agent.hpp>
#include <sc-memory/sc_event.hpp>
#include "modules/input_check_context.hpp"

class AuthorizationAgent : public ScAgent<ScActionInitiatedEvent, InputCheckContex>
{
public:
    ScAddr GetActionClass() const override;
    ScAddr GetEventSubscriptionElement() const override;
    ScTemplate GetInitiationConditionTemplate(ScActionInitiatedEvent const & event) const;
    ScResult DoProgram(ScAction & action) override;

    bool UserSearch(ScAction & action, std::string & input_login, std::string & input_password);
    ScAddr GetPassword(ScAddr user_login);
    ScAddr GetUser(ScAddr user_login);
};