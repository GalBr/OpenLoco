#pragma once

#include "../Currency.h"
#include "../Map/Map.hpp"
#include "../Objects/SteamObject.h"
#include "Entity.h"

namespace OpenLoco
{
    struct Exhaust;
    struct MoneyEffect;
    struct VehicleCrashParticle;
    struct ExplosionCloud;
    struct Splash;
    struct Fireball;
    struct ExplosionSmoke;
    struct Smoke;

    enum class MiscEntityType : uint8_t
    {
        exhaust = 0, // Steam from the exhaust
        redGreenCurrency = 1,
        windowCurrency = 2,       // currency which is created in the company's colour when a transaction is made (for example the train arrives with a passengers into the station)
        vehicleCrashParticle = 3, // parts (particles) of vehicle after crash which they fall to the ground after explosion
        explosionCloud = 4,       // explosion which is created when two trains (or maybe other vehicles) crash to each other
        splash = 5,               // splash when particles after explosion land to water and creates a splash (exploding train on the bridge)
        fireball = 6,
        explosionSmoke = 7,
        smoke = 8 // Smoke from broken down train
    };

#pragma pack(push, 1)
    struct MiscBase : EntityBase
    {
    private:
        template<typename TType, MiscEntityType TClass>
        TType* as() const
        {
            return getSubType() == TClass ? (TType*)this : nullptr;
        }

    public:
        MiscEntityType getSubType() const { return MiscEntityType(EntityBase::getSubType()); }
        void setSubType(const MiscEntityType newType) { EntityBase::setSubType(static_cast<uint8_t>(newType)); }
        Exhaust* asExhaust() const { return as<Exhaust, MiscEntityType::exhaust>(); }
        MoneyEffect* asRedGreenCurrency() const { return as<MoneyEffect, MiscEntityType::redGreenCurrency>(); }
        MoneyEffect* asWindowCurrency() const { return as<MoneyEffect, MiscEntityType::windowCurrency>(); }
        VehicleCrashParticle* asVehicleCrashParticle() const { return as<VehicleCrashParticle, MiscEntityType::vehicleCrashParticle>(); }
        ExplosionCloud* asExplosionCloud() const { return as<ExplosionCloud, MiscEntityType::explosionCloud>(); }
        Splash* asSplash() const { return as<Splash, MiscEntityType::splash>(); }
        Fireball* asFireball() const { return as<Fireball, MiscEntityType::fireball>(); }
        ExplosionSmoke* asExplosionSmoke() const { return as<ExplosionSmoke, MiscEntityType::explosionSmoke>(); }
        Smoke* asSmoke() const { return as<Smoke, MiscEntityType::smoke>(); }
    };

    struct Exhaust : MiscBase
    {
        uint8_t pad_20[0x26 - 0x20];
        int16_t var_26;
        int16_t var_28;
        uint8_t pad_2A[0x32 - 0x2A];
        int16_t var_32;
        int16_t var_34;
        int16_t var_36;
        uint8_t pad_38[0x49 - 0x38];
        uint8_t object_id; // 0x49

        SteamObject* object() const;

        static Exhaust* create(Map::map_pos3 loc, uint8_t type);
    };

    struct MoneyEffect : MiscBase
    {
        uint8_t pad_20[0x26 - 0x20];
        uint16_t var_26;
        uint16_t var_28;
        int32_t amount; // 0x2A - currency amount in British pounds - different currencies are probably getting recalculated
        int8_t var_2E;  // company colour?
        uint8_t pad_2F[0x44 - 0x2F];
        int16_t offsetX; // 0x44
        uint16_t wiggle; // 0x46

        static MoneyEffect* create(const Map::map_pos3& loc, const CompanyId_t company, const currency32_t amount);
    };

    struct VehicleCrashParticle : MiscBase
    {
        uint8_t pad_20[0x28 - 0x20];
        uint16_t frame; // 0x28
        uint8_t pad_2A[0x2E - 0x2A];
        ColourScheme colourScheme;  // 0x2E
        uint16_t crashedSpriteBase; // 0x30 crashed_sprite_base
    };

    struct ExplosionCloud : MiscBase
    {
        uint8_t pad_20[0x28 - 0x20];
        uint16_t frame; // 0x28
    };

    struct Splash : MiscBase
    {
        uint8_t pad_20[0x28 - 0x20];
        uint16_t frame; // 0x28
    };

    struct Fireball : MiscBase
    {
        uint8_t pad_20[0x28 - 0x20];
        uint16_t frame; // 0x28
    };

    struct ExplosionSmoke : MiscBase
    {
        uint8_t pad_20[0x28 - 0x20];
        uint16_t frame; // 0x28
    };

    struct Smoke : MiscBase
    {
        uint8_t pad_20[0x28 - 0x20];
        uint16_t frame; // 0x28

        static Smoke* create(Map::map_pos3 loc);
    };
#pragma pack(pop)
}