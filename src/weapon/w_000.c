// Weapon ID #0. Used by weapons:
// Tyrfing, Namakura, Gladius, Scimitar, Cutlass, Saber, Falchion, Broadsword,
// Bekatowa, Damascus sword, Hunter sword, Bastard sword, Talwar, Sword of
// Hador, Luminus, Harper, Gram, Mormegil, Terminus Est, Dark Blade,
// Mourneblade, Badelaire, Unknown#169
#include "weapon_private.h"
#include "shared.h"

u16 g_Clut0[] = {
    0x0000, 0x8000, 0xA821, 0x9DC0, 0xA821, 0xA821, 0xA821, 0xA821, // 0
    0x843F, 0xB0E4, 0x9CA4, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2F3,
    0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xED8C, 0xED8C, 0xED8C, // 1
    0x843F, 0xBC00, 0xBC00, 0xED8C, 0xED8C, 0xED8C, 0xD294, 0xFFFF,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xE021, 0xE021, // 2
    0x801F, 0x9C00, 0xB800, 0xE021, 0x0000, 0x0000, 0xD294, 0xEAD3,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA0C0, 0x0000, // 3
    0x843F, 0x0000, 0xA800, 0x0000, 0xF608, 0x0000, 0xD294, 0xE24C,
    0x0000, 0x8000, 0x9C00, 0x9DC0, 0x9C00, 0x9C00, 0x9C00, 0x9C00, // 4
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2D1,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0xD400, 0xD400, 0xD400, 0xD400, // 5
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xCCA0, 0x0000, // 6
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEA90,
};

u16 g_Clut1[] = {
    0x0000, 0x8007, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, // 0
    0x843F, 0xB148, 0xA928, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8007, 0x0000, 0x0000, 0x0000, 0xE717, 0xE717, 0xE717, // 1
    0x843F, 0xA0E6, 0xA0E6, 0xE717, 0xE717, 0xE717, 0xD294, 0xF39C,
    0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xB56A, 0xA927, // 2
    0x801F, 0x9062, 0x98C6, 0xB148, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA4E6, 0x0000, // 3
    0x843F, 0x0000, 0x9483, 0x0000, 0xA0C4, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8007, 0x98C6, 0x9DC0, 0x98C6, 0x98C6, 0x98C6, 0x98C6, // 4
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8007, 0x0000, 0x9DC0, 0xA94A, 0xA94A, 0xA94A, 0xA94A, // 5
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A5, 0x0000, // 6
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEB5A,
};

u16 g_Clut2[] = {
    0x0000, 0x8000, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, // 0
    0x83E0, 0x800F, 0x8CB4, 0x0000, 0x0000, 0x0000, 0xD294, 0xCF1C,
    0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xA818, 0xB0B8, 0xAC38, // 1
    0x83E0, 0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8014, 0x940C, // 2
    0x83E0, 0x8005, 0x844E, 0x807D, 0x0000, 0x0000, 0xD294, 0xE35C,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA008, 0x0000, // 3
    0x83E0, 0x0000, 0x8008, 0x0000, 0x806C, 0x0000, 0xD294, 0xBEBC,
    0x0000, 0x8000, 0x800B, 0x9DC0, 0x800B, 0x800B, 0x800B, 0x800B, // 4
    0x83E0, 0xB9C0, 0x800B, 0x0000, 0x0000, 0x0000, 0xD294, 0xAABC,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x8011, 0x8011, 0x8011, 0x8011, // 5
    0x83E0, 0xB9C0, 0x8011, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8008, 0x0000, // 6
    0x83E0, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0x9E1C,
};

u16 g_Clut3[] = {
    0x0000, 0x8000, 0x8900, 0x8900, 0x8900, 0x8900, 0x8902, 0x8904, // 0
    0x843F, 0x9541, 0x95E1, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2D1,
    0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xA208, 0xA208, 0xA208, // 1
    0x843F, 0x9541, 0x9541, 0xA208, 0xA208, 0xA208, 0xD294, 0xF39C,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8160, 0x8920, // 2
    0x801F, 0x8080, 0x88E1, 0x8160, 0x0000, 0x0000, 0xD294, 0xE796,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A0, 0x0000, // 3
    0x843F, 0x0000, 0x8080, 0x0000, 0xA264, 0x0000, 0xD294, 0xAB8D,
    0x0000, 0x8000, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x80E0, // 4
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2B2,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x8200, 0x8200, 0x8200, 0x8200, // 5
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8000, 0x0000, 0xA686, 0x0000, 0x0000, 0xA520, 0x0000, // 6
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xB792,
};

u16 g_Clut4[] = {
    0x0000, 0x8000, 0x817F, 0x81B6, 0x81DF, 0x827F, 0xA2FE, 0xD77F, // 0
    0x843F, 0x819E, 0x9A1F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xB77D, 0xB77D, 0xB77D, // 1
    0x843F, 0x811E, 0x811E, 0xB77D, 0xB77D, 0xB77D, 0xD294, 0xFFFF,
    0x0000, 0x8000, 0x0000, 0x9A1F, 0x0000, 0x0000, 0x8E3F, 0x99DF, // 2
    0x801F, 0x80B0, 0x811A, 0x9ADF, 0x0000, 0x0000, 0xD294, 0xE35C,
    0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x80FE, 0x0000, // 3
    0x843F, 0x0000, 0x80B1, 0x0000, 0x8157, 0x0000, 0xD294, 0xD31C,
    0x0000, 0x8000, 0x8158, 0x81B6, 0x819B, 0x823D, 0xA2FF, 0xD31F, // 4
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8000, 0x0000, 0xB77D, 0xB77D, 0xB77D, 0xB77D, 0xB77D, // 5
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
    0x0000, 0x8000, 0x0000, 0x819E, 0x0000, 0x0000, 0x811E, 0x0000, // 6
    0x843F, 0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C,
};

u8 g_Anim0Frame0[] = {
    0x01, 0x02, 0x02, 0x04, 0x03, 0x04, 0x04, 0x04, 0x05, 0x04,
    0x06, 0x06, 0x07, 0x06, 0x08, 0x06, 0x09, 0x06, 0x0A, 0x08,
    0x0B, 0x08, 0x0C, 0x08, 0x0D, 0x08, 0xFF, 0xFF,
};

u8 g_Anim0Frame1[] = {
    0x0E, 0x0A, 0x0F, 0x0C, 0x10, 0x0C, 0x11, 0x0C, 0x12, 0x0C,
    0x13, 0x0E, 0x14, 0x0E, 0x15, 0x0E, 0x16, 0x0E, 0x1F, 0x08,
    0x20, 0x08, 0x21, 0x08, 0x22, 0x08, 0xFF, 0xFF,
};

u8 g_Anim0Frame2[] = {
    0x0E, 0x0A, 0x17, 0x10, 0x18, 0x12, 0x19, 0x10, 0x1A, 0x12,
    0x1B, 0x14, 0x1C, 0x14, 0x1D, 0x14, 0x1E, 0x14, 0x1F, 0x08,
    0x20, 0x08, 0x21, 0x08, 0x22, 0x08, 0xFF, 0xFF};

u8 g_Anim0Frame3[] = {
    0x23, 0x16, 0x24, 0x18, 0x25, 0x18, 0x26, 0x18, 0x27, 0x18, 0x28, 0x1A,
    0x29, 0x1A, 0x2A, 0x1A, 0x2B, 0x1A, 0x2C, 0x08, 0xFF, 0xFF, 0x00, 0x00};

u8 g_Anim0Frame4[] = {
    0x2D, 0x1C, 0x2E, 0x1E, 0x2F, 0x1E, 0x30, 0x1E, 0x31, 0x1E, 0x32, 0x20,
    0x33, 0x20, 0x34, 0x20, 0x35, 0x20, 0x3E, 0x08, 0xFF, 0xFF, 0x00, 0x00};

u8 g_Anim0Frame5[] = {
    0x2D, 0x1C, 0x36, 0x22, 0x37, 0x22, 0x38, 0x22, 0x39, 0x22, 0x3A, 0x24,
    0x3B, 0x24, 0x3C, 0x24, 0x3D, 0x24, 0x3E, 0x08, 0xFF, 0xFF, 0x00, 0x00};

u8 g_Anim1Frame0[] = {
    0x01, 0x02, 0x3F, 0x26, 0x40, 0x26, 0x41, 0x26, 0x06, 0x06,
    0x07, 0x06, 0x08, 0x06, 0x09, 0x06, 0x0A, 0x08, 0x0B, 0x08,
    0x0C, 0x08, 0x0D, 0x08, 0xFF, 0xFF, 0x00, 0x00,
};

u8 g_Anim1Frame1[] = {
    0x0E, 0x0A, 0x42, 0x28, 0x43, 0x28, 0x44, 0x28, 0x13, 0x0E,
    0x14, 0x0E, 0x15, 0x0E, 0x16, 0x0E, 0x1F, 0x08, 0x20, 0x08,
    0x21, 0x08, 0x22, 0x08, 0xFF, 0xFF, 0x00, 0x00,
};

u8 g_Anim1Frame2[] = {
    0x0E, 0x0A, 0x45, 0x2A, 0x46, 0x2A, 0x47, 0x2A, 0x1B, 0x14,
    0x1C, 0x14, 0x1D, 0x14, 0x1E, 0x14, 0x1F, 0x08, 0x20, 0x08,
    0x21, 0x08, 0x22, 0x08, 0xFF, 0xFF, 0x00, 0x00,
};

u8 g_Anim1Frame3[] = {
    0x23, 0x16, 0x48, 0x2C, 0x49, 0x2C, 0x4A, 0x2C, 0x28, 0x1A,
    0x29, 0x1A, 0x2A, 0x1A, 0x2B, 0x1A, 0x2C, 0x08, 0xFF, 0xFF,
};

u8 g_Anim1Frame4[] = {
    0x2D, 0x1C, 0x4B, 0x2E, 0x4C, 0x2E, 0x4D, 0x2E, 0x32, 0x20,
    0x33, 0x20, 0x34, 0x20, 0x35, 0x20, 0x3E, 0x08, 0xFF, 0xFF,
};

u8 g_Anim1Frame5[] = {
    0x2D, 0x1C, 0x4E, 0x30, 0x4F, 0x30, 0x50, 0x30, 0x3A, 0x24,
    0x3B, 0x24, 0x3C, 0x24, 0x3D, 0x24, 0x3E, 0x08, 0xFF, 0xFF,
};

s8 g_Hitboxes[][4] = {
    {0, 0, 0, 0},     {4, -23, 8, 5},   {30, -17, 35, 8}, {30, -14, 18, 4},
    {-32, -31, 0, 0}, {-4, -6, 8, 5},   {22, 0, 35, 8},   {22, 3, 18, 4},
    {29, 22, 13, 11}, {12, 7, 19, 12},  {14, 14, 18, 4},  {1, -25, 8, 5},
    {27, -19, 35, 8}, {27, -16, 18, 4}, {-8, -26, 8, 5},  {24, -17, 35, 8},
    {24, -14, 18, 4}, {23, 0, 27, 14},  {18, 2, 21, 11},  {29, -14, 34, 4},
    {21, 3, 34, 4},   {28, 21, 12, 10}, {26, -16, 34, 4}, {23, -14, 34, 4},
    {22, 3, 26, 10},
};

u8* g_Anim0[] = {
    g_Anim0Frame0, g_Anim0Frame0, g_Anim0Frame1, g_Anim0Frame2,
    g_Anim0Frame3, g_Anim0Frame4, g_Anim0Frame5,
};

u8* g_Anim1[] = {
    g_Anim1Frame0, g_Anim1Frame0, g_Anim1Frame1, g_Anim1Frame2,
    g_Anim1Frame3, g_Anim1Frame4, g_Anim1Frame5,
};

WeaponAnimation g_SoundEvents[] = {
    {g_Anim1, g_Hitboxes, 0, 0x60B, 0x41, 4},
    {g_Anim0, g_Hitboxes, 0, 0x60B, 0x41, 4},
    {g_Anim0, g_Hitboxes, 0, 0x60C, 0x41, 4},
    {g_Anim0, g_Hitboxes, 0, 0x6A8, 0x41, 4},
    {g_Anim0, g_Hitboxes, 0, 0x60C, 0x41, 4},
};

u16* g_Cluts[] = {
    g_Clut1, g_Clut0, g_Clut2, g_Clut3, g_Clut4,
};

s32 g_HandId = HAND_ID;

void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s32 mask;
    s16 subType;

    self->posX.val = g_Entities->posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    subType = self->params & 0x7FFF;
    subType >>= 8;
    anim = &g_SoundEvents[subType];

    if (!(PLAYER.ext.weapon.unkAC >= anim->frameStart &&
          PLAYER.ext.weapon.unkAC < anim->frameStart + 7 &&
          g_Player.unk46 != 0)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = 0x30;
        SetWeaponProperties(self, 0);
        self->step++;
    }

    self->ext.generic.unkAC = PLAYER.ext.weapon.unkAC - anim->frameStart;
    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 0; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
