#include <FlameIDE/../../src/Templates/Tests/TestAggregator.hpp>
#include <FlameIDE/../../src/Common/Tests/TestAggregator.hpp>
#include <FlameIDE/../../src/Streams/Tests/TestAggregator.hpp>
#include <FlameIDE/../../src/Threads/Tests/TestAggregator.hpp>
#include <FlameIDE/../../src/Os/Tests/TestAggregator.hpp>

int main()
{
	flame_ide::templates::tests::TestAggregator().start();
	flame_ide::common::tests::TestAggregator().start();
	flame_ide::streams::tests::TestAggregator().start();
	flame_ide::threads::tests::TestAggregator().start();
	flame_ide::os::tests::TestAggregator().start();
	return 0;
}
