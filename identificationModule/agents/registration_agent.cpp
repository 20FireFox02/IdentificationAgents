#include "registration_agent.hpp"
#include "keynodes/identification_keynodes.hpp"

ScAddr RegistrationAgent::GetActionClass() const
{
    return IdentificationKeynodes::action_registration;
}

ScAddr RegistrationAgent::GetEventSubscriptionElement() const
{
    return ScKeynodes::action_initiated;
}

ScTemplate RegistrationAgent::GetInitiationConditionTemplate(ScActionInitiatedEvent const & event) const
{
  ScTemplate templ;
  templ.Triple(GetActionClass(), ScType::VarPermPosArc, event.GetOtherElement());
  return templ;
}

ScResult RegistrationAgent::DoProgram(ScAction & action)
{
    std::string input_login_str, input_password_str;
    
    auto const & [input_login, input_password] = action.GetArguments<2>();

    SC_AGENT_LOG_INFO("Login input check.");
    if (!m_context.ElementCheck("RegistrationAgent", input_login)) return action.FinishWithError();
    if (!m_context.EmptyCheck("RegistrationAgent", input_login, &input_login_str)) return action.FinishWithError();
    if (!m_context.SpaceCheck("RegistrationAgent", input_login_str)) return action.FinishWithError();
    if (!m_context.SizeCheck("RegistrationAgent", input_login_str)) return action.FinishWithError();

    SC_AGENT_LOG_INFO("Password input check.");
    if (!m_context.ElementCheck("RegistrationAgent", input_password)) return action.FinishWithError();
    if (!m_context.EmptyCheck("RegistrationAgent", input_password, &input_password_str)) return action.FinishWithError();
    if (!m_context.SpaceCheck("RegistrationAgent", input_password_str)) return action.FinishWithError();
    if (!m_context.SizeCheck("RegistrationAgent", input_password_str)) return action.FinishWithError();

    if (!RegistrationAgent::UserSearch(input_login_str)) return action.FinishWithError();

    action.SetResult(RegistrationAgent::UserCreation(input_login_str, input_login, input_password));
    SC_AGENT_LOG_INFO(input_login_str + ". Wellcome.");
    return action.FinishSuccessfully();
}

bool RegistrationAgent::UserSearch(std::string & input_login)
{
    SC_AGENT_LOG_INFO("User search.");

    std::string exist_login;
    ScIterator3Ptr const it3 = m_context.CreateIterator3(
        IdentificationKeynodes::concept_login,
        ScType::ConstPermPosArc,
        ScType::ConstNodeLink
    );
    
    while (it3->Next())
    {
        m_context.GetLinkContent(it3->Get(2), exist_login);
        if (exist_login == input_login)
        {
            SC_AGENT_LOG_ERROR("Such user already exists.");
            return false;
        }
    }
    return true;
}

ScAddr RegistrationAgent::UserCreation(std::string & input_login_str, ScAddr input_login, ScAddr input_password)
{
    SC_AGENT_LOG_INFO("User creation.");

    ScAddr const & new_user = m_context.GenerateNode(ScType::ConstNode);
    m_context.SetElementSystemIdentifier(input_login_str, new_user);

    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::concept_user, new_user);
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::concept_login, input_login);
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::concept_password, input_password);

    ScAddr const & password_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, input_login, input_password);
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::nrel_password, password_arcAddr);

    ScAddr const & login_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, new_user, input_login);
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::nrel_login, login_arcAddr);

    std::string get_login;
    m_context.GetLinkContent(input_login, get_login);
    ScAddr const & idtf_Addr = m_context.GenerateLink(ScType::ConstNodeLink);
    m_context.SetLinkContent(idtf_Addr, get_login);
    ScAddr const & idtf_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, new_user, idtf_Addr);
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::nrel_user_idtf, idtf_arcAddr);
    SC_AGENT_LOG_INFO("User " + input_login_str + " created.");
    return new_user;
}