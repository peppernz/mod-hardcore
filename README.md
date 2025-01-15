# Simple Hardcore Mod
AzerothCore module to replicate hardcore mode. 
Intended to be bizzlike but with some level configurations.
Need some polishment but feedback is appreciated.

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

ModHardcoGMCanResurrect.Enable
- Description: Enable GM resurrection.
- Default: 0 - Disabled 1 - Enabled

# Installation
Follow official guide: https://www.azerothcore.org/wiki/installation

No sql needed.

# To-Do
- After reviving by angel or spell you keep dead but doesn't look like it, just force ghost form.
- Change client UI texts? like mak'gora duels? maybe.
