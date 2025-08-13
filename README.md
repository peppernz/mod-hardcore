# Simple Hardcore Mod
AzerothCore module to replicate hardcore mode. 
Intended to be bizzlike but with some level configurations.

# This Fork
Hardcore mode can now be opted out of, every new player receives a token item which keeps them in hardcore mode.

Players can be resurrected by other players or the spirit guardian but will lose their hardcore status. No running back to your corpse and reviving

A recurrected player is never the same, you will acquire undead racials and lose most of your given ones.

This fork does depend on Playerbots version of Azerothcore. By default player bots are also hardcore. (will make this configurable in future)

# Configuration
ModHardcore.Enable
- Description: Enable Hardcore Mod.
- Default: 0 - Disabled 1 - Enabled

ModHardcoreMinLevel.Enable and ModHardcoreMaxLevel.Enable
- Description: Disable Hardcore Level at Min-Max range.
- Default: ModHardcoreMinLevel.Enable = 10 ModHardcoreMaxLevel.Enable = 79

Examples:
- Set a range of level 10 to 79 to enable hardcore, so at level 1-9 and 80 hardcore is disabled.
- Set a range of level 1 to 80 to enable hardcore all levels.

ModHardcoreGMCanResurrect.Enable
- Description: Enable GM resurrection.
- Default: 0 - Disabled 1 - Enabled

# Installation
Follow official guide: https://www.azerothcore.org/wiki/installation

No sql needed.

# To-Do
- Change client UI texts? like mak'gora duels? maybe.
