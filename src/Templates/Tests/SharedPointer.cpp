#include "SharedPointer.hpp"

namespace flame_ide
{namespace test
{

SharedPointer::SharedPointer() : AbstractTest("SharedPointer")
		, pointer {{1000, 100, 10, 1}}
		, stdpointer {std::make_shared<TestClass>(1000, 100, 10, 1)}
{}

SharedPointer::~SharedPointer()
{}

int SharedPointer::vStart()
{
	CHECK_RESULT_SUCCESS(doTestCase(
		"initializing"
		, [&]()
		{
			IN_CASE_CHECK_END(*pointer == *stdpointer);
		}

	));

	CHECK_RESULT_SUCCESS(doTestCase(
		"copying"
		, [&]()
		{
			auto copyPointer = pointer;
			auto stdcopyPointer = stdpointer;
			IN_CASE_CHECK_END(*copyPointer == *stdcopyPointer);
		}

	));

	CHECK_RESULT_SUCCESS(doTestCase(
		"moving"
		, [&]()
		{
			decltype(pointer) movePointer = flame_ide::move(pointer);
			decltype(stdpointer) stdmovePointer = std::move(stdpointer);
			IN_CASE_CHECK_END(*movePointer == *stdmovePointer);
		}

	));

	return 0;
}

}}
