#pragma once

#include <iostream>
#include <string>

#include "Database.h"
#include "Utils.h"

namespace library {
	class Member : public Database, public Utils
	{
	public:
		void createMember();
	};
}


