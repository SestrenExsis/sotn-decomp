#include "nz0.h"
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/39908", TestCollisions);

// DECOMP_ME_WIP EntityNumericDamage https://decomp.me/scratch/PMg4y 99.82%
// WIP
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/39908", EntityNumericDamage);
#else
// At decimal values above 9999, 0000 through 0999 start showing
// At hex value 2AF8, other sprite data starts creeping in
// 0x4000 is the critical flag, and requires another line to display text
extern u16 D_80180C28;
extern u16 D_80181950[];

/*
0x670F is the highest number that still displays properly
Numbers displayed whenever Alucard damages an enemy
The number gets translated into binary decimals for each digit
For normal damage:
    - alternates between yellow gradient and red gradient every frame
    - starts out skewed, moves to normal over time
For critical damage:
    - displays two lines, with the first line reading "CRITICAL!!"
Floats upward
Goes transparent at the end
*/
void EntityNumericDamage(Entity* entity) {
    Primitive* prim;
    s16 firstPrimIndex;
    u16 subId;
    u16 timer;
    s16 xOffset;
    u16 tempXPos1;
    u32 tempXPos2;
    u16 digitIndex;
    u16 tempYPos1;
    u16 paletteIndex;
    u32 tempEdge;
    s16 tempB2;
    u16 tempBlendMode;

    u32 tempH;
    u16 tempI;
    u16 tempJ;
    u16 tempL;
    u32 tempM;
    u16 tempN;

    u16 total;
    u16 digit;

    Multi tempMultiA;
    Multi tempMultiB;

    union {
        u16 modeU16;
        struct {
            u8 unk0;
            u8 unk1;
        } modeU8;
    } * tempUnk7E;

    if (entity->ext.generic.unk88.U16.unk0 != 0) {
        entity->posX.val = g_Entities[0].posX.val;
        entity->posY.val = g_Entities[0].posY.val + 0xFFF00000;
    }
    switch (entity->step) {
    case 0:
        if (entity->step_s == 9) {
            DestroyEntity(entity);
            return;
        } else {
            subId = entity->subId;
            tempUnk7E = &entity->ext.generic.unk7E;
            if (entity->step_s == 0) {
                InitializeEntity(&D_80180C28);
                entity->step = 0;
                // Convert the number into binary decimal and store each of the
                // 4 digits separately entity->unk7E.modeU16 stores how many
                // digits will be displayed (e.g., 3 for "255", 2 for "12", 1
                // for "0", etc.) entity->unk7C.s seems to also store how many
                // digits will be displayed? entity->unk80 stores the individual
                // digits, up to 4 entity->unk84 stores how long the digits are
                // on screen for, in frames
                if (subId == 0xC000) {
                    // GUARD has a single element to display
                    entity->ext.generic.unk7C.s += 1;
                } else {
                    total = subId & 0x3FFF;

                    // 1000s place
                    digit = total / 1000;
                    if (digit != 0) {
                        entity->ext.generic.unk7C.s += 1;
                        entity->ext.generic.unk7E.modeU16 += 1;
                    }
                    total -= 1000 * digit;
                    entity->ext.generic.unk80.modeS8.unk0 = digit;

                    // 100s place
                    digit = total / 100;
                    if ((digit != 0) ||
                        (entity->ext.generic.unk7E.modeU16 != 0)) {
                        entity->ext.generic.unk7C.s += 1;
                        entity->ext.generic.unk7E.modeU16 += 1;
                    }
                    total -= 100 * digit;
                    entity->ext.generic.unk80.modeS8.unk1 = digit;

                    // 10s place
                    digit = total / 10;
                    if ((digit != 0) || ((*tempUnk7E).modeU16 != 0)) {
                        entity->ext.generic.unk7C.s += 1;
                        (*tempUnk7E).modeU16 += 1;
                    }
                    total -= 10 * digit;
                    entity->ext.generic.unk80.modeS8.unk2 = digit;

                    // 1s place
                    digit = total / 1;
                    if (1) {
                        entity->ext.generic.unk7C.s += 1;
                        (*tempUnk7E).modeU16 += 1;
                    }
                    total -= 1 * digit;
                    entity->ext.generic.unk80.modeS8.unk3 = (total = digit);

                    if (subId & 0x4000) // Is it a critical hit?
                    {
                        entity->ext.generic.unk7C.s += 1;
                    }
                }
            }
            paletteIndex = subId;
            firstPrimIndex =
                g_api.AllocPrimitives(4, entity->ext.generic.unk7C.u);
            if (firstPrimIndex != 0) {
                prim = &g_PrimBuf[firstPrimIndex];
                entity->flags = entity->flags | 0x800000;
                entity->firstPolygonIndex = firstPrimIndex;
                digitIndex = (4 - (*tempUnk7E).modeU16);
                xOffset = -2 * (*tempUnk7E).modeU16; // Center the text?
                tempJ = 0; // TODO(sestren): Swap a1 for t2
                while (prim != NULL) {
                    if (tempJ == 0) {
                        tempJ += 1;
                        if ((subId & 0xC000) == 0xC000) {
                            // Select GUARD from the spritesheet
                            prim->u0 = prim->u2 = 0x43;
                            prim->u1 = prim->u3 = 0x59;
                            prim->v0 = prim->v1 = 0x4A;
                            prim->v2 = prim->v3 = 0x52;
                            *(u16*)&prim->r2 = 0xB;
                            *(u16*)&prim->b2 = 5;
                            *(u16*)&prim->r1 = 0; // ADDRESS 2e0 or 1a68
                            *(s16*)&prim->b1 = -0x10;
                        } else if ((subId & 0x4000) != 0) {
                            // Select CRITICAL!! from the spritesheet
                            prim->u0 = prim->u2 = 0x20;
                            prim->u1 = prim->u3 = 0x42;
                            prim->v0 = prim->v1 = 0x4A;
                            prim->v2 = prim->v3 = 0x52;
                            *(u16*)&prim->r2 = 0x11;
                            *(u16*)&prim->b2 = 5;
                            *(u16*)&prim->r1 = 0; // ADDRESS 328 or 1ab0
                            *(s16*)&prim->b1 = -0x18;
                        } else {
                            continue;
                        }
                    } else {
                        *(u16*)&prim->r1 = xOffset; // ADDRESS 334 or 1ac0
                        *(s16*)&prim->b1 = -0x10;
                        if (subId & 0x4000) {
                            *(u16*)&prim->r2 = 3;
                            *(u16*)&prim->b2 = 5;
                        } else {
                            *(u16*)&prim->r2 = 0x17;
                            *(u16*)&prim->b2 = 0;
                        }
                        tempH = &(entity->ext.generic.unk80.modeS8);
                        digit = *(u8*)(tempH + digitIndex);
                        if (digit != 0) {
                            // Offset for digits 1-9
                            prim->u0 = prim->u2 = 8 * digit + 0x18;
                            prim->u1 = prim->u3 = 8 * digit + 0x1E;
                        } else {
                            // Offset for digit 0
                            prim->u0 = prim->u2 = 0x68;
                            prim->u1 = prim->u3 = 0x6E;
                        }
                        xOffset += 4;
                        digitIndex += 1;
                        prim->v0 = prim->v1 = 0x40;
                        prim->v2 = prim->v3 = 0x49;
                    }
                    prim->tpage = 0x1A;
                    prim->priority = 0x1F8;
                    prim->blendMode = 8; // Invisible?
                    prim = prim->next;
                }
                entity->step_s = 0;
                entity->ext.generic.unk84.S16.unk0 =
                    64; // how long the digits are on screen for in frames
                entity->step += 1;
            }
            entity->step_s += 1;
        }
        break;
    case 1:
        timer = (entity->ext.generic.unk84.U16.unk0 -= 1);
        if (timer <= 0) {
            DestroyEntity(entity);
            return;
        }
        tempJ = timer & 1;
        // Color palette based on whether it's a critical, a guard, or normal
        // Color palette alternates every frame to create a flashing effect
        paletteIndex = (entity->subId >> 0xD) & 6;
        total = D_80181950[timer & 1 | paletteIndex];
        prim = &g_PrimBuf[entity->firstPolygonIndex];
        if ((paletteIndex != 0) && (paletteIndex != 4)) {
            while (prim != NULL) {
                if (entity->ext.generic.unk84.U16.unk0 >= 60) {
                    *(u16*)&prim->r2 += 1;
                    *(u16*)&prim->b2 += 1;
                } else if (entity->ext.generic.unk84.U16.unk0 >= 56) {
                    *(u16*)&prim->r2 -= 1;
                    *(u16*)&prim->b2 -= 1;
                }
                tempXPos1 = entity->posX.i.hi + *(s32*)&prim->r1;
                tempYPos1 = entity->posY.i.hi + *(s32*)&prim->b1;
                prim->x0 = prim->x2 = tempXPos1 - *(s32*)&prim->r2;
                prim->x1 = prim->x3 = tempXPos1 + *(s32*)&prim->r2;
                // subId = tempYPos1 - (*(s32*)&prim->b2); // TODO(sestren):
                // Remove this?
                prim->y0 = prim->y1 = tempYPos1 - *(s32*)&prim->b2;
                prim->y2 = prim->y3 = tempYPos1 + *(s32*)&prim->b2;
                prim->clut = total;
                tempMultiA = entity->ext.generic.unk84;
                prim->blendMode = (tempMultiA.U16.unk0 >= 6) ? 2 : 0x13;
                prim = prim->next;
            }
            if (entity->ext.generic.unk88.U16.unk0 == 0) {
                entity->posY.val -= 0x8000;
            }
        } else {
            while (prim != NULL) {
                if (*(u16*)&prim->r2 >= 4) {
                    *(s16*)&prim->r2 -= 1;
                }
                if (*(u16*)&prim->b2 < 10) {
                    *(u16*)&prim->b2 += 1;
                }
                tempXPos2 =
                    *(u16*)&entity->posX.i.hi + *(u16*)&prim->r1; // (x + r1)
                tempYPos1 =
                    *(u16*)&entity->posY.i.hi + *(u16*)&prim->b1; // (y + b1)
                prim->x0 = tempXPos2 - *(u16*)&prim->r2; // (x + r1) - r2
                prim->x1 = tempXPos2 + *(u16*)&prim->r2; // (x + r1) + r2
                prim->clut = total;
                tempM = ((*(u16*)&prim->b2) - 5);
                prim->y0 = prim->y1 =
                    tempYPos1 - tempM; // (y + b1) + (b2 - 5) // IS IT - OR +?
                tempJ = prim->y3 = tempYPos1 - tempM + (*(u16*)&prim->b2);
                prim->y2 = tempJ;         // (y + b1) - (b2 - 5) + b2
                prim->x2 = tempXPos2 - 3; // (x + r1) - 3
                prim->x3 = tempXPos2 + 3; // (x + r1) + 3
                tempMultiB = entity->ext.generic.unk84;
                prim->blendMode = (tempMultiB.U16.unk0 >= 6) ? 2 : 0x13;
                prim = prim->next;
            }
            entity->posY.val -= 0x8000;
        }
    }
}
#endif

#include "../create_entity_from_layout.h"

void CreateEntityWhenInVerticalRange(LayoutEntity* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Camera.posY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = layoutObj->posY;
    if (posY < yClose) {
        return;
    }

    if (yFar < posY) {
        return;
    }

    switch (layoutObj->entityId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        if (entity->entityId == E_NONE) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutEntity* layoutObj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;

    posX = g_Camera.posX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = layoutObj->posX;
    if (posX < xClose) {
        return;
    }

    if (xFar < posX) {
        return;
    }

    switch (layoutObj->entityId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        if (entity->entityId == E_NONE) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void func_801BB3B8(s16 arg0) {
    while (true) {
        if ((D_801CAA74->posX != 0xFFFE) && (D_801CAA74->posX >= (s32)arg0)) {
            break;
        }
        D_801CAA74++;
    }
}

void func_801BB404(s16 arg0) {
    while (true) {
        if (!(D_801CAA74->posX == 0xFFFF) &&
            (((s32)arg0 >= D_801CAA74->posX) || (D_801CAA74->posX == 0xFFFE))) {
            break;
        }
        D_801CAA74--;
    }
}

void func_801BB45C(s16 arg0) {
    s32 expected;
    u8 flag;

    if (D_801CAA7C != 0) {
        func_801BB3B8(arg0 - D_80097908);
        D_801CAA7C = 0;
    }

    while (true) {
        if ((D_801CAA74->posX == 0xFFFF) || (arg0 < D_801CAA74->posX)) {
            return;
        }

        expected = 0;
        flag = (D_801CAA74->entityRoomIndex >> 8) + 0xFF;
        if ((flag == 0xFF) ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(D_801CAA74);
        }
        D_801CAA74++;
    }
}

void func_801BB558(s16 arg0) {
    u8 flag;
    s32 expected;

    if (arg0 < 0) {
        arg0 = 0;
    }

    if (D_801CAA7C == 0) {
        func_801BB404(arg0 - D_80097908);
        D_801CAA7C = 1;
    }

    while (true) {
        if ((D_801CAA74->posX == 0xFFFE) || (arg0 > D_801CAA74->posX)) {
            return;
        }

        expected = 0;
        flag = (D_801CAA74->entityRoomIndex >> 8) + 0xFF;
        if ((flag == 0xFF) ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(D_801CAA74);
        }
        D_801CAA74--;
    }
}

void func_801BB66C(s16 arg0) {
    while (true) {
        if ((D_801CAA78[1] != 0xFFFE) && (D_801CAA78[1] >= (s32)arg0)) {
            break;
        }
        D_801CAA78 += 5;
    }
}

void func_801BB6B8(s16 arg0) {
    while (true) {
        if (!(D_801CAA78[1] == 0xFFFF) &&
            (((s32)arg0 >= D_801CAA78[1]) || (D_801CAA78[1] == 0xFFFE))) {
            break;
        }
        D_801CAA78 -= 5;
    }
}

void func_801BB710(s16 arg0) {
    u8 flag;
    s32 expected;

    if (D_801CAA80 != 0) {
        func_801BB66C(arg0 - D_8009790C);
        D_801CAA80 = 0;
    }

    while (true) {
        if ((D_801CAA78[1] == 0xFFFF) || (arg0 < D_801CAA78[1])) {
            return;
        }

        expected = 0;
        flag = (D_801CAA78[3] >> 8) + 0xFF;
        if ((flag == 0xFF) ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(D_801CAA78);
        }
        D_801CAA78 += 5;
    }
}

void func_801BB80C(s16 arg0) {
    u8 flag;
    s32 expected;

    if (arg0 < 0) {
        arg0 = 0;
    }

    if (D_801CAA80 == 0) {
        func_801BB6B8(arg0 - D_8009790C);
        D_801CAA80 = 1;
    }

    while (true) {
        if ((D_801CAA78[1] == 0xFFFE) || (arg0 > D_801CAA78[1])) {
            return;
        }

        expected = 0;
        flag = (D_801CAA78[3] >> 8) + 0xFF;
        if ((flag == 0xFF) ||
            (g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(D_801CAA78);
        }
        D_801CAA78 -= 5;
    }
}

void InitRoomEntities(s32 objLayoutId) {
    u16* pObjLayoutStart = D_801808EC[objLayoutId];
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;
    s16 temp_s0;
    s16 arg0;
    s16 i;
    u16* temp_v1;

    D_801CAA74 = pObjLayoutStart;
    D_801CAA78 = D_801809C0[objLayoutId];

    if (*pObjLayoutStart != 0xFFFE) {
        D_801CAA74 = pObjLayoutStart + 1;
        arg0 = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp_v1 = D_801CAA74;
            D_801CAA74 = temp_v1 + 1;
            arg0 -= temp_v1[0];
            if (arg0 < 0) {
                break;
            }
            D_801CAA74 = temp_v1 + 3;
        }
        D_801CAA74 = (temp_v1[2] << 0x10) + temp_v1[1];
        D_801CAA78 += i * 2 + 2;
        D_801CAA78 = (D_801CAA78[1] << 0x10) + D_801CAA78[0];
    }
    arg0 = currentRoomTileLayout->unkA;
    temp_s0 = arg0 + 0x140;
    i = arg0 - 0x40;
    if (i < 0) {
        i = 0;
    }

    D_801CAA7C = 0;
    D_801CAA80 = 0;
    func_801BB3B8(i);
    func_801BB45C(temp_s0);
    func_801BB66C(currentRoomTileLayout->unkE + 0x120);
}

void func_801BBA98(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = g_Camera.posX.i.hi;
        if (D_80097908 > 0)
            func_801BB45C(tmp + 320);
        else
            func_801BB558(tmp - 64);
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0)
            func_801BB710(currentRoomTileLayout->unkE + 288);
        else
            func_801BB80C(tmp - 64);
    }
}

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 entityId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->entityId = entityId;
    ent2->pfnUpdate = PfnEntityUpdates[entityId - 1];
    ent2->posX.i.hi = ent1->posX.i.hi;
    ent2->posY.i.hi = ent1->posY.i.hi;
}

s32 func_801BBC3C(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/39908", EntityRedDoor);

void DestroyEntity(Entity* self) {
    s32 i;
    s32 length;
    u32* ptr;

    if (self->flags & FLAG_HAS_PRIMS) {
        g_api.FreePrimitives(self->primIndex);
    }

    ptr = (u32*)self;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &g_Entities[index];

    while (entity < &D_8007EF1C) {
        DestroyEntity(entity);
        entity++;
    }
}

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u32 value = (entity->entityRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "st/AnimateEntity.h"

u8 func_801BCAD4(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->animFrameIdx * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->animFrameDuration == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1++;
            self->animFrameIdx++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.stub[0x3F] = (arg2 * Random()) >> 8;
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1;
            self->animFrameIdx++;
            return 0;
        }
    }
    self->animFrameDuration--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

// Absolute distance from g_CurrentEntity to the player in the X Axis
s32 GetDistanceToPlayerX(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

/**
 * Returns the player's side position relative to g_CurrentEntity
 * 0 = Player is on the right side
 * 1 = Player is on the left side
 * 2 = Player is above
 */
s16 GetSideToPlayer(void) {
    s16 side = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        side |= 2;
    }
    return side;
}

void MoveEntity() {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

s32 func_801BCCFC(u16* sensors) {
    Collider col;
    Collider colBack;
    s16 x;
    s16 y;
    s16 i;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->velocityY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *sensors++;
            y += *sensors++;
            g_api.CheckCollision(x, y, &col, 0);
            if (col.effects & EFFECT_UNK_8000) {
                if (i == 1) {
                    if (col.effects & EFFECT_SOLID) {
                        g_api.CheckCollision(x, y - 8, &colBack, 0);
                        if (!(colBack.effects & EFFECT_SOLID)) {
                            g_CurrentEntity->posY.i.hi =
                                (u16)g_CurrentEntity->posY.i.hi + 4 + col.unk18;
                            g_CurrentEntity->velocityX = 0;
                            g_CurrentEntity->velocityY = 0;
                            g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                            return 1;
                        }
                    }
                    continue;
                }
            }
            if (col.effects & EFFECT_NOTHROUGH && i != 1) {
                if (col.effects & EFFECT_QUICKSAND) {
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 4;
                }
                g_api.CheckCollision(x, y - 8, &colBack, 0);
                if (!(colBack.effects & EFFECT_SOLID)) {
                    g_CurrentEntity->posY.i.hi =
                        g_CurrentEntity->posY.i.hi + col.unk18;
                    g_CurrentEntity->velocityX = 0;
                    g_CurrentEntity->velocityY = 0;
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 1;
                }
            }
        }
    }
    g_CurrentEntity->flags |= FLAG_UNK_10000000;
    return 0;
}

s32 func_801BCF74(s16* posX) {
    Collider collider;
    s16 temp2;
    s16 temp4;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    temp2 = g_CurrentEntity->posY.i.hi + 3;
    g_CurrentEntity->posY.i.hi = temp2;
    x = g_CurrentEntity->posX.i.hi + *posX;
    posX++;
    y = temp2 + *posX;
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_SOLID)) {
        return 0;
    }
    posX++;

    g_CurrentEntity->posY.i.hi = g_CurrentEntity->posY.i.hi + collider.unk18;
    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            temp4 = x - *posX;
            posX++;
        } else {
            temp4 = x + *posX;
            posX++;
        }
        y = y + *posX - 7;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                g_CurrentEntity->posX.val =
                    g_CurrentEntity->posX.val - g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
                return 0xFF;
            }
            return 0x61;
        }
        y += 15;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                return 0x61;
            }
            return 1;
        }
        g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
        g_CurrentEntity->velocityX = 0;

        return 0x80;
    }
    return 1;
}

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (current->entityId == E_NONE) {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

s32 func_801BD1BC(u8 arg0, s16 arg1) { return D_80181978[arg0] * arg1; }

s16 func_801BD1E8(u8 arg0) { return D_80181978[arg0]; } // Unique

void func_801BD204(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_801BD1BC(arg0, arg1);
    g_CurrentEntity->velocityY = func_801BD1BC(arg0 - 0x40, arg1);
}

u8 func_801BD270(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8019AD64(ObjInit2* arg0, ObjInit2* arg1) {
    u16 x, y;

    x = arg1->zPriority - arg0->zPriority;
    y = arg1->palette - arg0->palette;

    return func_801BD270(x, y);
}

u8 func_801BD2F0(s16 arg0, s16 arg1) {
    s16 x, y;

    x = arg0 - g_CurrentEntity->posX.i.hi;
    y = arg1 - g_CurrentEntity->posY.i.hi;

    return func_801BD270(x, y);
}

u8 func_801BD338(u8 arg0, u8 arg1, u8 arg2) {
    u8 var_v0;
    s8 temp_a2 = arg2 - arg1;

    if (temp_a2 < 0) {
        var_v0 = -temp_a2;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
        if (temp_a2 < 0) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void UnkEntityFunc0(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = g_CurrentEntity;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->velocityX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = g_CurrentEntity;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->velocityY = moveY >> 4;
}

u16 func_801BD41C(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801BD44C(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD484(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

// TODO(sestren): Reconcile this func_801BD4CC with the one in 3E30C.c
u16 func_801BD4CC(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void SetSubStep(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_801BD568(u16 arg0, u16 sfxId) {
    if (sfxId != 0) {
        func_801C29B0(sfxId);
    }

    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    g_CurrentEntity->entityId = E_EXPLOSION;
    g_CurrentEntity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    g_CurrentEntity->params = arg0;
    g_CurrentEntity->animCurFrame = 0;
    g_CurrentEntity->unk19 = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = *arg0++;
    g_CurrentEntity->enemyId = enemyId;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->hitboxState = enemyDef->unkC;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->unk24;
    g_CurrentEntity->hitboxOffX = 0;
    g_CurrentEntity->hitboxOffY = 0;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->step++;
    if (g_CurrentEntity->zPriority == 0) {
        g_CurrentEntity->zPriority = g_zEntityCenter.S16.unk0 - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

s32 func_801BD720(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    u16 temp_a1;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (velocityX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_801BD848(u16* hitSensors, s16 sensorCount) {
    s32 velocityX = g_CurrentEntity->velocityX;
    Collider collider;
    s16 x, y;
    s16 i;

    if (velocityX == 0) {
        return;
    }

    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;

    for (i = 0; i < sensorCount; i++) {
        if (velocityX < 0) {
            x += *hitSensors++;
        } else {
            x -= *hitSensors++;
        }
        y += *hitSensors++;

        g_api.CheckCollision(x, y, &collider, 0);

        if ((collider.effects & EFFECT_UNK_0002) &&
            (!(collider.effects & EFFECT_UNK_8000) || (i != 0))) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/39908", func_801BD9A0);

#include "../replace_breakable_with_item_drop.h"

void func_801BDD9C(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->velocityY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->velocityX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }

    if (entity->velocityY < FIX(0.25)) {
        entity->velocityY += FIX(0.125);
    }
}

void func_801BDE20(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += FIX(0.125);
        } else {
            g_CurrentEntity->posY.i.hi += collider.unk18;
        }
    } else {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            func_801BDD9C();
        }
    }
}

void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &g_Status.hearts;
    *hearts += c_HeartPrizes[heartSize];

    if (g_Status.heartsMax < *hearts) {
        *hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_Status.gold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &g_BottomCornerTextTimer;
    if (*unk) {
        g_api.FreePrimitives(g_BottomCornerTextPrims);
        *unk = 0;
    }

    BottomCornerText(D_80181CEC[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80181CA8[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = D_80181CD8[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
        if (player->facing != 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_Status.hearts += HEART_VESSEL_RICHTER;

        if (g_Status.heartsMax < g_Status.hearts) {
            g_Status.hearts = g_Status.heartsMax;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
