/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

class HardcoreMode : public PlayerScript
{
public:
    explicit HardcoreMode() : PlayerScript("mod-hardcore")
    {

    }

    void OnLogin(Player* player) override
    {
        if (getHardcoreEnabledForPlayer(player))
        {
            if (player->isDead())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session. Light is not on your side, you can't revive anymore.");
            }
            else
            {
                this->sendHarcoreStatus(player);
            }
        }
    }

    void OnLevelChanged(Player* player, uint8 /*oldlevel*/) override
    {
        this->sendHarcoreStatus(player);
    }

    void OnPlayerReleasedGhost(Player* player) override
    {
        if (getHardcoreEnabledForPlayer(player))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session. You'll be a ghost forever now...");
            return;
        }
    }

    void OnPVPKill(Player* /*killer*/, Player* killed) override
    {
        if (getHardcoreEnabledForPlayer(killed))
        {
            ChatHandler(killed->GetSession()).PSendSysMessage("You died during hardcore session... Your killer must be proud.");
            return;
        }
    }

    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* killed) override
    {
        if (getHardcoreEnabledForPlayer(killed))
        {
            ChatHandler(killed->GetSession()).PSendSysMessage("You died during hardcore session... Skills issues.");
            return;
        }
    }

    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (getHardcoreEnabledForPlayer(player))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't get revived.");
            player->KillPlayer();
            return;
        }
    }

    bool CanPlayerUseChat(Player* player, uint32 type, uint32 language, std::string& msg) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            // ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't use chat."); // Keep commented
            return false;
        }
        return true;
    }

    bool CanPlayerUseChat(Player* player, uint32 type, uint32 language, std::string& msg, Player* receiver) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't use chat.");
            return false;
        }
        return true;
    }

    bool CanPlayerUseChat(Player* player, uint32 type, uint32 language, std::string& msg, Group* group) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't use chat.");
            return false;
        }
        return true;
    }

    bool CanPlayerUseChat(Player* player, uint32 type, uint32 language, std::string& msg, Guild* guild) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't use chat.");
            return false;
        }
        return true;
    }

    bool CanPlayerUseChat(Player* player, uint32 type, uint32 language, std::string& msg, Channel* channel) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't use chat.");
            return false;
        }
        return true;
    }

    bool CanGroupInvite(Player* player, std::string& membername) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't invite players to a group.");
            return false;
        }
        return true;
    }

    bool CanGroupAccept(Player* player, Group* group) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session... You can't be a part of a group.");
            return false;
        }
        return true;
    }

private:
    void sendHarcoreStatus(Player* player)
    {
        if (this->getHardcoreEnabledForPlayer(player))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Hardcore is now ENABLED...");
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Hardcore is now DISABLED...");
        }
    }

    bool getHardcoreEnabledForPlayer(Player* player)
    {
        if (sConfigMgr->GetOption<bool>("ModHardcore.Enable", false))
        {
            if (player->GetLevel() >= sConfigMgr->GetOption<int>("ModHardcoreMinLevel.Enable", 1) && player->GetLevel() <= sConfigMgr->GetOption<int>("ModHardcoreMaxLevel.Enable", 79))
            {
                return true;
            }
            return false;
        }
    }
};


void AddSC_mod_harcore()
{
    new HardcoreMode();
}
