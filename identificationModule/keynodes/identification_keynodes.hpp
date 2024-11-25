#pragma once

#include "sc-memory/sc_keynodes.hpp"

class IdentificationKeynodes : public ScKeynodes
{
public:
    static inline ScKeynode const action_authorization{"action_authorization", ScType::ConstNodeClass};
    static inline ScKeynode const action_registration{"action_registration", ScType::ConstNodeClass};
    static inline ScKeynode const user{"user", ScType::ConstNodeClass};
    static inline ScKeynode const login{"login", ScType::ConstNodeClass};
    static inline ScKeynode const password{"password", ScType::ConstNodeClass};
    static inline ScKeynode const nrel_login{"nrel_login", ScType::ConstNodeNonRole};
    static inline ScKeynode const nrel_password{"nrel_password", ScType::ConstNodeNonRole};
};
