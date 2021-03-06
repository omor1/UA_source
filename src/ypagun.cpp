#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "yw.h"
#include "ypagun.h"
#include "yparobo.h"


const NewClassDescr NC_STACK_ypagun::description("ypagun.class", &newinstance);

int NC_STACK_ypagun::ypagun_func0__sub0(stack_vals *stak)
{
    stack__ypagun.field_30 = 1;
    stack__ypagun.field_31 = 100;

    stack_vals *stk = stak;

    while ( 1 )
    {
        if (stk->id == stack_vals::TAG_END)
            break;
        else if (stk->id == stack_vals::TAG_PTAGS)
        {
            stk = (stack_vals *)stk->value.p_data;
        }
        else if ( stk->id == stack_vals::TAG_SKIP_N )
        {
            stk += stk->value.i_data;
            ////a2++; ////BUGFIX?
        }
        else
        {
            switch ( stk->id )
            {
            default:
                break;

            case BACT_ATT_WORLD:
                stack__ypagun.ywo = (NC_STACK_ypaworld *)stk->value.p_data;
                stack__ypagun.yw = &stack__ypagun.ywo->stack__ypaworld;
                break;

            case GUN_ATT_SIDEANGLE:
                setGUN_sideAngle(stk->value.i_data);
                break;

            case GUN_ATT_UPANGLE:
                setGUN_upAngle(stk->value.i_data);
                break;

            case GUN_ATT_DOWNANGLE:
                setGUN_downAngle(stk->value.i_data);
                break;

            case GUN_ATT_FIRETYPE:
                setGUN_fireType(stk->value.i_data);
                break;

            case GUN_ATT_FIRETIME:
                setGUN_fireTime(stk->value.i_data);
                break;

            case GUN_ATT_SETGROUND:
                setGUN_setGround ( stk->value.i_data );
                break;

            case GUN_ATT_ROBOGUN:
                setGUN_roboGun ( stk->value.i_data );
                break;
            }
            stk++;
        }
    }

    return 1;
}

size_t NC_STACK_ypagun::func0(stack_vals *stak)
{
    if ( !NC_STACK_ypabact::func0(stak) )
        return 0;

    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    gun->bact_intern = bact;
    bact->bact_type = BACT_TYPES_GUN;

    if ( !ypagun_func0__sub0(stak) )
    {
        func1(NULL);
        return 0;
    }

    return 1;
}

size_t NC_STACK_ypagun::func1(stack_vals *stak)
{
    return NC_STACK_ypabact::func1(stak);
}

int NC_STACK_ypagun::ypagun_func2__sub0(stack_vals *stak)
{
    stack_vals *stk = stak;

    while ( 1 )
    {
        if (stk->id == stack_vals::TAG_END)
            break;
        else if (stk->id == stack_vals::TAG_PTAGS)
        {
            stk = (stack_vals *)stk->value.p_data;
        }
        else if ( stk->id == stack_vals::TAG_SKIP_N )
        {
            stk += stk->value.i_data;
            ////a2++; ////BUGFIX?
        }
        else
        {
            switch ( stk->id )
            {
            default:
                break;

            case GUN_ATT_SIDEANGLE:
                setGUN_sideAngle(stk->value.i_data);
                break;

            case GUN_ATT_UPANGLE:
                setGUN_upAngle(stk->value.i_data);
                break;

            case GUN_ATT_DOWNANGLE:
                setGUN_downAngle(stk->value.i_data);
                break;

            case GUN_ATT_FIRETYPE:
                setGUN_fireType(stk->value.i_data);
                break;

            case GUN_ATT_FIRETIME:
                setGUN_fireTime(stk->value.i_data);
                break;

            case GUN_ATT_SETGROUND:
                setGUN_setGround ( stk->value.i_data );
                break;

            case GUN_ATT_ROBOGUN:
                setGUN_roboGun ( stk->value.i_data );
                break;
            }
            stk++;
        }
    }

    return 1;
}

size_t NC_STACK_ypagun::func2(stack_vals *stak)
{
    NC_STACK_ypabact::func2(stak);
    ypagun_func2__sub0(stak);
    return 1;
}

int NC_STACK_ypagun::ypagun_func3__sub0(stack_vals *stak)
{
    stack_vals *stk = stak;

    while ( 1 )
    {
        if (stk->id == stack_vals::TAG_END)
            break;
        else if (stk->id == stack_vals::TAG_PTAGS)
        {
            stk = (stack_vals *)stk->value.p_data;
        }
        else if ( stk->id == stack_vals::TAG_SKIP_N )
        {
            stk += stk->value.i_data;
            ////a2++; ////BUGFIX?
        }
        else
        {
            switch ( stk->id )
            {
            default:
                break;

            case GUN_ATT_SIDEANGLE:
                *(int *)stk->value.p_data = getGUN_sideAngle();
                break;

            case GUN_ATT_UPANGLE:
                *(int *)stk->value.p_data = getGUN_upAngle();
                break;

            case GUN_ATT_DOWNANGLE:
                *(int *)stk->value.p_data = getGUN_downAngle();
                break;

            case GUN_ATT_FIRETYPE:
                *(int *)stk->value.p_data = getGUN_fireType();
                break;

            case GUN_ATT_FIRETIME:
                *(int *)stk->value.p_data = getGUN_fireTime();
                break;

            case GUN_ATT_SETGROUND:
                *(int *)stk->value.p_data = getGUN_setGround();
                break;

            case GUN_ATT_ROBOGUN:
                *(int *)stk->value.p_data = getGUN_roboGun();
                break;


            }
            stk++;
        }
    }

    return 1;
}

size_t NC_STACK_ypagun::func3(stack_vals *stak)
{
    NC_STACK_ypabact::func3(stak);
    ypagun_func3__sub0(stak);
    return 1;
}


int sub_4BC8E4(NC_STACK_ypagun *obj)
{
    __NC_STACK_ypagun *gun = &obj->stack__ypagun;
    __NC_STACK_ypabact *bact = &obj->stack__ypabact;

    ypaworld_arg136 arg136;
    arg136.pos_x = bact->position.sx;
    arg136.pos_y = bact->position.sy;
    arg136.pos_z = bact->position.sz;
    arg136.field_14 = 0;

    if ( gun->field_39 & 4 )
        arg136.field_18 = -bact->height;
    else
        arg136.field_18 = bact->height;

    arg136.field_1C = 0;
    arg136.field_40 = 0;

    gun->ywo->ypaworld_func136(&arg136);

    return arg136.field_20;
}

void sub_4BC680(NC_STACK_ypagun *obj, float a5)
{
    __NC_STACK_ypagun *gun = &obj->stack__ypagun;
    __NC_STACK_ypabact *bact = &obj->stack__ypabact;

    xyz vaxis = gun->field_24;

    mat3x3 v17;

    mat_gen_axis_rotate(&vaxis, a5, &v17, MAT_FLAG_INV_SIN);

    mat3x3 dst;
    mat_mult(&bact->rotation, &v17, &dst);

    bact->rotation = dst;
}

void NC_STACK_ypagun::AI_layer3(update_msg *arg)
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    float v80 = arg->frameTime / 1000.0;

    switch ( bact->status )
    {
    case BACT_STATUS_NORMAL:
    case BACT_STATUS_IDLE:
    {
        if ( !(gun->field_39 & 2) )
        {
            if ( bact->clock - gun->field_3A > 800 )
            {
                gun->field_3A = bact->clock;

                if ( !sub_4BC8E4(this) )
                {
                    bact->energy = -10;
                    break;
                }
            }
        }

        if ( gun->field_30 == 1 && gun->field_35 > 0 )
        {
            gun->field_35 -= arg->frameTime;

            if ( gun->field_35 <= 0 )
            {
                gun->field_35 = 0;

                setState_msg arg78;
                arg78.unsetFlags = BACT_STFLAG_FIRE;
                arg78.newStatus = BACT_STATUS_NOPE;
                arg78.setFlags = 0;

                SetState(&arg78);
            }
        }

        if ( bact->secndTtype != BACT_TGT_TYPE_UNIT )
        {
            if ( !bact->secndTtype && gun->field_30 == 2 )
            {
                if ( bact->status_flg & BACT_STFLAG_FIRE )
                {
                    setState_msg arg78;
                    arg78.unsetFlags = BACT_STFLAG_FIRE;
                    arg78.newStatus = BACT_STATUS_NOPE;
                    arg78.setFlags = 0;

                    SetState(&arg78);
                }
            }
            break;
        }


        float v57 = bact->secndT.pbact->position.sx - bact->position.sx;
        float v58 = bact->secndT.pbact->position.sy - bact->position.sy;
        float v59 = bact->secndT.pbact->position.sz - bact->position.sz;

        float v19 = sqrt(POW2(v57) + POW2(v58) + POW2(v59));

        if ( v19 <= 0.001 )
            break;

        float v30 = gun->dir.sx * gun->field_24.sy;
        float v23 = gun->dir.sx * gun->field_24.sz;

        float v32 = gun->dir.sy * gun->field_24.sx;
        float v20 = gun->dir.sy * gun->field_24.sz;

        float v22 = gun->dir.sz * gun->field_24.sx;
        float v21 = gun->dir.sz * gun->field_24.sy;

        v57 /= v19;
        v58 /= v19;
        v59 /= v19;

        float v54 = v20 - v21;
        float v55 = v22 - v23;
        float v56 = v30 - v32;

        float v60 = v21 - v20;
        float v61 = v23 - v22;
        float v62 = v32 - v30;

        float v91 = v60 * bact->rotation.m00 + v61 * bact->rotation.m01 + v62 * bact->rotation.m02;

        if ( v91 > 1.0 )
            v91 = 1.0;

        if ( v91 < -1.0 )
            v91 = -1.0;

        float v78 = acos(v91);

        if ( v60 * bact->rotation.m02 - v62 * bact->rotation.m00 < 0.0 )
            v78 = -v78;

        float v96 = v55 * v58 + v54 * v57 + v56 * v59;

        if ( v96 > 1.0 )
            v96 = 1.0;

        if ( v96 < -1.0 )
            v96 = -1.0;

        float v97 = asin(v96);

        float v92 = gun->dir.sx * v57 + gun->dir.sy * v58 + gun->dir.sz * v59;

        if ( v92 > 1.0 )
            v92 = 1.0;

        if ( v92 < -1.0 )
            v92 = -1.0;

        if ( acos(v92) > 1.570796326794896 )
        {
            if ( v97 < 0.0 )
                v97 = -3.141592653589793 - v97;

            if ( v97 > 0.0 )
                v97 = 3.141592653589793 - v97;
        }

        if ( gun->field_14 <= 3.1 )
        {
            if ( v97 < -gun->field_14 )
                v97 = -gun->field_14;

            if ( v97 > gun->field_14 )
                v97 = gun->field_14;
        }

        float a5 = v97 - v78;

        if ( gun->field_14 > 3.1 )
        {
            if ( fabs(a5) > 3.141592653589793 )
            {
                if ( a5 < -3.141592653589793 )
                    a5 += 6.283185307179586;

                if ( a5 > 3.141592653589793 )
                    a5 -= 6.283185307179586;
            }
        }

        float ttmp = bact->maxrot * v80;

        if ( a5 >= 0.0 )
        {
            if ( a5 > ttmp )
                a5 = ttmp;
        }
        else
        {
            if ( a5 < -ttmp )
                a5 = -ttmp;
        }

        if ( a5 < -0.001 || a5 > 0.001 )
        {
            a5 = -a5;

            sub_4BC680(this, a5);
        }

        float v90 = -gun->field_24.sx * bact->rotation.m20 + -gun->field_24.sy * bact->rotation.m21 + -gun->field_24.sz * bact->rotation.m22;

        if ( v90 > 1.0 )
            v90 = 1.0;

        if ( v90 < -1.0 )
            v90 = -1.0;

        float v70 = asin(v90);

        float v95 = -gun->field_24.sy * v58 + -gun->field_24.sx * v57 + -gun->field_24.sz * v59;

        if ( v95 > 1.0 )
            v95 = 1.0;

        if ( v95 < -1.0 )
            v95 = -1.0;

        float v79 = asin(v95);

        if ( v79 > gun->field_c )
            v79 = gun->field_c;

        if ( v79 < -gun->field_10 )
            v79 = -gun->field_10;

        float v89 = v79 - v70;

        if ( v89 >= 0.0 )
        {
            if ( v89 > ttmp )
                v89 = ttmp;
        }
        else
        {
            if ( v89 < -ttmp )
                v89 = -ttmp;
        }

        if ( v89 < -0.001 || v89 > 0.001 )
        {
            float cs = cos(v89 * 0.3);
            float sn = sin(v89 * 0.3);

            mat3x3 mat1;
            mat1.m00 = 1.0;
            mat1.m01 = 0;
            mat1.m02 = 0;
            mat1.m10 = 0;
            mat1.m11 = cs;
            mat1.m12 = sn;
            mat1.m21 = -sn;
            mat1.m20 = 0;
            mat1.m22 = cs;

            mat3x3 v49;
            mat_mult(&mat1, &bact->rotation, &v49);

            bact->rotation = v49;
        }

        bact_arg75 arg75;
        arg75.fperiod = v80;
        arg75.g_time = bact->clock;
        arg75.target.pbact = bact->secndT.pbact;

        FightWithBact(&arg75);

        if ( !TestTargetSector(bact->secndT.pbact) )
        {
            setTarget_msg arg67;
            arg67.tgt_type = BACT_TGT_TYPE_NONE;
            arg67.priority = 1;

            SetTarget(&arg67);

            if ( gun->field_30 == 2 )
            {
                setState_msg arg78;
                arg78.unsetFlags = BACT_STFLAG_FIRE;
                arg78.newStatus = BACT_STATUS_NOPE;
                arg78.setFlags = 0;

                SetState(&arg78);
            }
        }
    }
    break;

    case BACT_STATUS_DEAD:
        DeadTimeUpdate(arg);
        break;

    case BACT_STATUS_CREATE:
        bact->scale_time -= arg->frameTime;

        if ( bact->scale_time <= 0 )
        {
            setState_msg arg78;
            arg78.newStatus = BACT_STATUS_NORMAL;
            arg78.setFlags = 0;
            arg78.unsetFlags = 0;

            SetState(&arg78);
        }
        break;

    default:
        break;
    }
}

void NC_STACK_ypagun::User_layer(update_msg *arg)
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    float v40 = arg->frameTime / 1000.0;

    if ( bact->status == BACT_STATUS_NORMAL )
    {
        if ( gun->field_39 & 2 || sub_4BC8E4(this) )
        {
            if ( sqrt( POW2(bact->viewer_position.sx) + POW2(bact->viewer_position.sx) + POW2(bact->viewer_position.sz) ) >= 3.0 )
            {
                float v33 = arg->frameTime + 50.0;

                bact->viewer_position.sx *= 50.0 / v33;
                bact->viewer_position.sy *= 50.0 / v33;
                bact->viewer_position.sz *= 50.0 / v33;
            }
            else
            {
                bact->viewer_position.sz = 0;
                bact->viewer_position.sy = 0;
                bact->viewer_position.sx = 0;
            }

            if ( bact->status_flg & BACT_STFLAG_FIRE )
            {
                if ( !(arg->inpt->but_flags & 1) && !(arg->inpt->but_flags & 2) )
                {
                    setState_msg arg78;
                    arg78.setFlags = 0;
                    arg78.newStatus = BACT_STATUS_NOPE;
                    arg78.unsetFlags = BACT_STFLAG_FIRE;

                    SetState(&arg78);
                }
            }

            bact_arg79 arg79;
            arg79.tgType = BACT_TGT_TYPE_CELL;
            arg79.tgt_pos.sx = bact->rotation.m20 * 1200.0 * 3.0 + bact->position.sx;
            arg79.tgt_pos.sy = bact->rotation.m21 * 1200.0 * 3.0 + bact->position.sy;
            arg79.tgt_pos.sz = bact->rotation.m22 * 1200.0 * 3.0 + bact->position.sz;

            bact_arg106 arg106;
            arg106.field_4.sx = bact->rotation.m20;
            arg106.field_4.sy = bact->rotation.m21;
            arg106.field_4.sz = bact->rotation.m22;
            arg106.field_0 = 5;

            if ( UserTargeting(&arg106) )
            {
                arg79.target.pbact = arg106.ret_bact;
                arg79.tgType = BACT_TGT_TYPE_UNIT;
            }

            if ( arg->inpt->but_flags & 1 || arg->inpt->but_flags & 2 )
            {
                if ( gun->field_30 == 1 )
                {
                    arg79.weapon = bact->weapon;
                    arg79.direction.sx = bact->rotation.m20;
                    arg79.direction.sy = bact->rotation.m21;
                    arg79.direction.sz = bact->rotation.m22;
                    arg79.g_time = bact->clock;
                    arg79.start_point = bact->fire_pos;
                    arg79.flags = ((arg->inpt->but_flags & 2) != 0) | 2;

                    if ( LaunchMissile(&arg79) )
                    {
                        bact->viewer_position.sy = 0;
                        bact->viewer_position.sz = -25.0;
                        bact->viewer_position.sx = 0;
                    }
                }
                else if ( gun->field_30 == 2 )
                {
//            if ( ~(bact->field_3D6 & 0x100) ) CHECK IT
                    if ( !(bact->status_flg & BACT_STFLAG_FIRE) )
                    {
                        setState_msg arg78;
                        arg78.unsetFlags = 0;
                        arg78.newStatus = BACT_STATUS_NOPE;
                        arg78.setFlags = BACT_STFLAG_FIRE;

                        SetState(&arg78);
                    }

                    bact_arg105 arg105;
                    arg105.field_0.sx = bact->rotation.m20;
                    arg105.field_0.sy = bact->rotation.m21;
                    arg105.field_0.sz = bact->rotation.m22;
                    arg105.field_C = v40;
                    arg105.field_10 = bact->clock;

                    FireMinigun(&arg105);

                    if ( gun->field_39 & 8 )
                    {
                        gun->field_39 &= 0xF7;
                    }
                    else
                    {
                        gun->field_39 |= 8;

                        bact->viewer_position.sx = 0;
                        bact->viewer_position.sy = -20.0;
                        bact->viewer_position.sz = -30.0;
                    }
                }
            }

            float a5 = arg->inpt->sliders_vars[0] * bact->maxrot * v40;

            if ( fabs( a5 ) > 0.001 )
            {
                float v16 = gun->field_24.sy * gun->dir.sz - gun->field_24.sz * gun->dir.sy;
                float v17 = gun->field_24.sz * gun->dir.sx - gun->field_24.sx * gun->dir.sz;
                float v20 = gun->field_24.sx * gun->dir.sy - gun->field_24.sy * gun->dir.sx;

                float v48 =  v16 * bact->rotation.m00 + v17 * bact->rotation.m01 + v20 * bact->rotation.m02;

                if ( v48 > 1.0 )
                    v48 = 1.0;

                if ( v48 < -1.0 )
                    v48 = -1.0;

                float v42 = acos(v48);

                if ( v16 * bact->rotation.m02 - v20 * bact->rotation.m00 > 0.0 )
                    v42 = -v42;

                if ( v42 + a5 < -gun->field_14 )
                    a5 = -gun->field_14 - v42;

                if ( v42 + a5 > gun->field_14 )
                    a5 = gun->field_14 - v42;

                sub_4BC680(this, a5);
            }

            float v46 = arg->inpt->sliders_vars[1] * bact->maxrot * v40;

            if ( fabs(v46) > 0.001 )
            {
                float v50 = -gun->field_24.sx * bact->rotation.m20 + -gun->field_24.sy * bact->rotation.m21 + -gun->field_24.sz * bact->rotation.m22;

                if ( v50 > 1.0 )
                    v50 = 1.0;

                if ( v50 < -1.0 )
                    v50 = -1.0;

                float v41 = asin(v50);

                if ( v41 + v46 < -gun->field_10 )
                    v46 = -gun->field_10 - v41;

                if ( v41 + v46 > gun->field_c )
                    v46 = gun->field_c - v41;

                float sn = sin(v46);
                float cs = cos(v46);

                mat3x3 mat1;
                mat1.m00 = 1.0;
                mat1.m01 = 0;
                mat1.m02 = 0;
                mat1.m10 = 0;
                mat1.m11 = cs;
                mat1.m12 = sn;
                mat1.m20 = 0;
                mat1.m21 = -sn;
                mat1.m22 = cs;

                mat3x3 dst;
                mat_mult(&mat1, &bact->rotation, &dst);

                bact->rotation = dst;
            }

            bact->viewer_rotation = bact->rotation;
        }
        else
        {
            bact->energy = -10;
        }
    }
    else if ( bact->status == BACT_STATUS_DEAD )
        DeadTimeUpdate(arg);
}

void NC_STACK_ypagun::FightWithBact(bact_arg75 *arg)
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    xyz v18;

    v18.sx = arg->target.pbact->position.sx - bact->position.sx;
    v18.sy = arg->target.pbact->position.sy - bact->position.sy;
    v18.sz = arg->target.pbact->position.sz - bact->position.sz;

    float v24 = sqrt(POW2(v18.sx) + POW2(v18.sy) + POW2(v18.sz));

    if ( v24 >= 0.001 )
    {
        v18.sx /= v24;
        v18.sy /= v24;
        v18.sz /= v24;

        if ( v24 <= 2400.0 && v18.sy * bact->rotation.m21 + v18.sx * bact->rotation.m20 + v18.sz * bact->rotation.m22 >= 0.95 )
        {
            if ( gun->field_30 == 1 )
            {
                bact_arg79 arg79;
                arg79.direction = v18;
                arg79.start_point = bact->fire_pos;
                arg79.tgType = BACT_TGT_TYPE_UNIT;
                arg79.target.pbact = arg->target.pbact;
                arg79.weapon = bact->weapon;
                arg79.g_time = arg->g_time;
                arg79.flags = 0;

                if ( LaunchMissile(&arg79) )
                {
                    int a5 = getBACT_inputting();

                    if ( !a5 )
                    {
                        /*bact_node *v15 = (bact_node *)bact->list3.tailpred; //Check it,
                        if ( v15->next ) //on null list it will work too */

                        //must be like:
                        bact_node *v15 = (bact_node *)bact->missiles_list.tailpred; //Check it,
                        if ( v15 != (bact_node *)&bact->missiles_list )
                        {
                            NC_STACK_ypamissile *miss = dynamic_cast<NC_STACK_ypamissile *>(v15->bacto);
                            miss->setMISS_ignoreBuilds(1);
                        }
                    }
                    gun->field_35 = gun->field_31;

                    setState_msg arg78;
                    arg78.unsetFlags = 0;
                    arg78.newStatus = BACT_STATUS_NOPE;
                    arg78.setFlags = BACT_STFLAG_FIRE;

                    SetState(&arg78);
                }
            }
            else if ( gun->field_30 == 2 )
            {
                if ( !(bact->status_flg & BACT_STFLAG_FIRE) )
                {
                    setState_msg arg78;
                    arg78.unsetFlags = 0;
                    arg78.newStatus = BACT_STATUS_NOPE;
                    arg78.setFlags = BACT_STFLAG_FIRE;

                    SetState(&arg78);
                }

                bact_arg105 arg105;
                arg105.field_C = arg->fperiod;
                arg105.field_10 = arg->g_time;
                arg105.field_0.sx = bact->rotation.m20;
                arg105.field_0.sy = bact->rotation.m21;
                arg105.field_0.sz = bact->rotation.m22;

                FireMinigun(&arg105);
            }
        }
        else if ( gun->field_30 == 2 )
        {
            setState_msg arg78;
            arg78.setFlags = 0;
            arg78.newStatus = BACT_STATUS_NOPE;
            arg78.unsetFlags = BACT_STFLAG_FIRE;

            SetState(&arg78);
        }
    }
}

void NC_STACK_ypagun::Die()
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    if ( !(bact->status_flg & BACT_STFLAG_DEATH1) )
    {
        NC_STACK_ypabact::Die();

        int v6 = 1;
        HandleVisChildrens(&v6);

        if ( gun->field_39 & 2 )
        {
            roboGun *a4 = bact->host_station->getROBO_guns();

            for (int i = 0; i < 8; i++)
            {
                if ( this == a4[i].gun_obj )
                    a4[i].gun_obj = NULL;
            }
        }
    }
}

size_t NC_STACK_ypagun::SetPosition(bact_arg80 *arg)
{
    if ( !NC_STACK_ypabact::SetPosition(arg) )
        return 0;

    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    if ( gun->field_39 & 1 )
    {
        ypaworld_arg136 arg136;
        arg136.pos_x = arg->pos.sx;
        arg136.pos_y = arg->pos.sy + -10000.0;
        arg136.pos_z = arg->pos.sz;
        arg136.field_14 = 0;
        arg136.field_18 = 20000.0;
        arg136.field_1C = 0;
        arg136.field_40 = 0;

        gun->ywo->ypaworld_func136(&arg136);

        if ( arg136.field_20 )
            bact->position.sy = arg136.field_30 - bact->overeof;

        gun_arg128 arg128;
        arg128.dir.sx = 0;
        arg128.dir.sy = 0;
        arg128.dir.sz = 1.0;
        arg128.field_0 = 0;

        ypagun_func128(&arg128);
    }
    else if ( !(arg->field_C & 4) )
    {
        bact->position.sy = arg->pos.sy + bact->pSector->height;
    }

    bact->old_pos = bact->position;

    int v12 = 2;
    HandleVisChildrens(&v12);

    return 1;
}

void NC_STACK_ypagun::EnergyInteract(update_msg *arg)
{
    //__NC_STACK_ypagun *gun = &obj->stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    if ( bact->status != BACT_STATUS_DEAD )
    {
        if ( bact->pSector->owner == bact->owner )
            bact->energy += bact->energy_max * (arg->frameTime / 1000.0) * bact->pSector->energy_power / 40000.0;

        if ( bact->energy > bact->energy_max )
            bact->energy = bact->energy_max;
    }
}

void NC_STACK_ypagun::Renew()
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    NC_STACK_ypabact::Renew();

    gun->field_39 = 0;
    gun->field_3A = 0;

    setBACT_extraViewer(1);

    bact->viewer_position.sx = 0;
    bact->viewer_position.sy = 0;
    bact->viewer_position.sz = 0;

    bact->viewer_rotation = bact->rotation;
}

size_t NC_STACK_ypagun::TestTargetSector(__NC_STACK_ypabact *cel_unit)
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    xyz tmp;

    tmp.sx = cel_unit->position.sx - bact->position.sx;
    tmp.sy = cel_unit->position.sy - bact->position.sy;
    tmp.sz = cel_unit->position.sz - bact->position.sz;

    float v35 = sqrt( POW2(tmp.sx) + POW2(tmp.sy) + POW2(tmp.sz) );

    if ( v35 < 1.0 )
        return 1;

    if ( v35 > 2400.0 )
        return 0;

    tmp.sx /= v35;
    tmp.sy /= v35;
    tmp.sz /= v35;

    float v38 = -gun->field_24.sx * tmp.sx - gun->field_24.sy * tmp.sy - gun->field_24.sz * tmp.sz;

    if ( v38 > 1.0 )
        v38 = 1.0;

    if ( v38 < -1.0 )
        v38 = -1.0;

    if ( 1.570796326794896 - acos(v38) > gun->field_c )
        return 0;

    float v37 = gun->field_24.sx * tmp.sx + gun->field_24.sy * tmp.sy + gun->field_24.sz * tmp.sz;

    if ( v37 > 1.0 )
        v37 = 1.0;

    if ( v37 < -1.0 )
        v37 = -1.0;

    if ( 1.570796326794896 - acos(v37) > gun->field_10 )
        return 0;

    float v14 = tmp.sx * gun->field_24.sx + tmp.sy * gun->field_24.sy + tmp.sz * gun->field_24.sz;

    float v32 = tmp.sx - gun->field_24.sx * v14;
    float v33 = tmp.sy - gun->field_24.sy * v14;
    float v34 = tmp.sz - gun->field_24.sz * v14;

    float v23 = sqrt( POW2(v32) + POW2(v33) + POW2(v34) );

    if ( v23 <= 0.1 )
        return 1;

    float v36 = (gun->dir.sx * v32 + gun->dir.sy * v33 + gun->dir.sz * v34) / v23;

    if ( v36 > 1.0 )
        v36 = 1.0;

    if ( v36 < -1.0 )
        v36 = -1.0;

    if ( acos(v36) <= gun->field_14 )
        return 1;

    return 0;
}

void NC_STACK_ypagun::ypagun_func128(gun_arg128 *arg)
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    float v5 = sqrt( POW2(arg->dir.sx) + POW2(arg->dir.sy) + POW2(arg->dir.sz) );

    if ( v5 > 0.001 )
    {
        arg->dir.sx /= v5;
        arg->dir.sy /= v5;
        arg->dir.sz /= v5;
    }

    gun->dir = arg->dir;
    bact->rotation.m20 = arg->dir.sx;
    bact->rotation.m21 = arg->dir.sy;
    bact->rotation.m22 = arg->dir.sz;

    if ( arg->dir.sy != 0.0 )
    {
        if ( arg->dir.sx != 0.0 || arg->dir.sz != 0.0 )
        {
            float v12 = -1.0 / ( arg->dir.sy / sqrt( POW2(arg->dir.sx) + POW2(arg->dir.sz) ) );

            bact->rotation.m11 = sqrt(POW2(v12) / (POW2(v12) + 1.0));

            if ( arg->dir.sx != 0.0 )
            {
                float v14 = 1.0 - POW2(bact->rotation.m11);
                bact->rotation.m10 = sqrt( v14 / (POW2(arg->dir.sz) / (POW2(arg->dir.sx)) + 1.0) );
                bact->rotation.m12 = sqrt( v14 - POW2(bact->rotation.m10) );
            }
            else
            {
                float v17 = 1.0 - POW2(bact->rotation.m11);
                bact->rotation.m12 = sqrt( v17 / (POW2(arg->dir.sx) / (POW2(arg->dir.sz)) + 1.0) );
                bact->rotation.m10 = sqrt( v17 - POW2(bact->rotation.m12) );
            }

            if ( arg->dir.sx < 0.0 )
                bact->rotation.m10 = -bact->rotation.m10;

            if ( arg->dir.sz < 0.0 )
                bact->rotation.m12 = -bact->rotation.m12;

            if ( arg->dir.sy > 0.0 )
            {
                bact->rotation.m10 = -bact->rotation.m10;
                bact->rotation.m12 = -bact->rotation.m12;
            }
        }
        else
        {
            bact->rotation.m10 = 0;
            bact->rotation.m11 = 0;
            bact->rotation.m12 = 1.0;
        }
    }
    else
    {
        bact->rotation.m10 = 0;
        bact->rotation.m11 = 1.0;
        bact->rotation.m12 = 0;
    }

    if ( arg->field_0 & 1 )
    {
        gun->field_39 |= 4;
        bact->rotation.m10 = -bact->rotation.m10;
        bact->rotation.m11 = -bact->rotation.m11;
        bact->rotation.m12 = -bact->rotation.m12;
    }

    gun->field_24.sx = bact->rotation.m10;
    gun->field_24.sy = bact->rotation.m11;
    gun->field_24.sz = bact->rotation.m12;

    bact->rotation.m00 = bact->rotation.m11 * bact->rotation.m22 - bact->rotation.m12 * bact->rotation.m21;
    bact->rotation.m01 = bact->rotation.m12 * bact->rotation.m20 - bact->rotation.m10 * bact->rotation.m22;
    bact->rotation.m02 = bact->rotation.m10 * bact->rotation.m21 - bact->rotation.m11 * bact->rotation.m20;
}

void ypagun_func129__sub0(xyz *vec, xyz *dir, float a4)
{
    float invangl = -a4;

    float sn = sin(-invangl);
    float cs = cos(invangl);
    float ics = 1.0 - cs;

    float v31 = (ics * vec->sx * vec->sy + sn * vec->sz) * dir->sx + (ics * vec->sy + cs) * dir->sy                     + (ics * vec->sy * vec->sz - sn * vec->sx) * dir->sz;
    float v32 = (ics * vec->sx * vec->sx + cs) * dir->sx           + (ics * vec->sx * vec->sy - sn * vec->sz) * dir->sy + (ics * vec->sz * vec->sx + sn * vec->sy) * dir->sz;
    float v33 = (ics * vec->sz * vec->sx - sn * vec->sy) * dir->sx + (ics * vec->sy * vec->sz + sn * vec->sx) * dir->sy + (ics * vec->sz * vec->sz + cs) * dir->sz;

    dir->sx = v32;
    dir->sy = v31;
    dir->sz = v33;
}

void ypagun_func129__sub1(xyz *vec, mat3x3 *mat, float angle)
{
    mat3x3 mat2;

    mat_gen_axis_rotate(vec, angle, &mat2, MAT_FLAG_INV_SIN);

    mat3x3 v18;
    mat_mult(mat, &mat2, &v18);

    *mat = v18;
}

void NC_STACK_ypagun::ypagun_func129(gun_arg129 *arg)
{
    __NC_STACK_ypagun *gun = &stack__ypagun;
    __NC_STACK_ypabact *bact = &stack__ypabact;

    ypagun_func129__sub0(&arg->vec, &gun->dir, arg->angle);

    arg->dir = gun->dir;

    ypagun_func129__sub1(&arg->vec, &bact->rotation, arg->angle);
}


void NC_STACK_ypagun::setGUN_sideAngle(int angl)
{
    stack__ypagun.field_14 = angl / 1000.0;
}

void NC_STACK_ypagun::setGUN_upAngle(int angl)
{
    stack__ypagun.field_c = angl / 1000.0;
}

void NC_STACK_ypagun::setGUN_downAngle(int angl)
{
    stack__ypagun.field_10 = angl / 1000.0;
}

void NC_STACK_ypagun::setGUN_fireType(int tp)
{
    stack__ypagun.field_30 = tp;
}

void NC_STACK_ypagun::setGUN_fireTime(int time)
{
    stack__ypagun.field_31 = time;
}

void NC_STACK_ypagun::setGUN_setGround(int grnd)
{
    if ( grnd )
        stack__ypagun.field_39 |= 1;
    else
        stack__ypagun.field_39 &= ~1;
}

void NC_STACK_ypagun::setGUN_roboGun(int rbo)
{
    if ( rbo )
        stack__ypagun.field_39 |= 2;
    else
        stack__ypagun.field_39 &= ~2;
}



int NC_STACK_ypagun::getGUN_sideAngle()
{
    return stack__ypagun.field_14 * 1000.0;
}

int NC_STACK_ypagun::getGUN_upAngle()
{
    return stack__ypagun.field_c * 1000.0;
}

int NC_STACK_ypagun::getGUN_downAngle()
{
    return stack__ypagun.field_10 * 1000.0;
}

int NC_STACK_ypagun::getGUN_fireType()
{
    return stack__ypagun.field_30;
}

int NC_STACK_ypagun::getGUN_fireTime()
{
    return stack__ypagun.field_31;
}

int NC_STACK_ypagun::getGUN_setGround()
{
    if ( stack__ypagun.field_39 & 1 )
        return 1;
    else
        return 0;
}

int NC_STACK_ypagun::getGUN_roboGun()
{
    if ( stack__ypagun.field_39 & 2 )
        return 1;
    else
        return 0;
}


size_t NC_STACK_ypagun::compatcall(int method_id, void *data)
{
    switch( method_id )
    {
    case 0:
        return (size_t)func0( (stack_vals *)data );
    case 1:
        return (size_t)func1( (stack_vals *)data );
    case 2:
        return func2( (stack_vals *)data );
    case 3:
        return func3( (stack_vals *)data );
    case 70:
        AI_layer3( (update_msg *)data );
        return 1;
    case 71:
        User_layer( (update_msg *)data );
        return 1;
    case 75:
        FightWithBact( (bact_arg75 *)data );
        return 1;
    case 77:
        Die();
        return 1;
    case 80:
        return (size_t)SetPosition( (bact_arg80 *)data );
    case 82:
        EnergyInteract( (update_msg *)data );
        return 1;
    case 96:
        Renew();
        return 1;
    case 111:
        return (size_t)TestTargetSector( (__NC_STACK_ypabact *)data );
    case 128:
        ypagun_func128( (gun_arg128 *)data );
        return 1;
    case 129:
        ypagun_func129( (gun_arg129 *)data );
        return 1;
    default:
        break;
    }
    return NC_STACK_ypabact::compatcall(method_id, data);
}
