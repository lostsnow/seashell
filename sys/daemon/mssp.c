// MSSP_D

#include <config.h>

// --------------------------------------------------------------------------
/// @brief mssp_telopt
///
/// MSSP-info formated for telopt interface provided by the driver via
/// master::get_mud_status()
/// @Returns mapping with appropriate key:value pairs
// --------------------------------------------------------------------------
mapping mssp_telopt()
{
    // *INDENT-OFF*
    return ([
        // required
        "NAME"                  : LOCAL_MUD_NAME(),
        "PLAYERS"               : itoa(sizeof(users())),
        "UPTIME"                : itoa(time() - uptime()),
        // generic
        "CRAWL DELAY"           : "24",
        "HOSTNAME"              : CFG_HOSTNAME(),
        "PORT"                  : itoa(LOCAL_MUD_PORT()),
        "CODEBASE"              : "FluffOS v2021",
        "CONTACT"               : CFG_AUTHOR(),
        "CREATED"               : CFG_CREATED(),
        "IP"                    : CFG_HOSTNAME(),
        "LANGUAGE"              : CFG_LANGUAGE(),
        "LOCATION"              : CFG_LOCATION(),
        "MINIMUM AGE"           : "13",
        "WEBSITE"               : CFG_WEBSITE(),
        "ICON"                  : CFG_ICON(),
        // categorization
        "FAMILY"                : "LPMud",
        "STATUS"                : "Live",
        // protocols
        "ANSI"                  : "1",
        "GMCP"                  : itoa(CFG_PTOTOCOL_GMCP()),
        "MCCP"                  : "1",
        "MCP"                   : "0",
        "MSDP"                  : "0",
        "MSP"                   : "0",
        "MXP"                   : itoa(CFG_PTOTOCOL_MXP()),
        "PUEBLO"                : "0",
        "UTF-8"                 : "1",
        "VT100"                 : "1",
        "XTERM 256 COLORS"      : "0",
    ]);
    // *INDENT-ON*
}
// --------------------------------------------------------------------------
/// @brief mssp_login
///
/// This function takes the mapping used for the telopt-interface and converts
/// it to a string representation which may be used for the login-interface.
/// @Returns MSSP-info formated as string
// --------------------------------------------------------------------------
string mssp_login()
{
    string key, val;
    mapping mssp = mssp_telopt();
    string  ret  = "MSSP-REPLY-START\r\n";

    foreach (key, val in mssp) {
        ret += sprintf("%s\t%s\r\n", key, val);
    }

    ret += "MSSP-REPLY-END\r\n";
    return ret;
}
