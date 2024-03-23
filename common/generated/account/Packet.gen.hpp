#pragma once

namespace gen {
namespace account {
    template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

    enum PacketId : uint16 {
        NONE = 0,
		LOGIN_REQ = 1,
		LOGOUT_REQ = 2,
		REGISTER_REQ = 3,
		LOGIN_RES = 4,
		REGISTER_RES = 5    
	};

}
}