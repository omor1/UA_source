#ifndef YTANK_H_INCLUDED
#define YTANK_H_INCLUDED

#include "nucleas.h"
#include "ypabact.h"

struct __NC_STACK_ypatank
{
    NC_STACK_ypaworld *ywo;
    _NC_STACK_ypaworld *yw;
    __NC_STACK_ypabact *bact_internal;
    uint8_t field_c;
    int     field_D;
    xyz     field_11;
    float   field_1D;
    float   field_21;
    uint8_t field_25;
    int     field_26;
};

struct tank_arg128
{
    float field_0;
    xyz field_4;
    int field_10;
    xyz field_14;
};

struct tank_arg129
{
    float field_0;
    xyz field_4;
};

class NC_STACK_ypatank: public NC_STACK_ypabact
{
public:
    virtual size_t func0(stack_vals *stak);
    virtual size_t func1(stack_vals *stak);
    virtual size_t func2(stack_vals *stak);
    virtual size_t func3(stack_vals *stak);
    virtual void AI_layer3(update_msg *arg);
    virtual void User_layer(update_msg *arg);
    virtual void Move(move_msg *arg);
    virtual size_t SetPosition(bact_arg80 *arg);
    virtual void ApplyImpulse(bact_arg83 *arg);
    virtual size_t CollisionWithBact(int arg);
    virtual void Recoil(bact_arg88 *arg);
    virtual void Renew();
    virtual size_t CheckFireAI(bact_arg101 *arg);
    virtual size_t TestTargetSector(__NC_STACK_ypabact *cel_unit);
    virtual void CorrectPositionOnLand(void *);
    virtual size_t ypatank_func128(tank_arg128 *arg);
    virtual size_t ypatank_func129(tank_arg129 *arg);

    virtual size_t compatcall(int method_id, void *data);
    NC_STACK_ypatank() {
        memset(&stack__ypatank, 0, sizeof(stack__ypatank));
    };
    virtual ~NC_STACK_ypatank() {};

    virtual const char * getClassName() {
        return "ypatank.class";
    };

    static NC_STACK_nucleus * newinstance() {
        return new NC_STACK_ypatank();
    };

    enum TANK_ATT
    {
        TANK_ATT_TIP = 0x80002000
    };

    virtual void setTANK_tip(int);

    virtual int getTANK_tip();


    int ypatank_func0__sub0(stack_vals *stak);
    void ypatank_func2__sub0(stack_vals *stak);
    void ypatank_func3__sub0(stack_vals *stak);

    //Data
    static const NewClassDescr description;

    __NC_STACK_ypatank stack__ypatank;
};


#endif // YTANK_H_INCLUDED
