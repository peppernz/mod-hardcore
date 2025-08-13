/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 *
 * Notes:
 * List of unused items: https://pastebin.com/sirbRBJY
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

class HardcoreMode : public PlayerScript
{
    const uint32 DEFAULT_TOKEN_ID = 11100;
public:
    explicit HardcoreMode() : PlayerScript("mod_hardcore")
    {
    }

    void OnPlayerFirstLogin(Player* player) override
    {
        uint32 hcTokenItem = sConfigMgr->GetOption<int>("ModHardcore.TokenItemId", DEFAULT_TOKEN_ID);
        player->AddItem(hcTokenItem, 1);
    }

    void OnPlayerLogin(Player* player) override
    {
        if (getHardcoreEnabledForPlayer(player))
        {
            if (player->isDead())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You died during hardcore session, so you are a permanent ghost.");
            }
            else
            {
                this->sendHarcoreStatus(player);
            }
        }
    }

    void OnPlayerLevelChanged(Player* player, uint8 /*oldlevel*/) override
    {
        if (getHardcoreEnabledForPlayer(player))
        {
            //this->sendHarcoreStatus(player);
            int level = player->GetLevel();
            if (level == 10) {
                sendWorldAnnouncement(Acore::StringFormat("{} has made it to level {}!", player->GetName(), level));
            } else if (level == 20) {
                sendWorldAnnouncement(Acore::StringFormat("{} has made it to level {}!", player->GetName(), level));
            } else if (level == 30) {
                sendWorldAnnouncement(Acore::StringFormat("{} has made it to level {}!", player->GetName(), level));
            } else if (level == 40) {
                sendWorldAnnouncement(Acore::StringFormat("{} has made it to level {}!", player->GetName(), level));
            } else if (level == 50) {
                sendWorldAnnouncement(Acore::StringFormat("{} has made it to level {}!", player->GetName(), level));
            } else if (level == 60) {
                sendWorldAnnouncement(Acore::StringFormat("{} is a legend and is now level {}!!", player->GetName(), level));
            }
        }
    }

    void OnPlayerJustDied(Player* /*player*/) override
    {
        // if (getHardcoreEnabledForPlayer(player))
        // {
        //     Group* group = player->GetGroup();
        //     if (group)
        //     {
        //         ChatHandler(player->GetSession()).PSendSysMessage("Leaving group... You can't be a part of living people anymore.");
        //         group->RemoveMember(player->GetGUID());
        //     }
        // }
    }

    void OnPlayerReleasedGhost(Player* player) override
    {
        if (getHardcoreEnabledForPlayer(player))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You'll be a ghost forever...unless you find help");
            return;
        }
    }

    void OnPlayerPVPKill(Player* killer, Player* killed) override
    {
        if (getHardcoreEnabledForPlayer(killed))
        {
            ChatHandler(killed->GetSession()).PSendSysMessage("You have died in Hardcore mode.");
            if (killed->GetGUID() != killer->GetGUID())
            {
                sendWorldAnnouncement(Acore::StringFormat("Hardcore level {} player {} was killed in a dual to the death by {}!", killed->GetLevel(), killed->GetName(), killer->GetName()));
            }
        }
    }

    void OnPlayerKilledByCreature(Creature* killer, Player* killed) override
    {
        if (getHardcoreEnabledForPlayer(killed))
        {
            sendWorldAnnouncement(Acore::StringFormat("Hardcore level {} player {} was killed by {}!", killed->GetLevel(), killed->GetName(), killer->GetName()));
            ChatHandler(killed->GetSession()).PSendSysMessage("You died during a hardcore session...");
            return;
        }
    }

    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    { // We keep this function just to prevent some exploits for reviving
        if (getHardcoreEnabledForPlayer(player))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You have been revived while playing hardcore. Hardcore mode is now off. You are forsaken.");
            return;
        }
    }

    bool OnPlayerCanUseChat(Player* player, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            return false;
        }
        return true;
    }

    bool OnPlayerCanUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Player* /*receiver*/) override
    {
        //if (getHardcoreEnabledForPlayer(player) && player->isDead())
        //{
        //    return false;
        //}
        return true;
    }

    bool OnPlayerCanUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Group* /*group*/) override
    {
        //if (getHardcoreEnabledForPlayer(player) && player->isDead())
        //{
        //    return false;
        //}
        return true;
    }

    bool OnPlayerCanUseChat(Player* /*player*/, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Guild* /*guild*/) override
    {
        //if (getHardcoreEnabledForPlayer(player) && player->isDead())
        //{
        //    return false;
        //}
        return true;
    }

    bool OnPlayerCanUseChat(Player* player, uint32 /*type*/, uint32 /*language*/, std::string& /*msg*/, Channel* /*channel*/) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            return false;
        }
        return true;
    }

    bool OnPlayerCanGroupInvite(Player* player, std::string& /*membername*/) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You can't invite players to a group while dead.");
            return false;
        }
        return true;
    }

    bool OnPlayerCanGroupAccept(Player* player, Group* /*group*/) override
    {
        if (getHardcoreEnabledForPlayer(player) && player->isDead())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You can't be a part of a group.");
            return false;
        }
        return true;
    }

private:

    void sendWorldAnnouncement(std::string message)
    {

        // Send localized messages to all sessions
        ChatHandler(nullptr).DoForAllValidSessions([&](Player* player)
        {


            // Check if there is a localized message if not use default one.
            if (message.empty())
                return;

            // Send the localized or fallback message
            ChatHandler(player->GetSession()).SendWorldTextOptional(message, ANNOUNCER_FLAG_DISABLE_AUTOBROADCAST);
        });

    }

    void sendHarcoreStatus(Player* player)
    {
        if (player->IsGameMaster())
        {
            return;
        }
        if (this->getHardcoreEnabledForPlayer(player))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Hardcore is enabled, good luck.");
        }
    }

    bool getHardcoreEnabledForPlayer(Player* player)
    {
        if (player->IsGameMaster()) 
	{	       
	    return false;
	}	
	if (sConfigMgr->GetOption<bool>("ModHardcore.Enable", false))
        {
            if (player->GetLevel() >= sConfigMgr->GetOption<int>("ModHardcoreMinLevel.Enable", 1) && player->GetLevel() <= sConfigMgr->GetOption<int>("ModHardcoreMaxLevel.Enable", 79))
            {
                // Has the HC item, will check bank
	        uint32 hcTokenItem = sConfigMgr->GetOption<int>("ModHardcore.TokenItemId", DEFAULT_TOKEN_ID);
                if (player->HasItemCount(hcTokenItem, 1, true)) 
	        {
		    return true;
		} 
            } 
        }
        return false;
    }


};

class HardModeServerScript : ServerScript
{
    const uint32 DEFAULT_TOKEN_ID = 11100;
public:
    HardModeServerScript() : ServerScript("mod_hardcore")
    {
    }

    bool CanPacketReceive(WorldSession* session, WorldPacket& packet) override
    {
        if (!sConfigMgr->GetOption<bool>("ModHardcore.Enable", false))
        {
            return true;
        }

        if (!session)
        {
            return true;
        }

        auto player = session->GetPlayer();
        if (!player || !player->isDead() || player->IsGameMaster() || !getHardcoreEnabledForPlayer(player))
        {
            return true;
        }

        if (player->GetLevel() >= sConfigMgr->GetOption<int>("ModHardcoreMinLevel.Enable", 1) && player->GetLevel() <= sConfigMgr->GetOption<int>("ModHardcoreMaxLevel.Enable", 79))
        {
            auto opCode = packet.GetOpcode();
            switch (opCode)
            {
                case SMSG_PRE_RESURRECT: // No idea
                case CMSG_HEARTH_AND_RESURRECT: // No idea
                case CMSG_RECLAIM_CORPSE:  // Reviving going to corpse
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You cannot self resurrect in Hardcore mode. Travel as a ghost or find help.");
                    return false;
                }
                case SMSG_RESURRECT_REQUEST:
                case CMSG_RESURRECT_RESPONSE: // Someone reviving your corpse
                case CMSG_SPIRIT_HEALER_ACTIVATE: // Spirit talking
                case SMSG_SPIRIT_HEALER_CONFIRM: // Spirit reviving, keep both spirit packets
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("If you accept being resurrected you will never be the same. Hardcore mode will be forfeited.");

                    uint32 hcTokenItem = sConfigMgr->GetOption<int>("ModHardcore.TokenItemId", DEFAULT_TOKEN_ID);
                    //Item* item = player->GetItemByEntry(hcTokenItem);
                    player->DestroyItemCount(hcTokenItem, 1, true, true);
                    //ObjectGuid itemGuid = item->GetGUID();
                    //uint64 playerGuid = player->GetGUID()
                    //std::string updateQuery = Acore::StringFormat("DELETE FROM `character_inventory` WHERE `item_guid` = {} AND `guid` = {};", itemGuid, playerGuid );
                    //CharacterDatabase.Execute(updateQuery.c_str());

                    makeUndead(player);
                    return true;
                }
                case CMSG_GM_RESURRECT:
                {
                    if (!sConfigMgr->GetOption<bool>("ModHardcoreGMCanResurrect.Enable", false))
                    {
                        return false;
                    }
                    break;
                }
            }
        }

        return true;
    }
private:

    // duplicate fn
    bool getHardcoreEnabledForPlayer(Player* player)
    {
        if (player->IsGameMaster())
        {
            return false;
        }
        if (sConfigMgr->GetOption<bool>("ModHardcore.Enable", false))
        {
            if (player->GetLevel() >= sConfigMgr->GetOption<int>("ModHardcoreMinLevel.Enable", 1) && player->GetLevel() <= sConfigMgr->GetOption<int>("ModHardcoreMaxLevel.Enable", 79))
            {
                // Has the HC item, will check bank
                uint32 hcTokenItem = sConfigMgr->GetOption<int>("ModHardcore.TokenItemId", DEFAULT_TOKEN_ID);
                if (player->HasItemCount(hcTokenItem, 1, true))
                {
                    return true;
                }
            }
        }
        return false;
    }

    void makeUndead(Player* player) {

        if (player->GetSession()->IsBot()) {
            return;
        }

        if (player->getRace() == FORM_UNDEAD)
        {
            player->removeSpell(20579, SPEC_MASK_ALL, false);  // unlearn Shadow Resistance
        }
        else
        {
            RemoveAllRacials(player);
            AddUndeadRacials(player);
        }
        player->CastSpell(player, 20577); // Cannibalize.
        player->SetDrunkValue(128);
        // player->AddAura(SPELL_AURA_MOD_SHAPESHIFT, player);
    }

    void AddUndeadRacials(Player* player) {
        // Undead:
        player->learnSpell(20577, false); // Cannibalize
        //player->learnSpell(20579, false); // Shadow Resistance
        player->learnSpell(5227, false);  // Underwater Breating
        player->learnSpell(7744, false);  // Will of the Forsaken
    }

    // New Function - remove all existing racials
    void RemoveAllRacials(Player* player)
    {
        // Draenei:
       // player->removeSpell(28875, SPEC_MASK_ALL, false); // unlearn Gemcutting
        player->removeSpell(6562, SPEC_MASK_ALL, false);  // unlearn Heroic Presence (Warrior, Paladin, Hunter, DK)
        player->removeSpell(28878, SPEC_MASK_ALL, false); // unlearn Heroic Presence (Priest, Shaman)
        player->removeSpell(28880, SPEC_MASK_ALL, false); // unlearn Gift of Naaru (Warrior, increased by AP)
        player->removeSpell(59542, SPEC_MASK_ALL, false); // unlearn Gift of Naaru (Paladin, increase by AP or SP, whichever is higher)
        player->removeSpell(59543, SPEC_MASK_ALL, false); // unlearn Gift of Naaru (Hunter, increase by AP)
        player->removeSpell(59544, SPEC_MASK_ALL, false); // unlearn Gift of Naaru (Priest, increase by SP)
        player->removeSpell(59545, SPEC_MASK_ALL, false); // unlearn Gift of Naaru (DK, increased by AP)
        player->removeSpell(59547, SPEC_MASK_ALL, false); // unlearn Gift of Narru (Shaman, increase by AP or SP, whichever is higher)
        player->removeSpell(59548, SPEC_MASK_ALL, false); // unlearn Gift of Naaru (Mage, increase by SP)
        player->removeSpell(59221, SPEC_MASK_ALL, false); // unlearn Shadow Resistance (Warrior)
        player->removeSpell(59535, SPEC_MASK_ALL, false); // unlearn Shadow Resistance (Paladin)
        player->removeSpell(59536, SPEC_MASK_ALL, false); // unlearn Shadow Resistance (Hunter)
        player->removeSpell(59538, SPEC_MASK_ALL, false); // unlearn Shadow Resistance (Priest)
        player->removeSpell(59539, SPEC_MASK_ALL, false); // unlearn Shadow Resistance (DK)
        player->removeSpell(59540, SPEC_MASK_ALL, false); // unlearn Shadow Resistance (Shaman)
        player->removeSpell(59541, SPEC_MASK_ALL, false); // unlearn Shadow Resistance (Mage)

        // Dwarf:
        player->removeSpell(2481, SPEC_MASK_ALL, false);  // unlearn Find Treasure
        player->removeSpell(20596, SPEC_MASK_ALL, false); // unlearn Frost Resistance
        player->removeSpell(20595, SPEC_MASK_ALL, false); // unlearn Gun Specialization
        player->removeSpell(59224, SPEC_MASK_ALL, false); // unlearn Mace Specialization
        //player->removeSpell(20594, SPEC_MASK_ALL, false); // unlearn Stoneform

        // Gnome:
        player->removeSpell(20592, SPEC_MASK_ALL, false); // unlearn Arcane Resistance
        //player->removeSpell(20593, SPEC_MASK_ALL, false); // unlearn Engineering Specialization
        player->removeSpell(20589, SPEC_MASK_ALL, false); // unlearn Escape Artist
        player->removeSpell(20591, SPEC_MASK_ALL, false); // unlearn Expansive Mind

        // Human:
        player->removeSpell(20599, SPEC_MASK_ALL, false); // unlearn Diplomacy
        player->removeSpell(59752, SPEC_MASK_ALL, false); // unlearn Every man for himself
        player->removeSpell(20864, SPEC_MASK_ALL, false); // unlearn Mace Specialization
        //player->removeSpell(58985, SPEC_MASK_ALL, false); // unlearn Perception
        player->removeSpell(20597, SPEC_MASK_ALL, false); // unlearn Sword Specialization
        player->removeSpell(20598, SPEC_MASK_ALL, false); // unlearn The Human Spirit

        // Night Elf:
        player->removeSpell(20583, SPEC_MASK_ALL, false); // unlearn Nature Resistance
        player->removeSpell(20582, SPEC_MASK_ALL, false); // unlearn Quickness
        //player->removeSpell(58984, SPEC_MASK_ALL, false); // unlearn Shadowmeld
        player->removeSpell(20585, SPEC_MASK_ALL, false); // unlearn Wisp Spirit
        player->removeSpell(21009, SPEC_MASK_ALL, false); // unlearn Elusiveness

        // Orc:
        player->removeSpell(20574, SPEC_MASK_ALL, false); // unlearn Axe Specialization
        //player->removeSpell(20573, SPEC_MASK_ALL, false); // unlearn Hardiness
        player->removeSpell(54562, SPEC_MASK_ALL, false); // unlearn Command (DK)
        player->removeSpell(20576, SPEC_MASK_ALL, false); // unlearn Command (Hunter)
        player->removeSpell(65222, SPEC_MASK_ALL, false); // unlearn Command (Shaman)
        player->removeSpell(20575, SPEC_MASK_ALL, false); // unlearn Command (Warlock)
        player->removeSpell(21563, SPEC_MASK_ALL, false); // unlearn Command (non-pet class)
        player->removeSpell(20572, SPEC_MASK_ALL, false); // unlearn Blood Fury (AP only)
        player->removeSpell(33697, SPEC_MASK_ALL, false); // unlearn Blood fury (AP + SP)
        player->removeSpell(33702, SPEC_MASK_ALL, false); // unlearn Blood Fury (SP only)

        // Tauren:
        player->removeSpell(20552, SPEC_MASK_ALL, false); // unlearn Cultivation
        player->removeSpell(20550, SPEC_MASK_ALL, false); // unlearn Endurance
        player->removeSpell(20551, SPEC_MASK_ALL, false); // unlearn Nature Resistance
        //player->removeSpell(20549, SPEC_MASK_ALL, false); // unlearn Warstomp

        // Troll:
        player->removeSpell(20557, SPEC_MASK_ALL, false); // unlearn Beast Slaying
        player->removeSpell(26297, SPEC_MASK_ALL, false); // unlearn Berserking
        player->removeSpell(26290, SPEC_MASK_ALL, false); // unlearn Bow Specialization
        player->removeSpell(20558, SPEC_MASK_ALL, false); // unlearn Throwing Specialization
        //player->removeSpell(58943, SPEC_MASK_ALL, false); // unlearn Da Voodoo Shuffle
        player->removeSpell(20555, SPEC_MASK_ALL, false); // unlearn Regeneration

        // Undead:
        player->removeSpell(20577, SPEC_MASK_ALL, false); // unlearn Cannibalize
        player->removeSpell(20579, SPEC_MASK_ALL, false); // unlearn Shadow Resistance
        player->removeSpell(5227, SPEC_MASK_ALL, false);  // unlearn Underwater Breating
        //player->removeSpell(7744, SPEC_MASK_ALL, false);  // unlearn Will of the Forsaken

        // Blood Elf:
        //player->removeSpell(28877, SPEC_MASK_ALL, false); // unlearn Arcane Affinity
        player->removeSpell(28730, SPEC_MASK_ALL, false); // unlearn Arcane Torrent (mana)
        player->removeSpell(25046, SPEC_MASK_ALL, false); // unlearn Arcane Torrent (energy)
        player->removeSpell(50613, SPEC_MASK_ALL, false); // unlearn Arcane Torrent (runic power)
        player->removeSpell(822, SPEC_MASK_ALL, false);   // unlearn Magic Resistance
    }
};


void AddSC_mod_hardcore()
{
    new HardcoreMode();
    new HardModeServerScript();
}
