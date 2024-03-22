#pragma once

namespace gen {
namespace account {
    template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

    enum PacketId : uint16 {
        NONE = 0,
		LOGIN_REQ = 1,
		REGISTER_REQ = 2,
		LOGIN_RES = 3,
		REGISTER_RES = 4    
	};

}
}