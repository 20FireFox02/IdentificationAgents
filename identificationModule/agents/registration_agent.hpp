#pragma once
#include <sc-memory/sc_agent.hpp>
#include <sc-memory/sc_event.hpp>
#include "modules/input_check_context.hpp"

class RegistrationAgent : public ScAgent<ScActionInitiatedEvent, InputCheckContex>
{
public:
    ScAddr GetActionClass() const override;
    ScAddr GetEventSubscriptionElement() const override;
    ScTemplate GetInitiationConditionTemplate(ScActionInitiatedEvent const & event) const;
    ScResult DoProgram(ScAction & action) override;

    bool UserSearch(std::string & input_login);
    ScAddr UserCreation(std::string & input_login_str, ScAddr input_login, ScAddr input_password);
};