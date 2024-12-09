#include "authorization_agent.hpp"
#include "keynodes/identification_keynodes.hpp"


ScAddr AuthorizationAgent::GetActionClass() const
{
    return IdentificationKeynodes::action_authorization;
}

ScAddr AuthorizationAgent::GetEventSubscriptionElement() const
{
    return ScKeynodes::action_initiated;
}

ScTemplate AuthorizationAgent::GetInitiationConditionTemplate(ScActionInitiatedEvent const & event) const
{
  ScTemplate templ;
  templ.Triple(GetActionClass(), ScType::VarPermPosArc, event.GetOtherElement());
  return templ;
}

ScResult AuthorizationAgent::DoProgram(ScAction & action)
{
    std::string input_login_str, input_password_str;

    auto const & [input_login, input_password] = action.GetArguments<2>();

    SC_AGENT_LOG_INFO("Login input check.");
    if (!m_context.ElementCheck("AuthorizationAgent", input_login)) return action.FinishWithError();
    if (!m_context.EmptyCheck("AuthorizationAgent", input_login, &input_login_str)) return action.FinishWithError();
    if (!m_context.SpaceCheck("AuthorizationAgent", input_login_str)) return action.FinishWithError();
    if (!m_context.SizeCheck("AuthorizationAgent", input_login_str)) return action.FinishWithError();

    SC_AGENT_LOG_INFO("Password input check.");
    if (!m_context.ElementCheck("AuthorizationAgent", input_password)) return action.FinishWithError();
    if (!m_context.EmptyCheck("AuthorizationAgent", input_password, &input_password_str)) return action.FinishWithError();
    if (!m_context.SpaceCheck("AuthorizationAgent", input_password_str)) return action.FinishWithError();
    if (!m_context.SizeCheck("AuthorizationAgent", input_password_str)) return action.FinishWithError();

    return (AuthorizationAgent::UserSearch(action, input_login_str, input_password_str)) ? action.FinishSuccessfully() : action.FinishWithError();
}

bool AuthorizationAgent::UserSearch(ScAction & action, std::string & input_login, std::string & input_password)
{
    SC_AGENT_LOG_INFO("User search.");

    std::string exist_login, exist_password;
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
            SC_AGENT_LOG_INFO("User " + input_login + " found.");
            m_context.GetLinkContent(AuthorizationAgent::GetPassword(it3->Get(2)), exist_password);
            if (exist_password == input_password)
            {
                SC_AGENT_LOG_INFO("Password is correct.");
                action.SetResult(AuthorizationAgent::GetUser(it3->Get(2)));
                SC_AGENT_LOG_INFO(input_login + ". Wellcome.");
                return true;
            }
            else
            {
                SC_AGENT_LOG_ERROR("Password is wrong.");
                return false;
            }
        }
    }
    SC_AGENT_LOG_ERROR("Uncorrect login.");
    return false;
}

ScAddr AuthorizationAgent::GetPassword(ScAddr user_login)
{
    SC_AGENT_LOG_INFO("Get password.");

    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        user_login,
        ScType::ConstCommonArc,
        ScType::ConstNodeLink,
        ScType::ConstPermPosArc,
        IdentificationKeynodes::nrel_password
    );
    it5->Next();
    return it5->Get(2);
}

ScAddr AuthorizationAgent::GetUser(ScAddr user_login)
{
    SC_AGENT_LOG_INFO("Get user.");
    
    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        ScType::ConstNode,
        ScType::ConstCommonArc,
        user_login,
        ScType::ConstPermPosArc,
        IdentificationKeynodes::nrel_login
    );
    it5->Next();
    return it5->Get(0);
}