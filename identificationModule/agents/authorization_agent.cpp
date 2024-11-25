#include "authorization_agent.hpp"
#include "keynodes/identification_keynodes.hpp"

ScAddr AuthorizationAgent::GetActionClass() const
{
    return IdentificationKeynodes::action_authorization;
}

ScResult AuthorizationAgent::DoProgram(ScAction & action)
{
    std::string input_login_str, input_password_str, exist_login_str, exist_password_str;

    auto const & [input_login, input_password] = action.GetArguments<2>();

    if (!m_context.IsElement(input_login))
    {
        SC_AGENT_LOG_ERROR("Login is not specified.");
        return action.FinishWithError();
    }

    if (!m_context.GetLinkContent(input_login, input_login_str))
    {
        SC_AGENT_LOG_ERROR("Login field is empty.");
        return action.FinishWithError();
    }

    if (!AuthorizationAgent::SpaceCheck(input_login_str)) return action.FinishWithError();


    if (!m_context.IsElement(input_password))
    {
        SC_AGENT_LOG_ERROR("Password is not specified.");
        return action.FinishWithError();
    }

    if (!m_context.GetLinkContent(input_password, input_password_str))
    {
        SC_AGENT_LOG_ERROR("Password field is empty.");
        return action.FinishWithError();
    }

    if (!AuthorizationAgent::SpaceCheck(input_password_str)) return action.FinishWithError();

    if (!AuthorizationAgent::SizeCheck(input_password_str)) return action.FinishWithError();

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
            SC_AGENT_LOG_INFO("Login is founded.");
            ScIterator5Ptr const it5 = m_context.CreateIterator5(
                it3->Get(2),
                ScType::ConstCommonArc,
                ScType::ConstNodeLink,
                ScType::ConstPermPosArc,
                IdentificationKeynodes::nrel_password
            );
            it5->Next();
            SC_AGENT_LOG_INFO("Password check.");
            m_context.GetLinkContent(it5->Get(2), exist_password_str);
            if (exist_password_str == input_password_str)
            {
                SC_AGENT_LOG_INFO("Password is correct.");
                                       
                action.SetResult(AuthorizationAgent::GetUser(it3->Get(2)));

                SC_AGENT_LOG_INFO("Wellcome.");
                return action.FinishSuccessfully();
            }
            else
            {
                SC_AGENT_LOG_ERROR("Password is wrong.");
                return action.FinishWithError();
            }
            /*while (it5->Next())
            {
            	SC_AGENT_LOG_INFO("Password check.");
                m_context.GetLinkContent(it5->Get(2), exist_password_str);
            	if (exist_password_str == input_password_str)
            	{
            	    SC_AGENT_LOG_INFO("Password is correct.");
                                        
                    action.SetResult(AuthorizationAgent::GetUser(it3->Get(2)));

                    SC_AGENT_LOG_INFO("Wellcome.");
             	    return action.FinishSuccessfully();
            	}
            	else
            	{
            	    SC_AGENT_LOG_ERROR("Password is wrong.");
            	    return action.FinishWithError();
            	}
            }*/
        }
    }
    SC_AGENT_LOG_ERROR("Uncorrect input of login or password.");
    return action.FinishWithError();
}

bool AuthorizationAgent::SpaceCheck(std::string & str)
{
    SC_AGENT_LOG_INFO("Space check.");
    for (char i : str)
    {
        if (i == ' ')
        {
            SC_AGENT_LOG_ERROR("Space cannot be entered.");
            return false;
        }
    }
    return true;
}
bool AuthorizationAgent::SizeCheck(std::string & str)
{
    SC_AGENT_LOG_INFO("Size check.");
    if (str.size() < 8)
    {
        SC_AGENT_LOG_ERROR("String size should be no less than 8 symbols.");
        return false;
    }
    return true;
}

/*ScAddr AuthorizationAgent::UserSearch(std::string input_login, std::string input_password)
{
    std::string exist_login, exist_password;

    ScIterator3Ptr const it3 = m_context.CreateIterator3(
        IdentificationKeynodes::login,
        ScType::ConstPermPosArc,
        ScType::ConstNodeLink
    );

    while (it3->Next())
    {
    	SC_AGENT_LOG_INFO("User search.");
        m_context.GetLinkContent(it3->Get(2), exist_login);
        if (exist_login == input_login)
        {
            SC_AGENT_LOG_INFO("Login is founded.");
            ScIterator5Ptr const it5 = m_context.CreateIterator5(
                it3->Get(2),
                ScType::ConstCommonArc,
                ScType::ConstNodeLink,
                ScType::ConstPermPosArc,
                IdentificationKeynodes::nrel_password
            );
            it5->Next();
            SC_AGENT_LOG_INFO("Password check.");
            m_context.GetLinkContent(it5->Get(2), exist_password_str);
            if (exist_password == input_password)
            {
                SC_AGENT_LOG_INFO("Password is correct.");
                                       
                SC_AGENT_LOG_INFO("Wellcome.");
                return AuthorizationAgent::GetUser(it3->Get(2));
            }
            else
            {
                SC_AGENT_LOG_ERROR("Password is wrong.");
                return action.FinishWithError();
            }
        }
    }
    return ScA
}*/

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