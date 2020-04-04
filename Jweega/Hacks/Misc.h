#pragma once

#include "../Memory.h"
#include "../Interfaces.h"
#include "../SDK/FrameStage.h"
#include "../SDK/UserCmd.h"
#include "../SDK/WeaponId.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/Entity.h"
#include "../SDK/Client.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GameMovement.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/Surface.h"
#include "../SDK/ConVar.h"
#include "../SDK/ViewSetup.h"
#include "../SDK/Input.h"

namespace Misc
{
    void edgejump(UserCmd* cmd) noexcept;
    void slowwalk(UserCmd* cmd) noexcept;
    void inverseRagdollGravity() noexcept;
    void updateClanTag(bool = false) noexcept;
    void spectatorList() noexcept;
    void sniperCrosshair() noexcept;
    void recoilCrosshair() noexcept;
    void watermark() noexcept;
    void prepareRevolver(UserCmd*) noexcept;
    void fastPlant(UserCmd*) noexcept;
    void drawBombTimer() noexcept;
    void stealNames() noexcept;
    void disablePanoramablur() noexcept;
    void quickReload(UserCmd*) noexcept;
    bool changeName(bool, const char*, float) noexcept;
    void bunnyHop(UserCmd*) noexcept;
    void fakeBan(bool = false) noexcept;
    void nadePredict() noexcept;
    void quickHealthshot(UserCmd*) noexcept;
    void fixTabletSignal() noexcept;
    void fakePrime() noexcept;
    void killMessage(GameEvent& event) noexcept;

    static float fov{ 0.0f };

    constexpr void drawFov() noexcept
    {
        if (config.misc.drawFOV && interfaces.engine->isInGame()) {
            const auto localPlayer{ interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer()) };
            if (!localPlayer || !localPlayer->isAlive())
                return;

            const auto activeWeapon{ localPlayer->getActiveWeapon() };
            if (!activeWeapon)
                return;

            auto weaponIndex{ getWeaponIndex(activeWeapon->itemDefinitionIndex2()) };
            if (!weaponIndex)
                return;

            auto weaponClass = getWeaponClass(activeWeapon->itemDefinitionIndex2());
            if (!config.aimbot[weaponIndex].enabled)
                weaponIndex = weaponClass;

            if (!config.aimbot[weaponIndex].enabled)
                weaponIndex = 0;

            if (config.aimbot[weaponIndex].enabled) {

                const auto [width, height]{ interfaces.surface->getScreenSize() };

                const auto actualFov{ std::atanf((static_cast<float>(width) / static_cast<float>(height)) * 0.75f * std::tanf(degreesToRadians(fov / 2.f))) };

                if (config.aimbot[weaponIndex].silent)
                    interfaces.surface->setDrawColor(255, 10, 10, 255);
                else
                    interfaces.surface->setDrawColor(10, 255, 10, 255);

                auto radius{ static_cast<int>(std::tanf(degreesToRadians(config.aimbot[weaponIndex].fov) / 2.f) / std::tanf(actualFov) * width) };
                
                interfaces.surface->drawCircle(width / 2, height / 2, radius, ++radius);
            }
        }
    }

    constexpr void fakeDuck(UserCmd* cmd) noexcept
    {
        
        if (config.misc.fakeDuckKey
            && GetAsyncKeyState(config.misc.fakeDuckKey))
            if (const auto localPlayer{ interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer()) };
                localPlayer
                && localPlayer->isAlive())
                if (interfaces.engine->getNetworkChannel()->chokedPackets > (config.misc.chokedPackets / 2))
                    cmd->buttons |= UserCmd::IN_DUCK;
                else
                    cmd->buttons &= ~UserCmd::IN_DUCK;
    }

    constexpr void fakeDuckFix(ViewSetup* setup) noexcept 
    {
        if (config.misc.fakeDuckKey
            && GetAsyncKeyState(config.misc.fakeDuckKey))
            if (const auto localPlayer{ interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer()) };
                localPlayer
                && localPlayer->isAlive()
                && localPlayer->flags() & 1)
            setup->origin.z = localPlayer->getAbsOrigin().z + interfaces.gameMovement->getPlayerViewOffset(false).z;
    }
    void fixMovement(UserCmd* cmd, float yaw) noexcept;
    void antiAfkKick(UserCmd* cmd) noexcept;
    void fixAnimationLOD(FrameStage stage) noexcept;
    void autoPistol(UserCmd* cmd) noexcept;
    void chokePackets(bool& sendPacket) noexcept;
    void autoReload(UserCmd* cmd) noexcept;
    void revealRanks(UserCmd* cmd) noexcept;
    void autoStrafe(UserCmd* cmd) noexcept;
    void removeCrouchCooldown(UserCmd* cmd) noexcept;
    void moonwalk(UserCmd* cmd) noexcept;
    void playHitSound(GameEvent& event) noexcept;
}
