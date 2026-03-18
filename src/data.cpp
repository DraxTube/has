// =============================================================================
//  data.cpp  –  Save / Load functions  (converted from Data.bb)
//  Saves to ux0:data/HardTime/ on the Vita memory card
// =============================================================================
#include "values.h"
#include "blitz_compat.h"
#include "players.h"
#include "functions.h"
#include <psp2/io/stat.h>
#include <algorithm>

static const BBString SAVE_ROOT = "ux0:data/HardTime/";

static void EnsureDir(const BBString& path) {
    sceIoMkdir(path.c_str(), 0777);
}

// ---------------------------------------------------------------------------
//  SaveOptions  (mirrors Data.bb SaveOptions())
// ---------------------------------------------------------------------------
void SaveOptions() {
    EnsureDir(SAVE_ROOT);
    BBFile* f = WriteFile(SAVE_ROOT + "Options.dat");
    if (!f || f->fd < 0) return;

    WriteInt(f, optRes);
    WriteInt(f, optPopulation);
    WriteInt(f, optFog);
    WriteInt(f, optShadows);
    WriteInt(f, optFX);
    WriteInt(f, optGore);
    WriteInt(f, keyAttack);
    WriteInt(f, keyDefend);
    WriteInt(f, keyThrow);
    WriteInt(f, keyPickUp);
    WriteInt(f, buttAttack);
    WriteInt(f, buttDefend);
    WriteInt(f, buttThrow);
    WriteInt(f, buttPickUp);
    for (int i = 1; i <= 3; ++i) WriteString(f, gamName[i]);
    CloseFile(f);
}

// ---------------------------------------------------------------------------
//  LoadOptions  (mirrors Data.bb LoadOptions())
// ---------------------------------------------------------------------------
void LoadOptions() {
    BBString path = SAVE_ROOT + "Options.dat";
    if (!FileExists(path)) return;

    BBFile* f = ReadFile(path);
    if (!f || f->fd < 0) return;

    optRes        = ReadInt(f);
    optPopulation = ReadInt(f);
    optFog        = ReadInt(f);
    optShadows    = ReadInt(f);
    optFX         = ReadInt(f);
    optGore       = ReadInt(f);
    keyAttack     = ReadInt(f);
    keyDefend     = ReadInt(f);
    keyThrow      = ReadInt(f);
    keyPickUp     = ReadInt(f);
    buttAttack    = ReadInt(f);
    buttDefend    = ReadInt(f);
    buttThrow     = ReadInt(f);
    buttPickUp    = ReadInt(f);
    for (int i = 1; i <= 3; ++i) gamName[i] = ReadString(f);
    CloseFile(f);
}

// ---------------------------------------------------------------------------
//  SaveProgress  (mirrors Data.bb SaveProgress())
// ---------------------------------------------------------------------------
void SaveProgress() {
    BBString slotDir = SAVE_ROOT + "Data/Slot0" + Str(slot) + "/";
    EnsureDir(SAVE_ROOT + "Data/");
    EnsureDir(slotDir);

    BBFile* f = WriteFile(slotDir + "Progress.dat");
    if (!f || f->fd < 0) return;

    WriteInt(f, no_chars);
    WriteInt(f, gamChar[slot]);
    WriteInt(f, gamPlayer[slot]);
    WriteInt(f, gamLocation[slot]);
    WriteInt(f, gamMoney[slot]);
    WriteInt(f, gamSpeed[slot]);
    WriteInt(f, gamSecs[slot]);
    WriteInt(f, gamMins[slot]);
    WriteInt(f, gamHours[slot]);
    WriteInt(f, gamMission[slot]);
    WriteInt(f, gamClient[slot]);
    WriteInt(f, gamTarget[slot]);
    WriteInt(f, gamDeadline[slot]);
    WriteInt(f, gamReward[slot]);
    WriteInt(f, gamWarrant[slot]);
    WriteInt(f, gamVictim[slot]);
    WriteInt(f, gamItem[slot]);
    WriteInt(f, gamArrival[slot]);
    WriteInt(f, gamFatality[slot]);
    WriteInt(f, gamRelease[slot]);
    WriteInt(f, gamEscape[slot]);
    WriteInt(f, gamGrowth[slot]);
    WriteInt(f, gamBlackout[slot]);
    WriteInt(f, gamBombThreat[slot]);
    WriteInt(f, phonePromo);
    for (int i = 1; i <= NO_PROMOS; ++i) WriteInt(f, promoUsed[i]);
    CloseFile(f);
}

// ---------------------------------------------------------------------------
//  LoadProgress  (mirrors Data.bb LoadProgress())
// ---------------------------------------------------------------------------
void LoadProgress() {
    BBString path = SAVE_ROOT + "Data/Slot0" + Str(slot) + "/Progress.dat";
    if (!FileExists(path)) return;

    BBFile* f = ReadFile(path);
    if (!f || f->fd < 0) return;

    no_chars           = ReadInt(f);
    gamChar[slot]      = ReadInt(f);
    gamPlayer[slot]    = ReadInt(f);
    gamLocation[slot]  = ReadInt(f);
    gamMoney[slot]     = ReadInt(f);
    gamSpeed[slot]     = ReadInt(f);
    gamSecs[slot]      = ReadInt(f);
    gamMins[slot]      = ReadInt(f);
    gamHours[slot]     = ReadInt(f);
    gamMission[slot]   = ReadInt(f);
    gamClient[slot]    = ReadInt(f);
    gamTarget[slot]    = ReadInt(f);
    gamDeadline[slot]  = ReadInt(f);
    gamReward[slot]    = ReadInt(f);
    gamWarrant[slot]   = ReadInt(f);
    gamVictim[slot]    = ReadInt(f);
    gamItem[slot]      = ReadInt(f);
    gamArrival[slot]   = ReadInt(f);
    gamFatality[slot]  = ReadInt(f);
    gamRelease[slot]   = ReadInt(f);
    gamEscape[slot]    = ReadInt(f);
    gamGrowth[slot]    = ReadInt(f);
    gamBlackout[slot]  = ReadInt(f);
    gamBombThreat[slot]= ReadInt(f);
    phonePromo         = ReadInt(f);
    for (int i = 1; i <= NO_PROMOS; ++i) promoUsed[i] = ReadInt(f);
    CloseFile(f);
    
    // Load characters too
    LoadChars();
}

// ---------------------------------------------------------------------------
//  SaveChars  (mirrors Data.bb SaveChars())
// ---------------------------------------------------------------------------
void SaveChars() {
    for (int charId = 1; charId <= no_chars; ++charId) {
        BBString path = SAVE_ROOT + "Data/Slot0" + Str(slot) + "/Character" + Dig(charId, 100) + ".dat";
        BBFile* f = WriteFile(path);
        if (!f || f->fd < 0) continue;

        // appearance
        WriteString(f, charName[charId]);
        WriteInt(f, charSnapped[charId]);
        WriteInt(f, charModel[charId]);
        WriteInt(f, charHeight[charId]);
        WriteInt(f, charSpecs[charId]);
        WriteInt(f, charAccessory[charId]);
        WriteInt(f, charHairStyle[charId]);
        WriteInt(f, charHair[charId]);
        WriteInt(f, charFace[charId]);
        WriteInt(f, charCostume[charId]);
        for (int count = 1; count <= 40; ++count) {
            WriteInt(f, charScar[charId][count]);
        }

        // attributes
        WriteInt(f, charHealth[charId]);
        WriteInt(f, charHP[charId]);
        WriteInt(f, charInjured[charId]);
        WriteInt(f, charStrength[charId]);
        WriteInt(f, charAgility[charId]);
        WriteInt(f, charHappiness[charId]);
        WriteInt(f, charBreakdown[charId]);
        WriteInt(f, charIntelligence[charId]);
        WriteInt(f, charReputation[charId]);
        WriteInt(f, charWeapon[charId]);
        for (int count = 1; count <= 30; ++count) {
            WriteInt(f, charWeapHistory[charId][count]);
        }

        // status
        WriteInt(f, charRole[charId]);
        WriteInt(f, charSentence[charId]);
        WriteInt(f, charCrime[charId]);
        WriteInt(f, charLocation[charId]);
        WriteInt(f, charBlock[charId]);
        WriteInt(f, charCell[charId]);
        WriteInt(f, charExperience[charId]);
        WriteFloat(f, charX[charId]);
        WriteFloat(f, charY[charId]);
        WriteFloat(f, charZ[charId]);
        WriteFloat(f, charA[charId]);

        // relationships
        WriteInt(f, charGang[charId]);
        for (int gang = 1; gang <= 6; ++gang) {
            WriteInt(f, charGangHistory[charId][gang]);
        }
        WriteInt(f, charAttacker[charId]);
        WriteInt(f, charWitness[charId]);
        WriteInt(f, charPromoRef[charId]);
        WriteInt(f, charFollowTim[charId]);
        WriteInt(f, charBribeTim[charId]);
        for (int v = 1; v <= no_chars; ++v) { // Uses NO_CHARS internally bounded by logic
            WriteInt(f, charRelation[charId][v]);
            WriteInt(f, charAngerTim[charId][v]);
            WriteInt(f, charPromo[charId][v]);
        }
        CloseFile(f);
    }
}

// ---------------------------------------------------------------------------
//  LoadChars  (mirrors Data.bb LoadChars())
// ---------------------------------------------------------------------------
void LoadChars() {
    for (int charId = 1; charId <= no_chars; ++charId) {
        BBString path = SAVE_ROOT + "Data/Slot0" + Str(slot) + "/Character" + Dig(charId, 100) + ".dat";
        if (!FileExists(path)) continue;

        BBFile* f = ReadFile(path);
        if (!f || f->fd < 0) continue;

        // appearance
        charName[charId]      = ReadString(f);
        charSnapped[charId]   = ReadInt(f);
        charModel[charId]     = ReadInt(f);
        charHeight[charId]    = ReadInt(f);
        charSpecs[charId]     = ReadInt(f);
        charAccessory[charId] = ReadInt(f);
        charHairStyle[charId] = ReadInt(f);
        charHair[charId]      = ReadInt(f);
        charFace[charId]      = ReadInt(f);
        charCostume[charId]   = ReadInt(f);
        for (int count = 1; count <= 40; ++count) {
            charScar[charId][count] = ReadInt(f);
        }

        // attributes
        charHealth[charId]       = ReadInt(f);
        charHP[charId]           = ReadInt(f);
        charInjured[charId]      = ReadInt(f);
        charStrength[charId]     = ReadInt(f);
        charAgility[charId]      = ReadInt(f);
        charHappiness[charId]    = ReadInt(f);
        charBreakdown[charId]    = ReadInt(f);
        charIntelligence[charId] = ReadInt(f);
        charReputation[charId]   = ReadInt(f);
        charWeapon[charId]       = ReadInt(f);
        for (int count = 1; count <= 30; ++count) {
            charWeapHistory[charId][count] = ReadInt(f);
        }

        // status
        charRole[charId]       = ReadInt(f);
        charSentence[charId]   = ReadInt(f);
        charCrime[charId]      = ReadInt(f);
        charLocation[charId]   = ReadInt(f);
        charBlock[charId]      = ReadInt(f);
        charCell[charId]       = ReadInt(f);
        charExperience[charId] = ReadInt(f);
        charX[charId]          = ReadFloat(f);
        charY[charId]          = ReadFloat(f);
        charZ[charId]          = ReadFloat(f);
        charA[charId]          = ReadFloat(f);

        // relationships
        charGang[charId] = ReadInt(f);
        for (int gang = 1; gang <= 6; ++gang) {
            charGangHistory[charId][gang] = ReadInt(f);
        }
        charAttacker[charId]  = ReadInt(f);
        charWitness[charId]   = ReadInt(f);
        charPromoRef[charId]  = ReadInt(f);
        charFollowTim[charId] = ReadInt(f);
        charBribeTim[charId]  = ReadInt(f);
        for (int v = 1; v <= no_chars; ++v) {
            charRelation[charId][v] = ReadInt(f);
            charAngerTim[charId][v] = ReadInt(f);
            charPromo[charId][v]    = ReadInt(f);
        }
        CloseFile(f);
    }
}
