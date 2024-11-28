#include "input_check_context.hpp"

bool InputCheckContex::ElementCheck(std::string active_agent, ScAddr element) {
    SC_LOG_INFO(active_agent<<": "<<"Element check");
    if (!IsElement(element)) {
        SC_LOG_ERROR(active_agent<<":"<<"Element is not specified.");
        return false;
    }
    return true;
}

bool InputCheckContex::EmptyCheck(std::string active_agent, ScAddr input_field, std::string * input_field_str) {
    SC_LOG_INFO(active_agent<<": "<<"Empty check");
    if (!GetLinkContent(input_field, (*input_field_str))) {
        SC_LOG_ERROR(active_agent<<":"<<"Field is empty.");
        return false;
    }
    return true;
}

bool InputCheckContex::SpaceCheck(std::string active_agent, std::string & str) {
    SC_LOG_INFO(active_agent<<": "<<"Space check");
    for (char i : str) if (i == ' ') {
        SC_LOG_ERROR(active_agent<<": "<<"You can't enter a space");
        return false;
    }
    return true;
}

bool InputCheckContex::SizeCheck(std::string active_agent, std::string & str) {
    SC_LOG_INFO(active_agent<<": "<<"Size check");
    if (str.size() < 8) {
        SC_LOG_ERROR(active_agent<<": "<<"String size cannot be less than 8 symbols.");
        return false;
     }
     return true;
}
