// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[];
extern u16 g_EInitCommon[];

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
#ifdef VERSION_PSP
        self->unk5A = LOHU(objInit->facingLeft);
#else
        self->unk5A = LOH(objInit->facingLeft);
#endif
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }

        if (self->params == 1) {
            self->scaleX = self->scaleY = 0x0200;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
