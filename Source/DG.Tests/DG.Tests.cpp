#include "stdafx.h"

using namespace testing;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
