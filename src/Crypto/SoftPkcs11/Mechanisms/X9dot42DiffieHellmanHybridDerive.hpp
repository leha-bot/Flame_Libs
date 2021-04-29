#ifndef FLAMEIDE_SRC_CRYPTO_SOFTPKCS11_MECHANISMS_X9_42_DH_HYBRID_DERIVE_HPP
#define FLAMEIDE_SRC_CRYPTO_SOFTPKCS11_MECHANISMS_X9_42_DH_HYBRID_DERIVE_HPP

#include <FlameIDE/../../src/Crypto/SoftPkcs11/Mechanisms/MechanismBase.hpp>

namespace flame_ide
{namespace soft_pkcs11
{namespace mechanisms
{

struct X9dot42DiffieHellmanHybridDerive: public MechanismBase
{
	X9dot42DiffieHellmanHybridDerive() noexcept;

	virtual ~X9dot42DiffieHellmanHybridDerive() noexcept override;

	virtual pkcs11::enums::Mechanism getType() const noexcept override;
};

}}} // namespace flame_ide::soft_pkcs11::mechanisms

#endif // FLAMEIDE_SRC_CRYPTO_SOFTPKCS11_MECHANISMS_X9_42_DH_HYBRID_DERIVE_HPP