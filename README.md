# Simple Hardcore Mod
AzerothCore module to replicate hardcore mode. 
Intended to be bizzlike but with some level configurations.

# This Fork

Hardcore mode can now be opted out of, every new player receives a token item which keeps them in hardcore mode.
Hardcore deaths are announced to the world!

## Configurable options

- Players can be resurrected by other players or a graveyard spirit healer but will lose their hardcore status. No running back to your corpse and reviving

- A recurrected player is never the same, you will acquire undead racials and lose most of your given ones (configurable).

- Hardcore Playerbots

- Achievements (Requires MPQ update on client, and DBC update on server)

## Notes 

This fork depends on Playerbots fork of Azerothcore. 

Player deaths and major level up milestones are announced to the world.

# Configuration

## Core Settings

**ModHardcore.Enable**
- Description: Enable Hardcore Mod.
- Default: 0 - Disabled, 1 - Enabled

**ModHardcore.TokenItemId**
- Description: Item ID of the hardcore token item. This is an unused NPC item used to track hardcore players. You may need to change this if it conflicts with other customizations.
- Default: 11100

## Level Range Settings

**ModHardcore.StartLevel** and **ModHardcore.EndLevel**
- Description: Set Hardcore Level at min-max range. This allows you to make certain levels not hardcore. Note that players can also opt out themselves at any time by removing the hardcore token item.
- Default: ModHardcore.StartLevel = 1, ModHardcore.EndLevel = 80

Examples:
- Set a range of level 10 to 79 to enable hardcore, so at level 1-9 and 80 hardcore is disabled.
- Set a range of level 1 to 80 to enable hardcore for all levels.

## Resurrection Settings

**ModHardcore.AllowPlayerRez**
- Description: Allow another player to resurrect dead hardcore player.
- Default: 0 - Disabled, 1 - Enabled

**ModHardcore.AllowSpiritRez**
- Description: Allow Spirit Healer at Graveyard to resurrect.
- Default: 0 - Disabled, 1 - Enabled

**ModHardcore.AllowGMRez**
- Description: Enable GM resurrection.
- Default: 0 - Disabled, 1 - Enabled

## Undead Transformation Settings

**ModHardcore.MakeUndeadOnRez**
- Description: Make player undead on resurrection. Change player racials to mostly undead racials. (Experimental)
- Default: 0 - Disabled, 1 - Enabled

**ModHardcore.MakeUndeadOnGMRez**
- Description: Make player undead on GM resurrection.
- Default: 0 - Disabled, 1 - Enabled

## Chat Settings

**ModHardcore.DisableChatWhenDead**
- Description: Make player undead on GM resurrection.
- Default: 0 - Allow Chat, 1 - No Chat

## Playerbot Settings

**ModHardcore.AllowHardcorePlayerBots**
- Description: Allow Hardcore Player Bots. (Experimental)
- Default: 0 - Disabled, 1 - Enabled

## Achievements & Titles

**ModHardcore.AchievementReward**
- Description: Comma separate pairs of (level, achievement Id)
- Default: "60 15050, 70 15051, 80 15052"

**ModHardcore.TitleReward**
- Description: Comma separate pairs of (level, title Id)
ModHardcore.TitleReward = "60 178, 70 179, 80 180"


# Installation
Follow official guide: https://www.azerothcore.org/wiki/installation

Copy the custom base db_world SQL to the usual place for install. This script modifies an unused NPC item into the Hardcore token trinket.

# To-Do
- Provide DBC / patch for achievements and titles
- Improve Instructions
- Fix buggy undead mode (requires dbc updates)


# Credits

- [Zindokar](https://github.com/Zindokar) - mod-hardcore creator
- [ZhengPeiRu21](https://github.com/ZhengPeiRu21) - mod-challenge-modes 