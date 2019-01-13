TEMPLATE = app
CONFIG += console
CONFIG += object_parallel_to_source
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS = -std=c++14 -pedantic -fno-rtti -fno-exceptions
QMAKE_CXXFLAGS_DEBUG += -gdwarf-3
INCLUDEPATH += include/
INCLUDEPATH += .

# headers
HEADERS += \
	./include/FlameIDE/About/About.hpp \
	./include/FlameIDE/Analysers/Ubjson/Array.hpp \
	./include/FlameIDE/Analysers/Ubjson/BaseValue.hpp \
	./include/FlameIDE/Analysers/Ubjson/HugeNumber.hpp \
	./include/FlameIDE/Analysers/Ubjson/Object.hpp \
	./include/FlameIDE/Analysers/Ubjson/Pair.hpp \
	./include/FlameIDE/Analysers/Ubjson/Settings.hpp \
	./include/FlameIDE/Analysers/Ubjson/SimpleTypeValues.hpp \
	./include/FlameIDE/Analysers/Ubjson/Stream.hpp \
	./include/FlameIDE/Analysers/Ubjson/String.hpp \
	./include/FlameIDE/Analysers/Ubjson/Traits.hpp \
	./include/FlameIDE/Analysers/Ubjson/Types.hpp \
	./include/FlameIDE/Analysers/Ubjson/Value.hpp \
	./include/FlameIDE/Analysers/Ubjson/ValueSpecializations.hpp \
	./include/FlameIDE/Bus/MsgInterface.hpp \
	./include/FlameIDE/Common/Byte.hpp \
	./include/FlameIDE/Common/Macroses.hpp \
	./include/FlameIDE/Common/PrimitiveTypes.hpp \
	./include/FlameIDE/Common/Traits.hpp \
	./include/FlameIDE/Common/Traits/ContainerTraits.hpp \
	./include/FlameIDE/Common/Traits/CreationProhibitions.hpp \
	./include/FlameIDE/Common/Traits/Defaults.hpp \
	./include/FlameIDE/Common/Traits/Fuctional.hpp \
	./include/FlameIDE/Common/Traits/Numbers.hpp \
	./include/FlameIDE/Common/Utils.hpp \
	./include/FlameIDE/Constants/C.hpp \
	./include/FlameIDE/Constants/CPP.hpp \
	./include/FlameIDE/Filesystem/BasicFile.hpp \
	./include/FlameIDE/Filesystem/Project.hpp \
	./include/FlameIDE/Filesystem/Session.hpp \
	./include/FlameIDE/Others/TextStyle.hpp \
	./include/FlameIDE/Process/CommandLine.hpp \
	./include/FlameIDE/Streams/DefaultAccumulator.hpp \
	./include/FlameIDE/Streams/StreamBase.hpp \
	./include/FlameIDE/Templates/AlignObject.hpp \
	./include/FlameIDE/Templates/Allocator.hpp \
	./include/FlameIDE/Templates/Allocator/ArrayAllocator.hpp \
	./include/FlameIDE/Templates/Allocator/Interface.hpp \
	./include/FlameIDE/Templates/Allocator/MallocAllocator.hpp \
	./include/FlameIDE/Templates/Allocator/ObjectAllocator.hpp \
	./include/FlameIDE/Templates/Array.hpp \
	./include/FlameIDE/Templates/ArrayBlocks.hpp \
	./include/FlameIDE/Templates/BitSet.hpp \
	./include/FlameIDE/Templates/Bits.hpp \
	./include/FlameIDE/Templates/ByteOrder.hpp \
	./include/FlameIDE/Templates/CircularArray.hpp \
	./include/FlameIDE/Templates/CircularVector.hpp \
	./include/FlameIDE/Templates/HybridVector.hpp \
	./include/FlameIDE/Templates/InitializerList.hpp \
	./include/FlameIDE/Templates/IntegerIterator.hpp \
	./include/FlameIDE/Templates/Iterator.hpp \
	./include/FlameIDE/Templates/Iterator/BaseIterator.hpp \
	./include/FlameIDE/Templates/Iterator/CircularIterator.hpp \
	./include/FlameIDE/Templates/Iterator/ConstCircularIterator.hpp \
	./include/FlameIDE/Templates/Iterator/ConstIterator.hpp \
	./include/FlameIDE/Templates/Iterator/ConstReverseIterator.hpp \
	./include/FlameIDE/Templates/Iterator/Iterator.hpp \
	./include/FlameIDE/Templates/Iterator/IteratorTraits.hpp \
	./include/FlameIDE/Templates/Iterator/Operators.hpp \
	./include/FlameIDE/Templates/Iterator/ReverseIterator.hpp \
	./include/FlameIDE/Templates/Iterator/UndefOperators.hpp \
	./include/FlameIDE/Templates/List.hpp \
	./include/FlameIDE/Templates/ObjectViewer.hpp \
	./include/FlameIDE/Templates/Optional.hpp \
	./include/FlameIDE/Templates/Pointers.hpp \
	./include/FlameIDE/Templates/Range.hpp \
	./include/FlameIDE/Templates/Serialization.hpp \
	./include/FlameIDE/Templates/Serialization/Deserializer.hpp \
	./include/FlameIDE/Templates/Serialization/Serializer.hpp \
	./include/FlameIDE/Templates/Serialization/SpecializedValue.hpp \
	./include/FlameIDE/Templates/Serialization/ValueInfo.hpp \
	./include/FlameIDE/Templates/SimpleAlgorithms.hpp \
	./include/FlameIDE/Templates/String.hpp \
	./include/FlameIDE/Templates/Templates.hpp \
	./include/FlameIDE/Templates/Trees.hpp \
	./include/FlameIDE/Templates/Tuple.hpp \
	./include/FlameIDE/Templates/Variant.hpp \
	./include/FlameIDE/Templates/Vector.hpp \
	./include/FlameIDE/Templates/WideFloat.hpp \
	./include/FlameIDE/Templates/WideInt.hpp \
	./src/Common/Tests/TestAggregator.hpp \
	./src/Common/Tests/Utils.hpp \
	./src/Templates/Tests/AllocatorTest.hpp \
	./src/Templates/Tests/ArrayTest.hpp \
	./src/Templates/Tests/BitsTest.hpp \
	./src/Templates/Tests/ByteOrderTest.hpp \
	./src/Templates/Tests/CircularArrayTest.hpp \
	./src/Templates/Tests/CircularIteratorTest.hpp \
	./src/Templates/Tests/CircularVectorTest.hpp \
	./src/Templates/Tests/HybridVectorTest.hpp \
	./src/Templates/Tests/IntegerIteratorTest.hpp \
	./src/Templates/Tests/ListTest.hpp \
	./src/Templates/Tests/SerializationTest.hpp \
	./src/Templates/Tests/SharedPointerTest.hpp \
	./src/Templates/Tests/StringTest.hpp \
	./src/Templates/Tests/TestAggregator.hpp \
	./src/Templates/Tests/TestClass.hpp \
	./src/Templates/Tests/TupleTest.hpp \
	./src/Templates/Tests/UniquePoiterTest.hpp \
	./src/Templates/Tests/VariantTest.hpp \
	./src/Templates/Tests/VectorTest.hpp \
	./src/Templates/Tests/WideIntTest.hpp \
	./tests/Test.hpp

# sources
SOURCES += \
	./src/Analysers/Ubjson/Array.cpp \
	./src/Analysers/Ubjson/Object.cpp \
	./src/Analysers/Ubjson/Pair.cpp \
	./src/Analysers/Ubjson/String.cpp \
	./src/Bus/MsgInterface.cpp \
	./src/Common/Tests/TestAggregator.cpp \
	./src/Common/Tests/Utils.cpp \
	./src/Filesystem/BasicFile.cpp \
	./src/Filesystem/Project.cpp \
	./src/Filesystem/Session.cpp \
	./src/Process/CommandLine.cpp \
	./src/Streams/DefaultAccumulator.cpp \
	./src/Streams/StreamBase.cpp \
	./src/Templates/Tests/AllocatorTest.cpp \
	./src/Templates/Tests/ArrayTest.cpp \
	./src/Templates/Tests/BitsTest.cpp \
	./src/Templates/Tests/ByteOrderTest.cpp \
	./src/Templates/Tests/CircularArrayTest.cpp \
	./src/Templates/Tests/CircularIteratorTest.cpp \
	./src/Templates/Tests/CircularVectorTest.cpp \
	./src/Templates/Tests/HybridVectorTest.cpp \
	./src/Templates/Tests/IntegerIteratorTest.cpp \
	./src/Templates/Tests/ListTest.cpp \
	./src/Templates/Tests/SerializationTest.cpp \
	./src/Templates/Tests/SharedPointerTest.cpp \
	./src/Templates/Tests/StringTest.cpp \
	./src/Templates/Tests/TestAggregator.cpp \
	./src/Templates/Tests/TestClass.cpp \
	./src/Templates/Tests/TupleTest.cpp \
	./src/Templates/Tests/UniquePoiterTest.cpp \
	./src/Templates/Tests/VariantTest.cpp \
	./src/Templates/Tests/VectorTest.cpp \
	./src/Templates/Tests/WideIntTest.cpp \
	./tests/main.cpp

