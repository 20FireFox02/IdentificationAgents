#include "registration_agent.hpp"
#include "keynodes/identification_keynodes.hpp"

ScAddr RegistrationAgent::GetActionClass() const
{
    return IdentificationKeynodes::action_registration;
}

ScResult RegistrationAgent::DoProgram(ScAction & action)
{
    auto const & [input_login, input_password] = action.GetArguments<2>();

    if (!m_context.IsElement(input_login))
    {
        SC_AGENT_LOG_ERROR("Login is not specified.");
        return action.FinishWithError();
    }
    if (!m_context.IsElement(input_password))
    {
        SC_AGENT_LOG_ERROR("Password is not specified.");
        return action.FinishWithError();
    }

    SC_AGENT_LOG_INFO("Every elements is right.");

    std::string input_login_str, exist_login_str, input_password_str;

    bool const input_login_str_exist = m_context.GetLinkContent(input_login, input_login_str);
    if (!input_login_str_exist)
    {
        SC_AGENT_LOG_ERROR("Login field is empty.");
        return action.FinishWithError();
    }

    bool const input_password_str_exist = m_context.GetLinkContent(input_password, input_password_str);
    if (!input_password_str_exist)
    {
        SC_AGENT_LOG_ERROR("Password field is empty.");
        return action.FinishWithError();
    }

    ScIterator3Ptr const it3 = m_context.CreateIterator3(
        IdentificationKeynodes::login,
        ScType::ConstPermPosArc,
        ScType::ConstNodeLink
    );
    
    while (it3->Next())
    {
    	SC_AGENT_LOG_INFO("User search.");
        m_context.GetLinkContent(it3->Get(2), exist_login_str);
        if (exist_login_str == input_login_str)
        {
            SC_AGENT_LOG_ERROR("Such user already exists.");
            return action.FinishWithError();
        }
    }

    SC_AGENT_LOG_INFO("Create user.");
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::login, input_login);
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::password, input_password);
    ScAddr const & password_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, input_login, input_password);
    m_context.GenerateConnector(ScType::ConstPermPosArc, IdentificationKeynodes::nrel_password, password_arcAddr);

    action.SetResult(input_login);

    return action.FinishSuccessfully();
}