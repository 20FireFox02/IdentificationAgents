#include "identification_module.hpp"

#include "agents/authorization_agent.hpp"
#include "agents/registration_agent.hpp"

SC_MODULE_REGISTER(IdentificationModule)
    ->Agent<AuthorizationAgent>()
    ->Agent<RegistrationAgent>();