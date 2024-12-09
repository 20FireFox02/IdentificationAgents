#pragma once

#include "sc-memory/sc_keynodes.hpp"

class IdentificationKeynodes : public ScKeynodes
{
public:
    static inline ScKeynode const action_authorization{"action_authorization", ScType::ConstNodeClass};
    static inline ScKeynode const action_registration{"action_registration", ScType::ConstNodeClass};
    static inline ScKeynode const concept_user{"concept_user", ScType::ConstNodeClass};
    static inline ScKeynode const concept_login{"concept_login", ScType::ConstNodeClass};
    static inline ScKeynode const concept_password{"concept_password", ScType::ConstNodeClass};
    static inline ScKeynode const nrel_login{"nrel_login", ScType::ConstNodeNonRole};
    static inline ScKeynode const nrel_password{"nrel_password", ScType::ConstNodeNonRole};
    static inline ScKeynode const nrel_user_idtf{"nrel_user_idtf", ScType::ConstNodeNonRole};
};
