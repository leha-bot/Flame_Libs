#ifndef FLAMEIDE_SRC_CRYPTO_SOFTPKCS11_MECHANISMS_SSL3_MASTER_KEY_DERIVE_DH_HPP
#define FLAMEIDE_SRC_CRYPTO_SOFTPKCS11_MECHANISMS_SSL3_MASTER_KEY_DERIVE_DH_HPP

#include <FlameIDE/../../src/Crypto/SoftPkcs11/Mechanisms/MechanismBase.hpp>

namespace flame_ide
{namespace soft_pkcs11
{namespace mechanisms
{

struct Ssl3MasterKeyDeriveDiffieHellman: public MechanismBase
{
	Ssl3MasterKeyDeriveDiffieHellman() noexcept;

	virtual ~Ssl3MasterKeyDeriveDiffieHellman() noexcept override;

	virtual pkcs11::enums::Mechanism getType() const noexcept override;
};

}}} // namespace flame_ide::soft_pkcs11::mechanisms

#endif // FLAMEIDE_SRC_CRYPTO_SOFTPKCS11_MECHANISMS_SSL3_MASTER_KEY_DERIVE_DH_HPP
