#ifndef FLAMEIDE_TEMPLATES_TESTS_SERIALIZATIONTEST_HPP
#define FLAMEIDE_TEMPLATES_TESTS_SERIALIZATIONTEST_HPP

#include <tests/Test.hpp>

#include <FlameIDE/Common/Traits.hpp>
#include <FlameIDE/Templates/Serialization.hpp>

namespace flame_ide
{namespace templates
{namespace test
{

class SerializationTest: public AbstractTest
{
public:
	SerializationTest() : AbstractTest("Serialization")
	{}
	virtual ~SerializationTest() = default;

private:
	using Types = flame_ide::Types;
	using SerializerLe = templates::SerializerLe;
	using SerializerBe = templates::SerializerBe;
	using DeserializerLe = templates::DeserializerLe;
	using DeserializerBe = templates::DeserializerBe;

	virtual int vStart();

	ResultType le();
	bool le16();
	bool le32();
	bool le64();

	ResultType be();
	bool be16();
	bool be32();
	bool be64();

	ResultType leSpec();
	bool leSpec32();
	bool leSpec64();

	ResultType beSpec();
	bool beSpec32();
	bool beSpec64();
};

}}}

#endif // FLAMEIDE_TEMPLATES_TESTS_SERIALIZATIONTEST_HPP
