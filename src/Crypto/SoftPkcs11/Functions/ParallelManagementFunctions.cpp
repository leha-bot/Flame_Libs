#include <FlameIDE/../../src/Crypto/SoftPkcs11/Functions/ParallelManagementFunctions.hpp>

#include <FlameIDE/Crypto/Pkcs11/Types/Enums.hpp>

namespace flame_ide
{namespace soft_pkcs11
{namespace functions
{namespace parallel_management
{

pkcs11::value_types::ReturnType getFunctionStatus(
		pkcs11::value_types::SessionHandle session
)
{
	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

pkcs11::value_types::ReturnType cancelStatus(
		pkcs11::value_types::SessionHandle session
)
{
	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

pkcs11::value_types::ReturnType waitForSlotEvent(
		pkcs11::value_types::Flags flags
		, pkcs11::value_types::SlotIdPtr slotId
		, pkcs11::value_types::ValuePtr
)
{
	return pkcs11::enums::value(pkcs11::enums::ReturnType::OK);
}

}}}} // flame_ide::soft_pkcs11::functions::namespace parallel_management